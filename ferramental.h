#ifndef FERRAMENTAL_H
#define FERRAMENTAL_H

#define MAX 100
#define ARQUIVO_DADOS "dados.txt"

typedef struct {
    int codigo;
    char descricao[81];
    char marca[51];
    int quantidade;
    double valor_estimado;
} Ferramenta;

void inicializar(void);
int carregar_dados(const char *nome_arquivo);
int cadastrar_ferramenta(void);
void listar_ferramentas(void);
void buscar_ferramenta(void);
void relatorio_patrimonio(void);
int salvar_dados(const char *nome_arquivo);
void liberar_memoria(void);
int obter_total_cadastrados(void);

#endif
