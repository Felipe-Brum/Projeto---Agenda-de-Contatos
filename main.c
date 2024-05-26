#include <stdio.h>
#include "Agenda.h"

int main(){
    funcao fs[] = {adicionar, listar, deletar};

    Contato contatos[TOTAL];

    int pos;

    carregar(contatos, &pos);

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Listar contato\n");
        printf("3 - Deletar contato\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;
        if(opcao > 2)
            printf("Opcao invalida\n");
        else if(opcao >= 0) {
            ERROS erro = fs[opcao](contatos, &pos);
            if(erro == NOME_INVALIDO) 
                printf("Erro ao executar a operacao: NOME_INVALIDO - %d\n", erro);
            else if(erro == SOBRENOME_INVALIDO)
                printf("Erro ao executar a operacao: SOBRENOME_INVALIDO - %d\n", erro);
            else if(erro == EMAIL_INVALIDO)
                printf("Erro ao executar a operacao: EMAIL_INVALIDO - %d\n", erro);
            else if(erro == TELEFONE_INVALIDO)
                printf("Erro ao executar a operacao: TELEFONE_INVALIDO - %d\n", erro);
            else if(erro == TELEFONE_DUPLICADO)
                printf("Erro ao executar a operacao: TELEFONE_DUPLICADO - %d\n", erro);
        }
        else
            printf("Sair...\n");

    } while(opcao >= 0);

    salvar(contatos, pos);

    return 0;
}