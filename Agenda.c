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
    if(sizeof(contato[*pos]. telefone) == 0){
        return  TELEFONE_INVALIDO;
    }

    *pos = *pos + 1;

    return OK;
}

ERROS listar(Contato contatos[], int *pos) {
    if(*pos == 0)
        return SEM_CONTATOS;

    for(int i = 0; i < *pos; i++){
        printf("%s\t", contatos[i].nome);
        printf("%s\t", contatos[i].sobrenome);
        printf("%s\t", contatos[i].email);
        printf("%d\n", &contatos[i].telefone);
    }
    return OK; 
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}