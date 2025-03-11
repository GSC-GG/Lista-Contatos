#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaligada.h"


int main() {
    char op;
    FILE *f;
    Lista *li = NULL;

    li = criaLista();
    if (li == NULL) {
        abortaPrograma();
    }


    f = fopen("contatos.txt", "rb");
    if(f == NULL){
        system("CLS");
        printf("\nNao foram encontrados contatos salvos.\n\n");
    }else{
        carregaClientes(li, f);
        system("CLS");
        printf("\nContatos salvos carregados corretamente.\n\n");
    }
    fclose(f);


    do{
        fflush(stdin);
        op = menu();
        switch(op){
            case '1':
                inserirCliente(li);
                break;
            case '2':
                exibeTudo(li);
                break;
            case '3':
                listaIndividual(li);
                break;
            case '4':
                buscaNome(li);
                break;
            case '5':
                alteraCliente(li);
                break;
            case '6':
                removeCliente(li);
                break;
            case '7':
                encerraPrograma(li);
                break;
            default:
                printf("\nOpcao nao existente");
                break;
        }
        system("pause");
        system("CLS");
    }while(op != '7');

    apagaLista(li);
    return 0;
}
