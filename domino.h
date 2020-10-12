#ifndef DOMINO_H
#define DOMINO_H

#include "stdio.h"
#include "stdlib.h"
//#include "conio.h"  //para uso no windows
#include "time.h"

typedef struct Peca{
	int E;
	int D;
	struct Peca *prox;
}Peca;

struct Peca *monte = NULL;
struct Peca *jogador = NULL;
struct Peca *tabuleiro = NULL;
struct Peca *oponente = NULL;

void principal_jogo();
void inicio_jogo (Peca **percorre, Peca **corre);
void apresenta_jogo();	
void apresenta(Peca *percorre, int verifica);	

#endif
