#include <stdio.h>
#include "ferramental.h"

static int ler_opcao(void) {
    char linha[50];
    int opcao;
    char extra;

    while (1) {
        printf("Escolha uma opcao: ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            return 5;
        }

        if (sscanf(linha, "%d %c", &opcao, &extra) == 1) {
            return opcao;
        }

        printf("Opcao invalida. Digite um numero de 1 a 5.\n");
    }
}

int main(void) {
    int opcao;

    inicializar();
    int carregados = carregar_dados(ARQUIVO_DADOS);

    printf("==============================================\n");
    printf(" SISTEMA DE CONTROLE DE FERRAMENTAL E OFICINA\n");
    printf("==============================================\n");
    printf("Registros carregados de %s: %d\n", ARQUIVO_DADOS, carregados);

    do {
        printf("\n--------------- MENU PRINCIPAL ---------------\n");
        printf("1. Cadastrar ferramenta/equipamento\n");
        printf("2. Listar todos\n");
        printf("3. Buscar por codigo patrimonial\n");
        printf("4. Relatorio / estatistica patrimonial\n");
        printf("5. Salvar e sair\n");
        printf("----------------------------------------------\n");

        opcao = ler_opcao();

        switch (opcao) {
            case 1:
                cadastrar_ferramenta();
                break;
            case 2:
                listar_ferramentas();
                break;
            case 3:
                buscar_ferramenta();
                break;
            case 4:
                relatorio_patrimonio();
                break;
            case 5:
                if (salvar_dados(ARQUIVO_DADOS)) {
                    printf("Dados salvos com sucesso em %s.\n", ARQUIVO_DADOS);
                }
                liberar_memoria();
                printf("Memoria liberada. Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida. Escolha entre 1 e 5.\n");
        }

    } while (opcao != 5);

    return 0;
}
