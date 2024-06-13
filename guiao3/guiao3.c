#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

// funçao que diz o valor da carta
int valor(wchar_t carta){
    wchar_t primeira_carta = 0x1F0A0;
    int valor = (carta - primeira_carta) % 16;
    return valor;
}

// funçao que diz o naipe da carta
wchar_t naipe(wchar_t carta) {
    wchar_t simbolos[] = {0x1F0A0, 0x1F0B0, 0x1F0C0, 0x1F0D0};
    wchar_t valores[] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++) {
        if (carta >= simbolos[i] && carta < simbolos[i] + 16) {
            return valores[i];
        }
    }
    return 0;
}

// funçao que troca as cartas, usada na funçao organiza
void troca_cartas(wchar_t *cartaA, wchar_t *cartaB){
    wchar_t temp = *cartaA;
    *cartaA = *cartaB;
    *cartaB = temp;
}

// funçao que organiza a sequencia por ordem crescente
void organiza(wchar_t resultados[], int tam_mao){
    for (int i = 0; i < tam_mao - 1; i++) {
        for (int j = 0; j < tam_mao - i - 1; j++) {
            int valorA = valor(resultados[j]);
            int valorB = valor(resultados[j + 1]);

            if (valorA > valorB || (valorA == valorB && naipe(resultados[j]) > naipe(resultados[j + 1]))) {
                troca_cartas(&resultados[j], &resultados[j + 1]);
            }
        }
    }
}

// funçao que verifica se é conjunto
bool verificar_conjunto(wchar_t s[]) {
    int valorBase = valor(s[0]);
    for (int i = 1; s[i] != L'\0'; i++) {
        if (valor(s[i]) != valorBase) return false;
    }
    return true;
}

//funcao apra verificar se é sequencia
bool verificar_sequencia(int s[], int size) {
    if (size <= 2) return false;
    for (int i = 1; i < size; i++) {
        if (s[i] != s[i - 1] + 1) return false;
    }
    return true;
}

//funcao para verificar se a sequencia é dupla sequencia
bool verificar_duplaSequencia(int s[], int size) {
    if (size <= 5) return false;
    for (int i = 0; i < size - 3; i+=2) {
        int valor1 = s[i];
        int valor2 = s[i+1];
        int valor3 = s[i+2];
        int valor4 = s[i+3];
        if (valor1 != valor2 || valor2+1 != valor3 || valor1+1!=valor3 || valor3!=valor4) return false;
    }
    return true;
}

// Verificar o tipo de combinação da jogada atual
int obterTipoCombinacao(wchar_t combinacao[], int tam_combinacao) {
    int valoresCombinacao[tam_combinacao];
    for (int i = 0; i < tam_combinacao; i++) {
        valoresCombinacao[i] = valor(combinacao[i]);
    }

    if (verificar_conjunto(combinacao)) {
        return 1;
    } else if (verificar_sequencia(valoresCombinacao, tam_combinacao)) {
        return 2;
    } else if (verificar_duplaSequencia(valoresCombinacao, tam_combinacao)) {
        return 3;
    }
    return 0;
}

void determinarUltimaJogada(wchar_t sequencias[][20], int linhas, wchar_t ultimaJogada[]) {
    if (linhas == 0) {
        ultimaJogada[0] = L'\0';
        return;
    } else wcscpy(ultimaJogada, sequencias[linhas-1]);

    if (wcscmp(sequencias[linhas - 1], L"PASSO") == 0) {
        int countPasso = 0;
        for (int i = linhas - 1; i >= 0; i--) {
            if (wcscmp(sequencias[i], L"PASSO") == 0) {
                countPasso++;
            } else {
                break;
            }
        }
        if (countPasso >= 3) {
            wcscpy(ultimaJogada, L"PASSO");
        } else if (countPasso == 2){
            wcscpy(ultimaJogada, sequencias[linhas - 3]);
        } else if (countPasso == 1){
            wcscpy(ultimaJogada, sequencias[linhas - 2]);
        } 
    }
}

bool verificarCombinacaoValida(wchar_t jogada[], wchar_t ultimaJogada[]) {
    int tipoAnterior;

    if (ultimaJogada[0] == L'\0') {
        tipoAnterior = 0;
    } else {
        tipoAnterior = obterTipoCombinacao(ultimaJogada, wcslen(ultimaJogada));
    }
    int tipoJogada = obterTipoCombinacao(jogada, wcslen(jogada));

    // Se a última jogada for vazia ou não houver uma última jogada, qualquer jogada é válida
    if (ultimaJogada[0] == L'\0' || tipoAnterior == 0) {
        return tipoJogada != 0;
    }

    // A jogada é válida se tiver o mesmo tipo de combinação que a última jogada
    return tipoJogada == tipoAnterior;
}

