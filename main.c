#include <stdio.h>
#include "Agenda.h"

int main() {
    funcao fs[] = {adicionar, listar, deletar, alterar};

    Contato contatos_pessoais[TOTAL];
    Contato contatos_trabalho[TOTAL];

    int pos_pessoais = 0;
    int pos_trabalho = 0;

    carregar(contatos_pessoais, &pos_pessoais, "contatos_pessoais.bin");
    carregar(contatos_trabalho, &pos_trabalho, "contatos_trabalho.bin");

    int opcao, agenda;
    do {
        printf("\nMenu principal\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Listar contato\n");
        printf("3 - Deletar contato\n");
        printf("4 - Alterar contato\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;
        if(opcao >= 0 && opcao <= 3) {
            printf("\nEscolha a agenda:\n");
            printf("1 - Pessoal\n");
            printf("2 - Trabalho\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &agenda);
            agenda--;

            Contato *contatos;
            int *pos;
            char *arquivo;

            if(agenda == 0) {
                contatos = contatos_pessoais;
                pos = &pos_pessoais;
                arquivo = "contatos_pessoais.bin";
            } else if(agenda == 1) {
                contatos = contatos_trabalho;
                pos = &pos_trabalho;
                arquivo = "contatos_trabalho.bin";
            } else {
                printf("Agenda invalida\n");
                continue;
            }

            ERROS erro = fs[opcao](contatos, pos);
            if(erro != OK) 
                printf("Erro ao executar a operacao: %d\n", erro);
        }
        else if(opcao == -1)
            printf("Sair...\n");
        else
            printf("Opcao invalida\n");

    } while(opcao >= 0);

    salvar(contatos_pessoais, pos_pessoais, "contatos_pessoais.bin");
    salvar(contatos_trabalho, pos_trabalho, "contatos_trabalho.bin");

    return 0;
}