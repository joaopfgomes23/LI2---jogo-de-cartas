#include "projetoli2.h"

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    int linhas;
    wscanf(L"%d", &linhas); // scan do numero de jogadas anteriores 

    wchar_t mao[20];
    wscanf(L"%ls", mao); // scan da mao do jogador

    wchar_t sequencias[1000][20];
    for (int j = 0; j < linhas; j++) {
        wscanf(L"%ls", sequencias[j]); // scan das jogadas anteriores da primeira até a ultima
    }

    wchar_t ultimaJogada[20] = L"";
    determinarUltimaJogada(sequencias, linhas, ultimaJogada); // chamada da funçao para descobrir a ultima jogada

    organiza(mao, wcslen(mao)); // chamada da funçao para organizar a mao do jogador de forma a facilitar a geraçao de combinaçoes 
    output(mao, ultimaJogada); // output

    return 0;
}
