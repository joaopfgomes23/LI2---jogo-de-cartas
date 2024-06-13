#include "projetoli2.h"

// funçao que descobre o valor da carta
int valor(wchar_t carta) {
    wchar_t primeira_carta = 0x1F0A0;
    return (carta - primeira_carta) % 16;
}

// funçao que descobre o naipe da carta
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

// funçao para torcar as cartas
void troca_cartas(wchar_t *cartaA, wchar_t *cartaB) {
    wchar_t temp = *cartaA;
    *cartaA = *cartaB;
    *cartaB = temp;
}

// funçao que organiza as cartas por ordem crescente usando a funçao troca cartas
void organiza(wchar_t resultados[], int tam_mao) {
    bool trocou = true;
    for (int i = 0; i < tam_mao - 1 && trocou; i++) {
        trocou = false;
        for (int j = 0; j < tam_mao - i - 1; j++) {
            int valorA = valor(resultados[j]);
            int valorB = valor(resultados[j + 1]);

            if (valorA > valorB || (valorA == valorB && naipe(resultados[j]) > naipe(resultados[j + 1]))) {
                troca_cartas(&resultados[j], &resultados[j + 1]);
                trocou = true;
            }
        }
    }
}

// funçao para verificar se a combinaçao é conjunto
bool verificar_conjunto(wchar_t s[]) {
    int valorBase = valor(s[0]);
    for (int i = 1; s[i] != L'\0'; i++) {
        if (valor(s[i]) != valorBase) return false;
    }
    return true;
}

// funçao para verificar se a combinaçao é sequencia
bool verificar_sequencia(int s[], int size) {
    if (size <= 2) return false;
    for (int i = 1; i < size; i++) {
        if (s[i] != s[i - 1] + 1) return false;
    }
    return true;
}

// funçao para verificar se a combinaçao é dupla sequencia
bool verificar_duplaSequencia(int s[], int size) {
    if (size <= 5) return false;
    for (int i = 0; i < size - 3; i++) {
        if (s[i] != s[i + 1] || s[i + 1] + 1 != s[i + 2] || s[i] + 1 != s[i + 2] || s[i + 2] != s[i + 3]) return false;
        i++;
    }
    return true;
}

// funçao que transforma o tipo de combinaçao em numeros para facilitar noutras funçoes
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

// funçao que conta o numero de reis para as excessoes
int contarReis(wchar_t ultimaJogada[]) {
    int countReis = 0;
    for (int i = 0; ultimaJogada[i] != L'\0'; i++) {
        if (valor(ultimaJogada[i]) == 14) {
            countReis++;
        }
    }
    return countReis;
}

// funçao que chama obterTipoCombinacao para ver se é uma combinaçao valida
bool verificarCombinacaoValida(wchar_t jogada[], wchar_t ultimaJogada[]) {
    int tipoAnterior = 0;

    if (ultimaJogada[0] != L'\0') {
        tipoAnterior = obterTipoCombinacao(ultimaJogada, wcslen(ultimaJogada));
    }

    int tipoJogada = obterTipoCombinacao(jogada, wcslen(jogada));

    if (tipoAnterior == 0) {
        return tipoJogada != 0;
    }

    return tipoJogada == tipoAnterior;
}

// funçao que usa o valor e o naipe para verificar qual é a sequencia maior
bool verificaMaior(wchar_t jogada[], wchar_t ultimaJogada[]) {
    int tam_jogada = wcslen(jogada);
    int tam_ultimajogada = wcslen(ultimaJogada);
    if (tam_ultimajogada != 0 && wcscmp(ultimaJogada, L"PASSO") != 0) {
        if (valor(jogada[tam_jogada - 1]) > valor(ultimaJogada[tam_ultimajogada - 1])) {
            return true;
        } else if (valor(jogada[tam_jogada - 1]) == valor(ultimaJogada[tam_ultimajogada - 1]) && naipe(jogada[tam_jogada - 1]) > naipe(ultimaJogada[tam_ultimajogada - 1])) {
            return true;
        }
        return false;
    }
    return true;
}

