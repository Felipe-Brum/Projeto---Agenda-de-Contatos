#define tamanho_tel 11
#define tamanho_nome 100
#define tamanho_sobrenome 100
#define tamanho_email 30
#define TOTAL 255

typedef enum {OK, MAX_TAREFAS, TELEFONE_NAO_ENCONTRADO, SEM_CONTATOS, NOME_INVALIDO, SOBRENOME_INVALIDO, EMAIL_INVALIDO, TELEFONE_INVALIDO, ERRO_ARQUIVO} ERROS;

typedef struct {
    long int telefone;
    char nome[tamanho_nome];
    char sobrenome[tamanho_sobrenome];
    char email[tamanho_email];
} Contato;

typedef ERROS (*funcao)(Contato[], int*);

ERROS adicionar(Contato contato[], int *pos);
ERROS listar(Contato contato[], int *pos);
ERROS deletar(Contato contato[], int *pos);
ERROS salvar(Contato contatos[], int pos);
ERROS carregar(Contato contatos[], int *pos);
void clearBuffer();