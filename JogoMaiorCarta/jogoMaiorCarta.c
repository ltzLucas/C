
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define quantidadeCartasIniciais 5


struct carta {
    int id;
    int numero;
    char naipe;
    int utilizada;
           
};
struct jogador {
    int contadorPontosJogador;
    int jogarNovamente;
    struct carta listaCartaJogador[5];
};
struct computador {
    int contadorPontosComputador;
    struct carta listaCartaComputador[5];
};

struct carta baralho[52];
struct jogador jogador;
struct computador computador;

int aux1 = 0;
int contadorCartasDist = 0;
void carregarJogo();
void criarJogador();
void criarComputador();

void criarCartas();
void embaralharCartas();

void mostrarTodasCartas();
void mostrarCartasJogadores(struct carta listaCartaJogador[],struct carta listaCartaComputador[]);
int mostrarCartaJogador();
void mostrarCartaComputador(int i);
void mostrarCarta(struct carta carta);

void mostrarCartaGrandes(struct carta listaCartaComputador[],int i);

void avaliacaoRodada(int i);

void verificacaoGanhador();

void requisitarCartasIniciais();
void requisitarCartaJogador();
void requisitarCartaComputador();

int main(){
    int resposta = 1;
    srand(time(NULL));
    carregarJogo();
    requisitarCartasIniciais();

    while (resposta == 1) {
        mostrarCartasJogadores(jogador.listaCartaJogador,computador.listaCartaComputador);

        system("pause");
        
        verificacaoGanhador();

        
        printf("\n\n\nDeseja jogar mais uma vez? 'Digite 1 para jogar ou 0 para encerrar o programa'\n");
        scanf("%i",&resposta);
        system("cls");
        }
    

    return 0;
}





void criarCartas() {
    char listaNaipe[] = {'p', 'c', 'e', 'o'};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            int index =  13*i + j;

            struct carta carta = baralho[index];

            carta.id = index;
            carta.numero = j + 2;
            carta.naipe = listaNaipe[i];
            

            baralho[index] = carta;
        }
    }
}
void embaralharCartas() {

    struct carta baralhoEmbaralhado[52];

    int contador = 0; 
    while (contador < 52) {
        int NumeroSorteado = rand() % 52;

        int CartaJaEmbaralhada = 0;
        for (int i = 0; i < 52; i++) {
            if (baralhoEmbaralhado[i].id == NumeroSorteado) {
                CartaJaEmbaralhada = 1;
                break;
            }
        }

        if (CartaJaEmbaralhada == 0) {
            baralhoEmbaralhado[contador] = baralho[NumeroSorteado];
            contador++;
        }
    }

    for (int i = 0; i < 52; i++) {
        baralho[i] = baralhoEmbaralhado[i];
    }
}

void mostrarTodasCartas() {
    for (int i = 0; i < 52; i++) {
        mostrarCarta(baralho[i]);
    }
}
void mostrarCartasJogadores(struct carta listaCartaJogador[],struct carta listaCartaComputador[]) {
    printf("----------------------------\n");
    printf("Vamos comecar o jogo!!\n");
    printf("O computador joga primeiro\n");
    printf("----------------------------\n");
    for (int i = 0; i < 5; i++) {
        mostrarCartaComputador(i);
        mostrarCartaJogador();
        avaliacaoRodada(i);
        system("pause");
        system("cls");
    }
}
void mostrarCartaComputador(int i){
    /*printf("============================\n");
    printf("Carta do Computador: %i %c\n",computador.listaCartaComputador[i].numero,computador.listaCartaComputador[i].naipe);
    printf("============================\n");
    */
   mostrarCartaGrandes(computador.listaCartaComputador,i);
}
int mostrarCartaJogador(){
    int escolhaDaCarta;
    printf("============================\n");
    printf("As suas cartas sao:\n\n");

    for (int i = 0; i < 5; i++) {
        if (jogador.listaCartaJogador[i].utilizada == 0) {
        printf("Carta numero %i: %i %c\n",i + 1, jogador.listaCartaJogador[i].numero,jogador.listaCartaJogador[i].naipe);
        }
        
    }

    printf("\nEscolha uma das cartas para ser jogada, escolhendo o numero da carta\n");
    scanf("%i",&escolhaDaCarta);

    //VERIFICAÇÃO SE A CARTA ESCOLHIDA ESTA VALIDA AINDA
    if (escolhaDaCarta > 5 || escolhaDaCarta < 1) {
        while (escolhaDaCarta > 5 || escolhaDaCarta < 1) {
            printf("Numero escolhido da carta invalido tente novamente:\n");
            scanf("%i",&escolhaDaCarta);
            
        }
    }
    if (jogador.listaCartaJogador[escolhaDaCarta - 1].utilizada == 1) {
        while (jogador.listaCartaJogador[escolhaDaCarta - 1].utilizada == 1) {
            printf("Esta carta ja foi escolhida tente novamente:\n");
            scanf("%i",&escolhaDaCarta);
        }
    }
    
    
    aux1 = escolhaDaCarta - 1 ;
    jogador.listaCartaJogador[escolhaDaCarta - 1].utilizada = 1; //se for = 1 já foi utilizada
    printf("Carta Escolhida: %i %c\n",jogador.listaCartaJogador[aux1].numero,jogador.listaCartaJogador[aux1].naipe);
    return aux1;
}


