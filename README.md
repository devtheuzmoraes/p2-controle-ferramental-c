# P2 — Controle de Ferramental e Oficina em C

Projeto prático integrado da disciplina **Linguagem de Programação I**, desenvolvido em linguagem C com **TAD (Tipo Abstrato de Dados), ponteiros, alocação dinâmica, `struct` e persistência em arquivo texto**.

## Identificação da dupla

- **Matheus Moraes de Oliveira** · RA 1630482613018

- **Caio Fábio Ferreira da Silva** · RA 1630482613005

## Tema escolhido

**Tema 7 — Controle de Ferramental e Oficina**.

O sistema cadastra ferramentas e equipamentos utilizando os seguintes dados:

- código patrimonial;
- descrição;
- marca;
- quantidade disponível;
- valor estimado por unidade.

### Justificativa da escolha

O tema foi escolhido por representar uma situação comum em ambientes industriais e oficinas, permitindo aplicar os conceitos estudados em aula a um problema concreto de controle patrimonial. Além do cadastro e consulta dos equipamentos, o sistema calcula o valor financeiro acumulado dos itens disponíveis, fornecendo uma visão simples do patrimônio da oficina.


## Divisão de tarefas

- **Matheus Moraes de Oliveira:** implementação em C, documentação do projeto, publicação no GitHub e testes iniciais.
- **Caio Fábio Ferreira da Silva:** execução do programa no próprio computador, validação do cadastro, da busca, do relatório e da persistência, e conferência das instruções no Teams. Validação pendente.

## Arquitetura e decisões de implementação

O projeto foi dividido em três arquivos principais, seguindo a abordagem de TAD:

- `ferramental.h`: interface do módulo, definição da `struct Ferramenta`, constantes e protótipos das funções públicas;
- `ferramental.c`: implementação do TAD, incluindo armazenamento, busca, cadastro, persistência, relatórios e gerenciamento de memória;
- `main.c`: fluxo principal da aplicação, responsável apenas pelo menu e pelas chamadas das funções públicas do TAD.

O vetor de dados fica encapsulado dentro de `ferramental.c`:

```c
static Ferramenta *acervo[MAX];
```

Cada posição começa em `NULL`. A memória para um registro é criada somente quando um equipamento é cadastrado ou carregado do arquivo:

```c
Ferramenta *nova = malloc(sizeof(Ferramenta));
```

Antes do encerramento, todas as posições utilizadas são liberadas com `free()` e voltam a apontar para `NULL`.

### Persistência

Os dados são armazenados no arquivo `dados.txt` utilizando o caractere `|` como separador:

```text
codigo|descricao|marca|quantidade|valor
```

Na inicialização:

1. o sistema abre o arquivo com `fopen(..., "r")`;

2. cada linha é lida com `fgets()`;

3. os campos são interpretados com `sscanf()`;

4. um registro é alocado dinamicamente com `malloc()`.

Ao escolher **Salvar e sair**:

1. o arquivo é aberto no modo `"w"`;

2. os registros são gravados com `fprintf()`;

3. o arquivo é fechado com `fclose()`;

4. a memória dinâmica é liberada com `free()`.

Se `dados.txt` não existir, a aplicação inicia normalmente com o acervo vazio.

## Funcionalidades

O menu principal contém:

1. **Cadastrar ferramenta/equipamento** — valida duplicidade de código e realiza alocação dinâmica;

2. **Listar todos** — exibe todos os registros existentes;

3. **Buscar por código patrimonial** — localiza e exibe um único registro;

4. **Relatório/estatística patrimonial** — mostra quantidade de registros, total de unidades, patrimônio total e equipamento com maior valor patrimonial;

5. **Salvar e sair** — persiste os dados, fecha o arquivo e libera a memória.

## Relatório / estatística

Para cada equipamento é calculado:

```text
valor patrimonial do item = quantidade × valor estimado por unidade
```

O relatório apresenta:

- número total de registros;
- número total de unidades em estoque;
- valor patrimonial total da oficina;
- equipamento com maior valor patrimonial acumulado.

## Estrutura do repositório

```text
p2-controle-ferramental/
    ferramental.h
    ferramental.c
    main.c
    dados.txt
    README.md
    .gitignore
    P2 Controle de Ferramental.pdf
```

## Compilação

### GCC — Windows, Linux ou macOS

Dentro da pasta do projeto:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c ferramental.c -o ferramental
```

### Execução no Windows

```powershell
.\ferramental.exe
```

### Execução no Linux/macOS

```bash
./ferramental
```

## Exemplo do arquivo de dados

```text
1001|Furadeira de bancada|Bosch|2|1890.00
1002|Paquimetro digital|Mitutoyo|4|740.50
1003|Torquimetro 20-200 Nm|Gedore|3|1280.90
```

## Conceitos da disciplina aplicados

- `struct`;
- `typedef`;
- TAD e encapsulamento;
- vetor de ponteiros;
- ponteiros;
- alocação dinâmica com `malloc()`;
- liberação de memória com `free()`;
- manipulação de arquivos com `FILE *`, `fopen()`, `fgets()`, `sscanf()`, `fprintf()` e `fclose()`;
- modularização em `.h` e `.c`;
- funções;
- laços de repetição;
- `switch-case` e `do...while`;
- tratamento básico de erros de entrada, arquivo e memória.

## Autores

Matheus Moraes de Oliveira — RA 1630482613018  
Caio Fábio Ferreira da Silva, RA 1630482613005
