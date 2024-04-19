#include <stdio.h>
#include <string.h>
#include "Agenda.h"

ERROS adicionar(Contato contato[], int *pos){

    if(*pos >= TOTAL)
        return MAX_TAREFAS;

    printf("Digite seu nome (primeiro nome): ");
    scanf("%s", contato[*pos].nome);
    clearBuffer();
    if(sizeof(contato[*pos].nome) == 0){
        return NOME_INVALIDO;
    }

    printf("Digite seu sobrenome: ");
    scanf("%s", contato[*pos].sobrenome);
    clearBuffer();
    if(sizeof(contato[*pos].sobrenome) == 0){
        return SOBRENOME_INVALIDO;
    }

    printf("Digite seu email (aleatorio@gmail.com): ");
    scanf("%s", contato[*pos].email);
    clearBuffer();
    if(sizeof(contato[*pos].email) == 0){
        return EMAIL_INVALIDO;
    }

    printf("Digite seu telefone (11912345678): ");
    scanf("%ld", &contato[*pos].telefone);
    clearBuffer();
    if(sizeof(contato[*pos]. telefone) == 0 || contato[*pos].telefone < 10000000000 || contato[*pos].telefone > 99999999999){
        return  TELEFONE_INVALIDO;
    }

    *pos = *pos + 1;

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

ERROS deletar(Contato contato[], int *pos){
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

ERROS salvar(Contato contatos[], int pos) {
    FILE *file = fopen("contatos.bin", "wb");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo para escrita\n");
        return ERRO_ARQUIVO;
    }

    fwrite(contatos, sizeof(Contato), pos, file);

    fclose(file);
    return OK;
}

ERROS carregar(Contato contatos[], int *pos) {
    FILE *file = fopen("contatos.bin", "rb");
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

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