// funçao que verifica se a jogada tem o mesmo tamanho da ultima jogada
bool verificaTamanho(wchar_t jogada[], wchar_t ultimaJogada[]) {
    int tam_jogada = wcslen(jogada);
    int tam_ultimajogada = wcslen(ultimaJogada);

    if (tam_ultimajogada != 0 && wcscmp(ultimaJogada, L"PASSO") != 0) {
        if (tam_jogada != tam_ultimajogada) return false;
    }
    return true;
}

// funçao que determina a ultima jogada
void determinarUltimaJogada(wchar_t sequencias[][20], int linhas, wchar_t ultimaJogada[]) {
    if (linhas == 0) {
        ultimaJogada[0] = L'\0';
        return;
    } else wcscpy(ultimaJogada, sequencias[linhas - 1]);

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
        } else if (countPasso == 2) {
            wcscpy(ultimaJogada, sequencias[linhas - 3]);
        } else if (countPasso == 1) {
            wcscpy(ultimaJogada, sequencias[linhas - 2]);
        }
    }
}

// funçao que é chamada no output para escrever a combinaçao
void imprimirCombinacao(wchar_t comb[]) {
    int tam_comb = wcslen(comb);
    for (int i = 0; i < tam_comb - 1; i++) {
        wprintf(L"%lc ", comb[i]);
    }
    wprintf(L"%lc\n", comb[tam_comb - 1]);
}

// funçao que gera as combinaçoes quando existe excessoes de reis
bool gerarCombReis(wchar_t mao[], wchar_t ultimaJogada[], wchar_t combAtual[], int pos, int tam_desejado, int tam_combAtual, int tipoComb) {
    bool combinacaoGerada = false;

    if (pos == tam_desejado) {
        if (tipoComb == obterTipoCombinacao(combAtual, tam_desejado)) {
            organiza(combAtual, tam_desejado);
            imprimirCombinacao(combAtual);
            return true;
        }
        return false;
    }

    for (int i = 0; mao[i] != L'\0'; i++) {
        combAtual[pos] = mao[i];
        combAtual[pos + 1] = L'\0';
        if (gerarCombReis(mao + i + 1, ultimaJogada, combAtual, pos + 1, tam_desejado, tam_combAtual + 1, tipoComb))
            combinacaoGerada = true;
    }
    return combinacaoGerada;
}

// funçao geral para gerar combinaçoes com o mesmo tamanho, tipo de combinaçao e maior que a ultima jogada
bool gerarCombPossiveis(wchar_t mao[], wchar_t ultimaJogada[], wchar_t combAtual[], int pos, int tam_ultimaJogada, int tam_combAtual) {
    bool combinacaoGerada = false;

    if (pos == tam_ultimaJogada) {
        if (verificarCombinacaoValida(combAtual, ultimaJogada) && verificaMaior(combAtual, ultimaJogada)) {
            organiza(combAtual, wcslen(combAtual));
            imprimirCombinacao(combAtual);
            return true;
        }
        return false;
    }

    for (int i = 0; mao[i] != L'\0'; i++) {
        if (valor(mao[i]) >= valor(ultimaJogada[pos])) {
            combAtual[pos] = mao[i];
            combAtual[pos + 1] = L'\0';
            if (gerarCombPossiveis(mao + i + 1, ultimaJogada, combAtual, pos + 1, tam_ultimaJogada, tam_combAtual))
                combinacaoGerada = true;
        }
    }

    return combinacaoGerada;
}

// funçao preguiçosa que so escreve PASSO
void output(wchar_t mao[], wchar_t ultimaJogada[]) {
    if (verificar_conjunto(mao) && verificar_conjunto(ultimaJogada)) {}
    wprintf(L"PASSO\n");
}
