#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define quantidadeCartasIniciais 2
#define quantidadeCartasPequenasPorLinha 7

struct Carta {
    int id;
    int valor;
    int numero;
    char naipe;
};
struct Jogador {
    int aposta;
    struct Carta listaCarta[9];
    int quantidadeCartas;
};
struct InformacoesCabecalho {
    int numeroRodada;
    struct Carta carta;
    int valorTotalJogador;
};


int numeroRodada = 1;
int indexProximaCarta = 0;

struct Carta baralho[52];
struct Jogador jogador;

void carregarJogo(); 

void criarJogador();
void criarCartas();
void embaralharCartas();

int somarValorCartas(struct Carta listaCarta[9]);

void mostrarListaCarta(struct Carta listaCarta[], int quantidade);
void mostrarLinhaCarta(struct Carta listaCarta[], int quantidade);

void mostrarRegrasJogo();

void construirCabecalho();
void mostrarCabecalho(struct InformacoesCabecalho informacoes);

void requisitarCarta();
void requisitarCartasIniciais();
int validarStatusJogo();
int perguntarRequisicaoCarta();

void ConstruirMensagemResultado();

int main() {
    carregarJogo(); 
    mostrarRegrasJogo();

    int resposta = 1;
    int statusJogo = 0;
    while (statusJogo == 0 && resposta == 1) {
        construirCabecalho();

        resposta = perguntarRequisicaoCarta();
        if (resposta == 1) {
            requisitarCarta();
        }

        numeroRodada++;
        statusJogo = validarStatusJogo();
    }

    ConstruirMensagemResultado();
    return 0;
}

void carregarJogo() {
    srand(time(NULL));

    criarCartas();
    printf("===========================================\n");
    printf("         TODAS AS CARTAS DO BARALHO        \n");
    printf("===========================================\n");
    
    mostrarListaCarta(baralho, 52);
    printf("\n");
    system("pause");
    
    embaralharCartas();
    printf("===========================================\n");
    printf("        TODAS AS CARTAS EMBARALHADAS       \n");
    printf("===========================================\n");
    
    mostrarListaCarta(baralho, 52);
    
    printf("\n");
    system("pause");
    system("cls");

    criarJogador();
}

