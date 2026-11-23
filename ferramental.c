#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ferramental.h"

static Ferramenta *acervo[MAX];
static int total_cadastrados = 0;

static void remover_quebra_linha(char *texto) {
    texto[strcspn(texto, "\n")] = '\0';
}

static void substituir_separador(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '|') {
            texto[i] = '/';
        }
    }
}

static int ler_inteiro(const char *mensagem, int *valor) {
    char linha[100];
    char extra;

    while (1) {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            return 0;
        }

        if (sscanf(linha, "%d %c", valor, &extra) == 1) {
            return 1;
        }

        printf("Entrada invalida. Digite um numero inteiro.\n");
    }
}

static int ler_double(const char *mensagem, double *valor) {
    char linha[100];
    char extra;

    while (1) {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            return 0;
        }

        if (sscanf(linha, "%lf %c", valor, &extra) == 1) {
            return 1;
        }

        printf("Entrada invalida. Digite um valor numerico.\n");
    }
}

static int ler_texto(const char *mensagem, char *destino, size_t tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, (int)tamanho, stdin) == NULL) {
        return 0;
    }

    remover_quebra_linha(destino);
    substituir_separador(destino);
    return 1;
}

static int buscar_posicao_por_codigo(int codigo) {
    for (int i = 0; i < MAX; i++) {
        if (acervo[i] != NULL && acervo[i]->codigo == codigo) {
            return i;
        }
    }
    return -1;
}

static int buscar_posicao_livre(void) {
    for (int i = 0; i < MAX; i++) {
        if (acervo[i] == NULL) {
            return i;
        }
    }
    return -1;
}

static void imprimir_registro(const Ferramenta *f) {
    double patrimonio = f->quantidade * f->valor_estimado;

    printf("\n----------------------------------------\n");
    printf("Codigo patrimonial : %d\n", f->codigo);
    printf("Descricao          : %s\n", f->descricao);
    printf("Marca              : %s\n", f->marca);
    printf("Quantidade         : %d\n", f->quantidade);
    printf("Valor estimado     : R$ %.2f\n", f->valor_estimado);
    printf("Valor patrimonial  : R$ %.2f\n", patrimonio);
    printf("----------------------------------------\n");
}

void inicializar(void) {
    for (int i = 0; i < MAX; i++) {
        acervo[i] = NULL;
    }
    total_cadastrados = 0;
}

int obter_total_cadastrados(void) {
    return total_cadastrados;
}

int carregar_dados(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    char linha[300];
    int carregados = 0;

    if (arquivo == NULL) {
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int posicao = buscar_posicao_livre();
        if (posicao == -1) {
            break;
        }

        Ferramenta temporaria;
        int lidos = sscanf(
            linha,
            "%d|%80[^|]|%50[^|]|%d|%lf",
            &temporaria.codigo,
            temporaria.descricao,
            temporaria.marca,
            &temporaria.quantidade,
            &temporaria.valor_estimado
        );

        if (lidos != 5) {
            continue;
        }

        if (buscar_posicao_por_codigo(temporaria.codigo) != -1) {
            continue;
        }

        Ferramenta *nova = malloc(sizeof(Ferramenta));
        if (nova == NULL) {
            printf("Erro: memoria insuficiente durante a carga dos dados.\n");
            break;
        }

        *nova = temporaria;
        acervo[posicao] = nova;
        total_cadastrados++;
        carregados++;
    }

    fclose(arquivo);
    return carregados;
}

