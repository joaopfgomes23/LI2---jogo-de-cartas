#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <assert.h>

typedef enum {
    ESPADAS = 0x1F0A0,
    OUROS = 0x1F0B0,
    COPAS = 0x1F0C0,
    PAUS = 0x1F0D0
} NAIPE;

typedef enum {
    A = 0x1,
    DOIS = 0x2,
    TRES = 0x3,
    QUATRO = 0x4,
    CINCO = 0x5,
    SEIS = 0x6,
    SETE = 0x7,
    OITO = 0x8,
    NOVE = 0x9,
    DEZ = 0xA,
    J = 0xB,
    C = 0xC,
    Q = 0xD,
    K = 0xE
} VALOR;

NAIPE naipe(wchar_t carta) {
    return (NAIPE)(carta & 0xF0);
}

VALOR valor(wchar_t carta) {
    return (VALOR)(carta & 0xF);
}

typedef struct {
    char valor;
    char naipe;
    wchar_t carta;
} Carta;

// Transforma o wchar da carta para o seu valor e naipe 
void transforma_mao(wchar_t mao[], int tamanho, Carta resultados[]){
    wchar_t primeira_carta = 0x1F0A0;

    for (int i=0; i<tamanho; i++){
        wchar_t carta = mao[i];
        int novacarta = carta - primeira_carta;
        int naipe = (novacarta / 16) + 1;
        int valor = novacarta % 16;

        resultados[i].naipe = naipe;
        resultados[i].valor = valor;
        resultados[i].carta = carta;
    }
}

// Troca a ordem das cartas de forma a ficar organizada
void troca_cartas(Carta* cartaA, Carta* cartaB){
    Carta temp = *cartaA;
    *cartaA = *cartaB;
    *cartaB = temp;
}

// Verifica se a sequencia esta em ordem e se nao estiver usa a funçao troca_cartas para organizar a sequencia
void organiza(Carta resultados[], int tam_mao){
    for (int i= 0; i<tam_mao-1; i++){
        for (int j = 0; j<tam_mao-i-1; j++){
            if (resultados[j].valor>resultados[j+1].valor ||
                (resultados[j].valor == resultados[j+1].valor && resultados[j].naipe > resultados[j+1].naipe)){
                    troca_cartas(&resultados[j], &resultados [j+1]);
                }
        }
    }
}

// Compara as cartas 
int comparar(const void *a, const void *b) {
    Carta *cartaA = (Carta *)a;
    Carta *cartaB = (Carta *)b;

    if (cartaA->valor == cartaB->valor)
        return cartaB->naipe - cartaA->naipe;
    else
        return cartaB->valor - cartaA->valor; 
}

//verifica se é um conjunto
bool verificar_conjunto(Carta *resultados, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        if (resultados[i].valor != resultados[0].valor)
            return false;
    }
    return true;
}

// verifica se é uma sequencia
bool verificar_sequencia(Carta *resultados, int tamanho) {
    if(tamanho <= 2) return false;
    else for (int i = 0; i < tamanho - 1; i++) {
          if (resultados[i +1].valor - resultados[i].valor != 1)
            return false;
    }
    return true;
}

// verifica se é dupla sequencia
bool verificar_dupla_sequencia(Carta *resultados, int tamanho) {
    if(tamanho <= 5) return false;
    for (int i = 0; i < tamanho - 3; i+=2) {
        int valor1=resultados[i].valor;
        int valor2=resultados[i+1].valor;
        int valor3=resultados[i+2].valor;
        int valor4=resultados[i+3].valor;
        if (valor1 != valor2 || valor2+1 != valor3 || valor1+1!=valor3 || valor3!=valor4) return false;
    }
    return true;
}

// imprime o tipo de mao
void imprimir_tipo_mao(wchar_t mao[], Carta *resultados, int tam_mao) {
    transforma_mao(mao, tam_mao, resultados);
    organiza(resultados, tam_mao);
    int maiorCarta = tam_mao -1;

    if (verificar_conjunto(resultados, tam_mao)) {
        wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n", tam_mao, resultados[maiorCarta].carta);
    } else if (verificar_sequencia(resultados, tam_mao)) {
        wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n", tam_mao, resultados[maiorCarta].carta);
    } else if (verificar_dupla_sequencia(resultados, tam_mao)) {
        wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n", tam_mao/2, resultados[maiorCarta].carta);
    } else {
        wprintf(L"Nada!\n");
    }
}

int main() {
    int T;
    setlocale(LC_CTYPE, "C.UTF-8");
    assert(scanf("%d ", &T)==1); 
    Carta resultados[T][100];
    wchar_t mao[T][100];

    for (int i = 0; i < T; i++) {
        if(scanf("%ls", mao[i]) != 1){
        }
    }

    for (int i = 0; i < T; i++) {
        int tam_mao = wcslen(mao[i]); 
        imprimir_tipo_mao(mao[i], resultados[i], tam_mao); 
    }

    return 0;
}
