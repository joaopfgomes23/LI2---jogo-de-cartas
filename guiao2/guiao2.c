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

// funçao que compara as cartas pelo valor e naipe
int compara_cartas(const void *a, const void *b) {
    wchar_t cartaA = *(wchar_t *)a;
    wchar_t cartaB = *(wchar_t *)b;
    
    int valorA = valor(cartaA);
    int valorB = valor(cartaB);

    if (valorA != valorB) {
        return valorA - valorB;
    } else {
        return naipe(cartaA) - naipe(cartaB);
    }
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
    if (size <= 4) return false;
    for (int i = 0; i < size - 3; i++) {
        if (s[i] == s[i + 1] && s[i + 2] == s[i + 3]) return true;
    }
    return false;
}

//funçao para contar as cartas da sequencia
int contacartas(int nseqs, wchar_t sequencias[][15]){
    int soma = 0;
    for (int i = 0; i < nseqs; i++){
        for (int j = 0; sequencias[i][j] != L'\0'; j++){
            soma++;
        }
    }
    return soma;
}

//funcao que ordena as cartas pelos seus valores para a verificaçao das combinaçoes
void ordenaValores(int s[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (s[i] > s[j]) {
                int temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}

//funçao que verifica se tem o mesmo tipo de combinaçoes
bool verificarCombinacoes(wchar_t s[][15], int linhas){
    int r = 0;
    int lastCombination = -1;

    for (int a = 0; a < linhas; a++){
        int size = wcslen(s[a]);
        int val[size];
        
        for (int i = 0; i < size; i++){
            val[i] = valor(s[a][i]);
        }
        
        ordenaValores(val, size);
        
        int currentCombination = -1;

        if (verificar_conjunto(s[a]) && size >= 1 && size <= 4) {
            currentCombination = 1;
        } else if (verificar_sequencia(val, size) && size >= 3) {
            currentCombination = 2;
        } else if (verificar_duplaSequencia(val, size) && size / 2 >= 3) {
            currentCombination = 3;
        } else {
            currentCombination = 0;
        }

        if (lastCombination != -1 && currentCombination != lastCombination) {
            r = 1;
            break;
        }
        lastCombination = currentCombination;
    }
    return r;
}

// funçao que armazena as sequencias do input por linhas
void armazenaCartas(int linhas, wchar_t sequencias[][15]){
    for (int i = 0; i < linhas; i++){
        wscanf(L"%ls", sequencias[i]);
    }
}

// funçao que troca as matrizes                                   
void TrocaMatrizes(wchar_t sequencias[][15], int x, int y){
    for (int j = 0; sequencias[x][j] != '\0'; j++){
        wchar_t temp[100][14];
        temp[0][j] = sequencias[x][j];
        sequencias[x][j] = sequencias[y][j];
        sequencias[y][j] = temp[0][j];
    }
}


int cartasLinha(int linhas, wchar_t sequencias[][15]){            
    int ncartas[linhas];
    int r = 0;
    for (int i = 0; i < linhas; i++){
        ncartas[i] = 0;
        for (int j = 0; sequencias[i][j] != L'\0'; j++){
            ncartas[i]++;
        }
    }
    for (int i = 1; i < linhas; i++){
        if (ncartas[i] != ncartas[i - 1]) {
            r = 1;
        }
    }
    return r;
}

// funçao que da o output
void output(wchar_t sequencias[][15], int linhas){
    int cartaslinha = (contacartas(linhas, sequencias) / linhas);
    for (int i = 0; i < linhas - 1; i++){
        for (int j = 1, x = 0; j < linhas; j++){
            organiza(sequencias[j], cartaslinha);
            organiza(sequencias[j - 1], cartaslinha);
            if (valor(sequencias[j][x]) < valor(sequencias[j - 1][x])){
                TrocaMatrizes(sequencias, j, j - 1);
            } else if ((valor(sequencias[j][x]) == valor(sequencias[j - 1][x])) && (sequencias[j][cartaslinha - 1] < sequencias[j - 1][cartaslinha - 1])){
                TrocaMatrizes(sequencias, j, j - 1);
            }
        }
    }

    for (int i = 0; i < linhas; i++){
        for (int j = 0; sequencias[i][j] != L'\0'; j++){
            wprintf(L"%lc", sequencias[i][j]);
            if (j != cartaslinha - 1) {
                wprintf(L" ");
            }
        }
        wprintf(L"\n");
    }
}

int main(){
    setlocale(LC_CTYPE, "C.UTF-8");
    int testes, linhas;
    wscanf(L"%d", &testes);
    for (int i = 0; i < testes; i++){
        wprintf(L"Teste %d\n", i + 1);
        wscanf(L"%d", &linhas);
        wchar_t sequencias[1000][15];
        armazenaCartas(linhas, sequencias);
        if ((cartasLinha(linhas, sequencias)) || (verificarCombinacoes(sequencias, linhas))){ 
            wprintf(L"Combinações não iguais!\n");
        } else {
            output(sequencias, linhas);   
        }
    }
    return 0;     
}

