#include "pilha_float.h"   
#include <stdio.h>    
#include <stdlib.h>                            

void  InicializaPilha(PILHA *p) {
    p->topo = NULL;
}

void pilha_push(PILHA* p) {
    NO *ptr = (NO*) malloc(sizeof(NO));

    if (ptr == NULL) {
        printf("ERRO DE ALOCACAO\n");
        return;
    }else{
        // insere o elemento na proxima posicao linear livre
        char bug;
        scanf("%c",&bug);
        printf("Informe o Nome do Processo\n");
        scanf("%c",&ptr->nome);
        printf("Informe a Prioridade do Processo\n");
        scanf("%d",&ptr->prioridade);
        printf("Informe o Tempo do Processo\n");
        scanf("%d",&ptr->tempo);
        ptr->prox = p->topo;
        p->topo = ptr;
    }
}


void pilha_pop(PILHA* p) {
    NO* ptr = p->topo;
    char nome;
    int prioridade;
    int tempo;

    if (pilha_vazia(p)) {
        printf("\nPilha vazia.\n");
        return;
    }else{
        p->topo = ptr->prox;
        ptr->prox = NULL;
        nome = ptr->nome;
        prioridade=ptr->prioridade;
        tempo = ptr->tempo;
        pilha_libera(ptr);
    }
}

int pilha_vazia(PILHA* ptr_pilha) {
    return ptr_pilha->topo == 0;
}

void pilha_libera(PILHA* ptr_pilha) {
    free(ptr_pilha);
}

void pilha_imprimir(PILHA* ptr_pilha){
    NO *ptr = ptr_pilha->topo;
    if (pilha_vazia(ptr_pilha)) {
        printf("\nPilha vazia.\n");
        return;
    }else{
        while (ptr != NULL) {
            printf("Nome: %c\n",ptr->nome);
            printf("Prioridade: %d\n",ptr->prioridade);
            printf("Tempo: %d\n",ptr->tempo);
            ptr = ptr->prox;
        }
    }
}

void ProcessoEmExecucao(PILHA* p,PILHA* pilhaAtiva,PILHA* pilhaEspera){
    NO *ptr = p->topo;
    NO *ptrAtivo = pilhaAtiva->topo;
    if (pilha_vazia(pilhaAtiva)) {
        pilha_copiar(p,pilhaAtiva);
        pilha_pop(p);
    }else{
        while (ptr != NULL) {
            if (ptr->prioridade < ptrAtivo->prioridade) {
                pilha_copiar(pilhaAtiva,pilhaEspera);//copia a pilha Ativa Para A pilha de Espera
                pilha_pop(pilhaAtiva);//tira a pilhaAtiva
                pilha_copiar(p,pilhaAtiva);//Copia oq o usuario digitou pra PilhaAtiva
                pilha_pop(p);//tira a pilhadoUsiario
            }else{
                pilha_copiar(p,pilhaEspera);
                pilha_pop(p);
            }
            ptr = ptr->prox;
        }
    }
}

void cicloExecucao(PILHA* pilhaAtiva,PILHA* pilhaEspera){
    printf("=======Antes=======\n");
    pilha_imprimir(pilhaAtiva);
    pilhaAtiva->topo->tempo = pilhaAtiva->topo->tempo - 1;
    printf("=======Depois=======\n");
    pilha_imprimir(pilhaAtiva);
    if (pilhaAtiva->topo->tempo == 0) {
        pilha_pop(pilhaAtiva);
        adicionaNoCiclo(pilhaEspera,pilhaAtiva);
    }
}

void adicionaNoCiclo(PILHA* pilhaEspera,PILHA* pilhaAtiva) {
    NO *ptr = pilhaEspera->topo;
    NO *aux = (NO*) malloc(sizeof(NO));

    aux->nome = ptr->nome;
    aux->prioridade = ptr->prioridade;
    aux->tempo = ptr->tempo;

    aux->prox = pilhaAtiva->topo;
    pilhaAtiva->topo = aux;
    
    pilha_pop(pilhaEspera);

}

void pilha_copiar(PILHA* original,PILHA* pilhaCopia){
    NO *ptr = original->topo;
    NO *copia = (NO*) malloc(sizeof(NO));
   
    copia->nome = ptr->nome;
    copia->prioridade = ptr->prioridade;
    copia->tempo = ptr->tempo;

    copia->prox = pilhaCopia->topo;
    pilhaCopia->topo = copia;
}