void avaliacaoRodada(int i){
    if (computador.listaCartaComputador[i].numero > jogador.listaCartaJogador[aux1].numero) {
       if (computador.listaCartaComputador[i].naipe == jogador.listaCartaJogador[aux1].naipe ) {

           computador.contadorPontosComputador = computador.contadorPontosComputador + 2;
            i++;
        }
        else {
            computador.contadorPontosComputador = computador.contadorPontosComputador + 1;
            i++;
        }
    }
    else if (computador.listaCartaComputador[i].numero < jogador.listaCartaJogador[aux1].numero) {
        if (computador.listaCartaComputador[i].naipe == jogador.listaCartaJogador[aux1].naipe ) {

            jogador.contadorPontosJogador = jogador.contadorPontosJogador + 2;
            i++;
        }
        else{
            jogador.contadorPontosJogador = jogador.contadorPontosJogador + 1;
            i++;
        }
    }
    else {
        printf("Essa rodada deu empate, ambos jogadores nao ganham pontos");
        i++;
    }

    printf("\n======================\t");
    printf("======================\n");
    printf("||                  ||\t");
    printf("||                  ||\n");
    printf("|| Pontos Comp:%i    ||\t",computador.contadorPontosComputador);
    printf("|| Pontos Joga:%i    ||\n",jogador.contadorPontosJogador);
    printf("||                  ||\t");
    printf("||                  ||\n");
    printf("======================\t");
    printf("======================\n");
}

void verificacaoGanhador(){
    if (jogador.contadorPontosJogador > computador.contadorPontosComputador) {
        system("cls");
        printf("\n                        Parabens voce ganhou!!\n");  
    }
    else if (jogador.contadorPontosJogador < computador.contadorPontosComputador) {
        system("cls");
        printf("\n                           VOCE PERDEU!!\n");
    }
    else if (jogador.contadorPontosJogador == computador.contadorPontosComputador) {
        system("cls");
        printf("\n                             Empatou!!\n");   
    }
     
    
}





void mostrarCarta(struct carta carta) {
    printf("id: %i\t", carta.id);
    printf("numero: %i\t", carta.numero);
    printf("naipe: %c\n", carta.naipe);
}

void carregarJogo() {
    
    criarCartas();
    mostrarTodasCartas();

    system("pause");
    embaralharCartas();
    mostrarTodasCartas();

    system("pause");
    system("cls");

    criarJogador();
    criarComputador();
}

void criarJogador() {
    struct jogador jogador;

    struct carta listaCartaInicial[quantidadeCartasIniciais];
    requisitarCartasIniciais;
}
void criarComputador() {
    struct computador computador;

    struct carta listaCartaInicial[quantidadeCartasIniciais];
    requisitarCartasIniciais;
}


void requisitarCartaJogador() {
    for (int i = 0; i < 5; i++) {
       jogador.listaCartaJogador[i].numero = baralho[i].numero;
       jogador.listaCartaJogador[i].naipe = baralho[i].naipe;
    }
}
void requisitarCartaComputador() {
    for (int j = 10; j < 15; j++) {
       computador.listaCartaComputador[j-10].numero = baralho[j].numero;
       computador.listaCartaComputador[j-10].naipe = baralho[j].naipe;
    }
}
void requisitarCartasIniciais() {    
 
    requisitarCartaJogador();
    requisitarCartaComputador();
}

void mostrarCartaGrandes(struct carta listaCartaComputador[],int i) {

    //------------------------------------CARTAS COM NUMERO DE DOIS DIGITOS--------------------------

    if (computador.listaCartaComputador[i].numero > 10) {
        for (int i = 0; i < 11; i++) {
        printf(" -");  
        }

        printf("\n");
        
        printf("|   %i%c              |\n",computador.listaCartaComputador[i].numero,computador.listaCartaComputador[i].naipe);
        
        printf("|   --------------   |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |      %c       |  |\n",computador.listaCartaComputador[i].naipe);
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|   --------------   |\n");
            

        printf("|               %i%c  |\n",computador.listaCartaComputador[i].numero,computador.listaCartaComputador[i].naipe);
        printf("|                    |\n");
        
        printf(" ");
        for (int i = 0; i < 11; i++) {
            printf(" -");
        }
        printf ("\n");

    }
    
    //------------------------------------CARTAS COM NUMERO DE UM DIGITO--------------------------
    else {
        for (int i = 0; i < 11; i++) {
            printf(" -");  
        }
        printf("\n");
        
        printf("|   %i%c               |\n",computador.listaCartaComputador[i].numero,computador.listaCartaComputador[i].naipe);
        
        printf("|   --------------   |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |      %c       |  |\n",computador.listaCartaComputador[i].naipe);
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|  |              |  |\n");
        printf("|   --------------   |\n");
            

        printf("|               %i%c   |\n",computador.listaCartaComputador[i].numero,computador.listaCartaComputador[i].naipe);
        printf("|                    |\n");
        
        printf(" ");
        for (int i = 0; i < 11; i++) {
            printf(" -");
        }
        printf ("\n");

    }

}


