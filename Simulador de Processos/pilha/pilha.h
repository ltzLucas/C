typedef struct NO{
    char nome;
    int prioridade;
    int tempo;
    struct NO *prox;
}NO;
typedef struct pilha {
    NO *topo;
} PILHA;


void  InicializaPilha(PILHA *p);
void pilha_push(PILHA* p);
void pilha_pop(PILHA* p);
int pilha_vazia(PILHA* ptr_pilha);
void pilha_libera(PILHA* ptr_pilha);
void pilha_imprimir(PILHA* ptr_pilha);
void ProcessoEmExecucao(PILHA* p,PILHA* pilhaAtiva,PILHA* pilhaEspera);
void cicloExecucao(PILHA* pilhaAtiva,PILHA* pilhaEspera);
void adicionaNoCiclo(PILHA* pilhaAtiva,PILHA* pilhaEspera);

void pilha_copiar(PILHA* original,PILHA* pilhaCopia);
//==========================================================//
