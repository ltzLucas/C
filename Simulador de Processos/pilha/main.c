#include "pilha_float.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    PILHA *p1 = (PILHA*) malloc (sizeof(PILHA));
    InicializaPilha(p1);
    PILHA *pilhaAtiva = (PILHA*) malloc (sizeof(PILHA));
    InicializaPilha(pilhaAtiva);
    PILHA *pilhaEspera = (PILHA*) malloc (sizeof(PILHA));
    InicializaPilha(pilhaEspera);

    int op=0;
    

    do {
        system("pause");
        op = menuView();
        system("pause");
        system("cls");
       switch (op) {
        case 1 : //Adicionar Processo
            pilha_push(p1);
            ProcessoEmExecucao(p1,pilhaAtiva,pilhaEspera);
        break;

        case 2 ://Visualizar Pilha
            printf("-----------------\n");
            printf("|Pilha em Espera|\n");
            printf("-----------------\n");
            pilha_imprimir(pilhaEspera);
        break;

        case 3 : //Visualizar Processoss
            printf("----------------------------\n");
            printf("|Processo Atual em execucao|\n");
            printf("----------------------------\n");
            pilha_imprimir(pilhaAtiva);
           
        break;

        case 4:// Passar ciclo de execucao
            if (pilha_vazia(pilhaAtiva)) {
                printf("\nSem processos em Execucao.\n");
                break;
            }else{
                cicloExecucao(pilhaAtiva,pilhaEspera);
            }
            
        break;

        case 0://SAIR 
            
        break;

        default:
        break;
        
       }
    } while (op != 0);
    pilha_libera(p1);
    pilha_libera(pilhaAtiva);
    pilha_libera(pilhaEspera);
}

int menuView(){
    int op;
    printf("Seja bem Vindo ao Simulador de Gerenciamento de Processos\n");
    printf("-----------------------------\n");
    printf(" 1 - Adicionar um processo\n");
    printf(" 2 - Visualizar pilha\n");
    printf(" 3 - Visualizar processos\n");
    printf(" 4 - Passar ciclo de execucao\n");
    printf(" 0 - Sair\n");
    printf("-----------------------------\n");
    scanf("%d",&op);
    return op;

}