void criarJogador() {
    jogador.quantidadeCartas = 0;
    requisitarCartasIniciais();
}
void criarCartas() {
    char listaNaipe[] = {'p', 'c', 'e', 'o'};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            int index =  13*i + j;

            struct Carta carta;

            carta.id = index;
            carta.numero = j + 2;
            carta.naipe = listaNaipe[i];
            carta.valor = carta.numero <= 10 ? carta.numero : 10;

            baralho[index] = carta;
        }
    }
}
void embaralharCartas() {
    struct Carta baralhoEmbaralhado[52];

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

int somarValorCartas(struct Carta listaCarta[]) {
    int soma = 0;
    
    for (int i = 0; i < jogador.quantidadeCartas; i++) {
        soma += listaCarta[i].valor;
    }

    return soma;
}

void mostrarListaCarta(struct Carta listaCarta[], int quantidade) {
    int quantidadeMostrada = 0;

    int quantidadeLinha = quantidade / quantidadeCartasPequenasPorLinha;
    
    for (int i = 0; i < quantidade; i += quantidadeCartasPequenasPorLinha) {
        struct Carta listaCartaLinha[quantidadeCartasPequenasPorLinha]; 
        
        int ultimaCartaLinha = i + quantidadeCartasPequenasPorLinha >= quantidade - 1 ? quantidade : i + quantidadeCartasPequenasPorLinha;   
        for (int j = i; j < ultimaCartaLinha; j++) {
            listaCartaLinha[j - i] = listaCarta[j];
        }
        
        mostrarLinhaCarta(listaCartaLinha, ultimaCartaLinha - i);
    }
}

void mostrarLinhaCarta(struct Carta listaCarta[], int quantidade) {
    char espacoAuxiliar[2];

    char linhaLimiteHorizontal[]    = " ------  ";
    char linhaInformacoesTopo[]     = "| %i%c%s | ";
    char linhaMeio[]                = "|      | ";
    char linhaInformacoesInferior[] = "| %s%i%c | ";

    printf("\n");
    for (int i = 0; i < quantidade; i++) {
        printf(linhaLimiteHorizontal);
    }
    
    printf("\n");
    for (int i = 0; i < quantidade; i++) {
        if (listaCarta[i].numero < 10) 
            strcpy(espacoAuxiliar, "  ");
        else 
            strcpy(espacoAuxiliar, " ");
        
        printf(linhaInformacoesTopo, listaCarta[i].numero, listaCarta[i].naipe, espacoAuxiliar);
    }
    
    printf("\n");
    for (int i = 0; i < quantidade; i++) {
        printf(linhaMeio);
    }
    
    printf("\n");
    for (int i = 0; i < quantidade; i++) {
        printf(linhaMeio);
    }
    
    printf("\n");
    for (int i = 0; i < quantidade; i++) {
        if (listaCarta[i].numero < 10) 
            strcpy(espacoAuxiliar, "  ");
        else 
            strcpy(espacoAuxiliar, " ");
        
        printf(linhaInformacoesInferior, espacoAuxiliar, listaCarta[i].numero, listaCarta[i].naipe);
    }

    printf("\n");
    for (int i = 0; i < quantidade; i++) {
        printf(linhaLimiteHorizontal);
    }
}

void mostrarRegrasJogo() {
    printf("----------------------------------------\n");
    printf("Seja bem vindo ao jogo de 21\n");
    printf("Voce recebera 3 cartas de inicio\n");
    printf("Voce devera somar essas 3 cartas e verificar se vale apena pedir mais uma ou nao\n");
    printf("Voce ganha se ao somar as cartas encontre na soma o numero 21\n");
    printf("Se vc atinja a soma de 19 ou 20 pontos vc recebe o valor apostado\n");
    printf("Caso vc atinja 21, vc dobra a sua aposta\n");
    printf("Caso contrario vc perde o valor apostado\n");
    printf("VAMOS COMECAR\n");
    printf("-----------------------------------------\n");
    printf("Lista das cartas iniciais: \n");

    mostrarListaCarta(jogador.listaCarta, jogador.quantidadeCartas);
    printf("\n");
    system("pause");
}

void construirCabecalho() {
    struct InformacoesCabecalho informacoes;
    informacoes.numeroRodada = numeroRodada;
    informacoes.carta = jogador.listaCarta[indexProximaCarta - 1];
    informacoes.valorTotalJogador = somarValorCartas(jogador.listaCarta);

    mostrarCabecalho(informacoes);
}
void mostrarCabecalho(struct InformacoesCabecalho informacoes) {
    system("cls");

    printf("Ultima carta dada:");
    mostrarListaCarta(&informacoes.carta, 1);
    printf("\n");
    
    printf("-----------------------------------------\n");
    printf("Rodada: %i\n", informacoes.numeroRodada);
    printf("A carta dada ao usuario: %i%c\n", informacoes.carta.numero, informacoes.carta.naipe);
    printf("Valor da carta: %i\n", informacoes.carta.valor);
    printf("Valor total: %i\n", informacoes.valorTotalJogador);
    printf("-----------------------------------------\n");
}

void requisitarCarta() {
    jogador.listaCarta[indexProximaCarta] = baralho[indexProximaCarta];
    jogador.quantidadeCartas++;
    indexProximaCarta++; 
}
void requisitarCartasIniciais() {    
    for (int i = 0; i < quantidadeCartasIniciais; i++) {
        requisitarCarta();
    }
}

int perguntarRequisicaoCarta() {
    char resposta;
    
    printf("Deseja mais uma carta? [Y/n]\n");
    gets(&resposta);

    return resposta == 'Y' || resposta == 'y' ? 1 : 0;
}

int validarStatusJogo() {
    int pontuacaoTotal = somarValorCartas(jogador.listaCarta);

    if (pontuacaoTotal < 19) {
        return 0;
    }

    if (pontuacaoTotal > 21) {
        return 1;
    }

    if (pontuacaoTotal == 19 || pontuacaoTotal == 20) {
        return 2;
    }    

    return 3;
}

void ConstruirMensagemResultado() {
    int pontuacaoTotal = somarValorCartas(jogador.listaCarta);
    char mensagem[100];
    
    if (pontuacaoTotal < 21 && jogador.quantidadeCartas > quantidadeCartasIniciais) {
        strcpy(mensagem, "Voce perdeu");
    }

    if (pontuacaoTotal < 19) {
        strcpy(mensagem, "nao ganhou nem perdeu");
    }

    if (pontuacaoTotal == 19 || pontuacaoTotal == 20) {
        strcpy(mensagem, "Voce ganhou o valor da aposta");
    }

    if (pontuacaoTotal == 21) {
        strcpy(mensagem, "Voce ganhou o dobro do valor da aposta");
    }
    
    if (pontuacaoTotal > 21) {
        strcpy(mensagem, "Voce perdeu o valor da aposta");
    }

    construirCabecalho();
    printf("Todas as cartas dadas ao jogador:");
    mostrarListaCarta(jogador.listaCarta, jogador.quantidadeCartas);

    printf("\n%s", mensagem);
}
