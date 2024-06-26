#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "Agenda.h"

int validarEmail(const char *email) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}$", REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else {
        return 0;
    }
}

int telefoneDuplicado(Contato contato[], int pos, long telefone) {
    for (int i = 0; i < pos; i++) {
        if (contato[i].telefone == telefone) {
            return 1;
        }
    }
    return 0;
}

ERROS adicionar(Contato contato[], int *pos) {
    if(*pos >= TOTAL)
        return MAX_TAREFAS;

    printf("Digite seu nome (primeiro nome): ");
    scanf("%s", contato[*pos].nome);
    clearBuffer();
    if(strlen(contato[*pos].nome) == 0) {
        return NOME_INVALIDO;
    }

    printf("Digite seu sobrenome: ");
    scanf("%s", contato[*pos].sobrenome);
    clearBuffer();
    if(strlen(contato[*pos].sobrenome) == 0) {
        return SOBRENOME_INVALIDO;
    }

    printf("Digite seu email (aleatorio@gmail.com): ");
    scanf("%s", contato[*pos].email);
    clearBuffer();
    if(strlen(contato[*pos].email) == 0 || !validarEmail(contato[*pos].email)) {
        return EMAIL_INVALIDO;
    }

    printf("Digite seu telefone (11912345678): ");
    scanf("%ld", &contato[*pos].telefone);
    clearBuffer();
    if(contato[*pos].telefone < 10000000000 || contato[*pos].telefone > 99999999999 || telefoneDuplicado(contato, *pos, contato[*pos].telefone)) {
        return TELEFONE_INVALIDO;
    }

    *pos = *pos + 1;

    return OK;
}

ERROS alterar(Contato contato[], int *pos) {
    if(*pos == 0)
        return SEM_CONTATOS;

    long telefone_alterar;
    printf("Entre com o telefone do contato a ser alterado: ");
    scanf("%ld", &telefone_alterar);
    clearBuffer();

    int i;
    for(i = 0; i < *pos; i++){
        if(contato[i].telefone == telefone_alterar)
            break;
    }

    if(i == *pos)
        return TELEFONE_NAO_ENCONTRADO;

    printf("Digite o novo nome (primeiro nome): ");
    scanf("%s", contato[i].nome);
    clearBuffer();
    if(strlen(contato[i].nome) == 0) {
        return NOME_INVALIDO;
    }

    printf("Digite o novo sobrenome: ");
    scanf("%s", contato[i].sobrenome);
    clearBuffer();
    if(strlen(contato[i].sobrenome) == 0) {
        return SOBRENOME_INVALIDO;
    }

    printf("Digite o novo email (aleatorio@gmail.com): ");
    scanf("%s", contato[i].email);
    clearBuffer();
    if(strlen(contato[i].email) == 0 || !validarEmail(contato[i].email)) {
        return EMAIL_INVALIDO;
    }

    long novo_telefone;
    printf("Digite o novo telefone (11912345678): ");
    scanf("%ld", &novo_telefone);
    clearBuffer();
    if(novo_telefone < 10000000000 || novo_telefone > 99999999999 || (novo_telefone != telefone_alterar && telefoneDuplicado(contato, *pos, novo_telefone))) {
        return TELEFONE_INVALIDO;
    }

    contato[i].telefone = novo_telefone;

    return OK;
}

ERROS listar(Contato contatos[], int *pos) {
    if(*pos == 0)
        return SEM_CONTATOS;

    printf("\n==================== Lista de Contatos ====================\n");
    for(int i = 0; i < *pos; i++){
        printf("Nome: %s    ", contatos[i].nome);
        printf("Sobrenome: %s    ", contatos[i].sobrenome);
        printf("Email: %s    ", contatos[i].email);
        printf("Telefone: (%02ld) %05ld-%04ld\n", contatos[i].telefone / 1000000000, (contatos[i].telefone / 10000) % 100000, contatos[i].telefone % 10000);

    }
    printf("===========================================================\n");
    return OK; 
}

ERROS deletar(Contato contato[], int *pos) {
    if(*pos == 0)
        return SEM_CONTATOS;

    long telefone_deletar;
    printf("Entre com o telefone do contato a ser deletado: ");
    scanf("%ld", &telefone_deletar);
    clearBuffer();

    int i;
    for(i = 0; i < *pos; i++){
        if(contato[i].telefone == telefone_deletar)
            break;
    }

    if(i == *pos) 
        return TELEFONE_NAO_ENCONTRADO;

    for(; i < *pos - 1; i++){
        contato[i] = contato[i+1];
    }

    *pos = *pos - 1;

    return OK;
}

ERROS salvar(Contato contatos[], int pos, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo para escrita\n");
        return ERRO_ARQUIVO;
    }

    fwrite(contatos, sizeof(Contato), pos, file);

    fclose(file);
    return OK;
}

ERROS carregar(Contato contatos[], int *pos, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo para leitura\n");
        return ERRO_ARQUIVO;
    }

    *pos = 0;
    while (fread(&contatos[*pos], sizeof(Contato), 1, file) == 1) {
        (*pos)++;
    }

    fclose(file);
    return OK;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}