bool verificarReis(wchar_t ultimaJogada[], wchar_t jogada[]) {
    int tam_ultimaJogada = wcslen(ultimaJogada);
    int tam_jogada = wcslen(jogada);
    int valoresUltimaJogada[tam_ultimaJogada];
    for (int i = 0; i < tam_ultimaJogada; i++) {
        valoresUltimaJogada[i] = valor(ultimaJogada[i]);
    }

    // Verificar se a última jogada contém um Rei
    int countReis = 0;
    for (int i = 0; i < tam_ultimaJogada; i++) {
        if (valoresUltimaJogada[i] == 14) { // 14 é o valor do Rei
            countReis++;
        }
    }

    // Verificar as regras dos Reis
    if (countReis > 0) {
        // Condições para jogadas com um Rei
        if (countReis == 1 && tam_ultimaJogada == 1) {
            if (tam_jogada == 4 && obterTipoCombinacao(jogada, tam_jogada) == 1) {
                return true;
            }
        }
        // Condições para jogadas com dois Reis
        else if (countReis == 2 && tam_ultimaJogada == 2) {
            if (tam_jogada == 8 && obterTipoCombinacao(jogada, tam_jogada) == 3) {
                return true;
            }
        }
        // Condições para jogadas com três Reis
        else if (countReis == 3 && tam_ultimaJogada == 3) {
            if (tam_jogada == 10 && obterTipoCombinacao(jogada, tam_jogada) == 3) {
                return true;
            }
        }
    }

    return false;
}

void removerCartas(wchar_t mao[], wchar_t jogada[], int tam_mao, int tam_jogada) {
    for (int i = 0; i < tam_jogada; i++) {
        for (int j = 0; j < tam_mao; j++) {
            if (jogada[i] == mao[j]) {
                for (int k = j; k < tam_mao - 1; k++) {
                    mao[k] = mao[k + 1];
                }
                mao[tam_mao - 1] = L'\0';
                tam_mao--;
                break;
            }
        }
    }
}

bool verificaMaior(wchar_t jogada[], wchar_t ultimaJogada[]){
    int tam_jogada = wcslen(jogada);
    int tam_ultimajogada = wcslen(ultimaJogada);
    if(tam_ultimajogada != 0 && wcscmp(ultimaJogada, L"PASSO") != 0){
        if(valor(jogada[tam_jogada-1])>valor(ultimaJogada[tam_ultimajogada-1])){
            return true;
        } else if (valor(jogada[tam_jogada-1])==valor(ultimaJogada[tam_ultimajogada-1]) && naipe(jogada[tam_jogada-1])>naipe(ultimaJogada[tam_ultimajogada-1])){
            return true;
        }
        return false;
    }
    return true;
}

bool verificaTamanho(wchar_t jogada[], wchar_t ultimaJogada[]){
    int tam_jogada = wcslen(jogada);
    int tam_ultimajogada = wcslen(ultimaJogada);

    if(tam_ultimajogada != 0 && wcscmp(ultimaJogada, L"PASSO") != 0){
        if (tam_jogada!= tam_ultimajogada) return false;
    }
    return true;
}

void output(wchar_t mao[],wchar_t jogada[],wchar_t ultimaJogada[]){
        organiza(jogada, wcslen(jogada));
        if (verificarCombinacaoValida(jogada, ultimaJogada) && verificaMaior(jogada, ultimaJogada) && verificaTamanho(jogada,ultimaJogada)) {
            removerCartas(mao, jogada, wcslen(mao), wcslen(jogada));
        } else if (verificarReis(ultimaJogada, jogada)){
            removerCartas(mao, jogada, wcslen(mao), wcslen(jogada));
        }
        
        organiza(mao, wcslen(mao));
        for (int k = 0; mao[k] != L'\0'; k++) {
            wprintf(L"%lc", mao[k]);
            if (mao[k + 1] != L'\0') {
                wprintf(L" ");
            }
        }
        wprintf(L"\n");
}

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    int testes;
    wscanf(L"%d", &testes);

    for (int i = 0; i < testes; i++) {
        wprintf(L"Teste %d\n", i + 1);
        int linhas;
        wscanf(L"%d", &linhas);

        wchar_t mao[20];
        wscanf(L"%ls", mao);

        wchar_t sequencias[1000][20];
        for (int j = 0; j < linhas; j++) {
            wscanf(L"%ls", sequencias[j]);
        }

        wchar_t jogada[20];
        if (wscanf(L"%ls", jogada) == 0) {
            wprintf(L"entrou\n");
        }

        wchar_t ultimaJogada[20] = L"";
        determinarUltimaJogada(sequencias, linhas, ultimaJogada); 
        wprintf(L"%ls - %ls\n" ,mao, jogada);

        output(mao, jogada, ultimaJogada);
    }

    return 0;
}