int cadastrar_ferramenta(void) {
    if (total_cadastrados >= MAX) {
        printf("Acervo cheio. Nao e possivel cadastrar mais ferramentas.\n");
        return 0;
    }

    int posicao = buscar_posicao_livre();
    if (posicao == -1) {
        printf("Nao ha posicao livre no vetor.\n");
        return 0;
    }

    Ferramenta *nova = malloc(sizeof(Ferramenta));
    if (nova == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return 0;
    }

    if (!ler_inteiro("Codigo patrimonial: ", &nova->codigo)) {
        free(nova);
        return 0;
    }

    if (buscar_posicao_por_codigo(nova->codigo) != -1) {
        printf("Ja existe uma ferramenta com esse codigo.\n");
        free(nova);
        return 0;
    }

    if (!ler_texto("Descricao: ", nova->descricao, sizeof(nova->descricao)) ||
        !ler_texto("Marca: ", nova->marca, sizeof(nova->marca)) ||
        !ler_inteiro("Quantidade disponivel: ", &nova->quantidade) ||
        !ler_double("Valor estimado por unidade (R$): ", &nova->valor_estimado)) {
        free(nova);
        return 0;
    }

    if (nova->quantidade < 0 || nova->valor_estimado < 0) {
        printf("Quantidade e valor nao podem ser negativos. Cadastro cancelado.\n");
        free(nova);
        return 0;
    }

    acervo[posicao] = nova;
    total_cadastrados++;

    printf("Ferramenta cadastrada com sucesso.\n");
    return 1;
}

void listar_ferramentas(void) {
    if (total_cadastrados == 0) {
        printf("Nenhuma ferramenta cadastrada.\n");
        return;
    }

    printf("\n========== FERRAMENTAS CADASTRADAS ==========\n");
    for (int i = 0; i < MAX; i++) {
        if (acervo[i] != NULL) {
            imprimir_registro(acervo[i]);
        }
    }

    printf("Total de registros: %d\n", total_cadastrados);
}

void buscar_ferramenta(void) {
    int codigo;

    if (!ler_inteiro("Digite o codigo patrimonial para busca: ", &codigo)) {
        return;
    }

    int posicao = buscar_posicao_por_codigo(codigo);
    if (posicao == -1) {
        printf("Ferramenta nao encontrada.\n");
        return;
    }

    imprimir_registro(acervo[posicao]);
}

void relatorio_patrimonio(void) {
    if (total_cadastrados == 0) {
        printf("Nao ha dados para gerar o relatorio.\n");
        return;
    }

    double valor_total = 0.0;
    double maior_patrimonio = -1.0;
    Ferramenta *mais_valiosa = NULL;
    int total_unidades = 0;

    for (int i = 0; i < MAX; i++) {
        if (acervo[i] != NULL) {
            double patrimonio_item = acervo[i]->quantidade * acervo[i]->valor_estimado;
            valor_total += patrimonio_item;
            total_unidades += acervo[i]->quantidade;

            if (patrimonio_item > maior_patrimonio) {
                maior_patrimonio = patrimonio_item;
                mais_valiosa = acervo[i];
            }
        }
    }

    printf("\n============= RELATORIO PATRIMONIAL =============\n");
    printf("Registros cadastrados : %d\n", total_cadastrados);
    printf("Unidades em estoque   : %d\n", total_unidades);
    printf("Patrimonio total      : R$ %.2f\n", valor_total);

    if (mais_valiosa != NULL) {
        printf("Maior patrimonio     : %s (codigo %d) - R$ %.2f\n",
               mais_valiosa->descricao,
               mais_valiosa->codigo,
               maior_patrimonio);
    }
    printf("===================================================\n");
}

int salvar_dados(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir %s para gravacao.\n", nome_arquivo);
        return 0;
    }

    for (int i = 0; i < MAX; i++) {
        if (acervo[i] != NULL) {
            fprintf(
                arquivo,
                "%d|%s|%s|%d|%.2f\n",
                acervo[i]->codigo,
                acervo[i]->descricao,
                acervo[i]->marca,
                acervo[i]->quantidade,
                acervo[i]->valor_estimado
            );
        }
    }

    fclose(arquivo);
    return 1;
}

void liberar_memoria(void) {
    for (int i = 0; i < MAX; i++) {
        if (acervo[i] != NULL) {
            free(acervo[i]);
            acervo[i] = NULL;
        }
    }
    total_cadastrados = 0;
}
