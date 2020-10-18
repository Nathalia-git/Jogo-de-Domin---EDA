#ifndef DOMINO_H
#define DOMINO_H

#include "stdio.h"
#include "stdlib.h"
//#include "conio.h"  //uso no windows
#include "time.h"
//cores para o jogo
#define RS "\033[0m"
#define OL "\033[1m"
#define FR "\033[31m" 
#define FG "\033[32m" 
#define FB "\033[34m" 
#define FW "\033[37m" 
#define BR "\033[41m" 
#define BB "\033[44m" 

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
int jogador_jog(Peca *inicio, Peca *fim);		
int oponente_jog(Peca **oponente, Peca *inicio, Peca *fim);		
Peca* final_de_lista(Peca *comeco);	
Peca* inicia(Peca *ptr);
Peca* dispersar(Peca **inicio1, Peca **inicio2 , int qtd_pecas, int visualizar);		
int contabiliza(Peca *percorre);		
void conta_maior (Peca **percorre, Peca **corre);		
Peca* arrevesar_peca(Peca *peca);
Peca* seleciona();		
void apresenta_posicao(Peca *percorre);	
void para_baixo(Peca *percorre, int verifica);		
int somatorio(Peca *percorre);		
Peca* coloca_fim(Peca **lst, Peca **colocado);	
int confere_peca(Peca *ptr, Peca *comeco, Peca *final); 
void final_jogo();		
void acabar() 


#endif
