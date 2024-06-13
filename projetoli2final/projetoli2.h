#ifndef PROJETOLI2_H
#define PROJETOLI2_H

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

// Função que diz o valor da carta
int valor(wchar_t carta);

// Função que diz o naipe da carta
wchar_t naipe(wchar_t carta);

// Função que troca as cartas, usada na função organiza
void troca_cartas(wchar_t *cartaA, wchar_t *cartaB);

// Função que organiza a sequência por ordem crescente
void organiza(wchar_t resultados[], int tam_mao);

// Função que verifica se é conjunto
bool verificar_conjunto(wchar_t s[]);

// Função para verificar se é sequência
bool verificar_sequencia(int s[], int size);

// Função para verificar se a sequência é dupla sequência
bool verificar_duplaSequencia(int s[], int size);

// Verificar o tipo de combinação da jogada atual
int obterTipoCombinacao(wchar_t combinacao[], int tam_combinacao);

// Função para verificar se a jogada atual é válida de acordo com as regras dos reis
int contarReis(wchar_t ultimaJogada[]);

bool verificarCombinacaoValida(wchar_t jogada[], wchar_t ultimaJogada[]);

bool verificaMaior(wchar_t jogada[], wchar_t ultimaJogada[]);

bool verificaTamanho(wchar_t jogada[], wchar_t ultimaJogada[]);

void determinarUltimaJogada(wchar_t sequencias[][20], int linhas, wchar_t ultimaJogada[]);

// Função para imprimir uma combinação com espaços entre as cartas
void imprimirCombinacao(wchar_t comb[]);

// Função para gerar todas as combinações possíveis com o mesmo tamanho e tipo que a última jogada
bool gerarCombReis(wchar_t mao[], wchar_t ultimaJogada[], wchar_t combAtual[], int pos, int tam_desejado, int tam_combAtual, int tipoComb);

// Função para gerar todas as combinações possíveis com o mesmo tamanho e tipo que a última jogada
bool gerarCombPossiveis(wchar_t mao[], wchar_t ultimaJogada[], wchar_t combAtual[], int pos, int tam_ultimaJogada, int tam_combAtual);

void output(wchar_t mao[], wchar_t ultimaJogada[]);

#endif // PROJETOLI2_H
