#include"domino.h"

int main(){
	int op=0;
	
	printf(     "____________________________________________ \n");
	printf("%s%s|              ____________                |%s%s\n",BB,FW,OL,RS);
	printf("%s%s|             |Vamos Jogar?|               |%s%s\n",BB,FW,OL,RS);
	printf("%s%s|              ------------                |%s%s\n",BB,FW,OL,RS);
	printf("%s%s|                                          |%s%s\n",BB,FW,OL,RS);
	printf("%s%s|               1 - Jogar                  |%s%s\n",BB,FW,OL,RS);
	printf("%s%s|               2 - Sair                   |%s%s\n",BB,FW,OL,RS);
	printf("%s%s|__________________________________________|%s%s\n",BB,FW,OL,RS);
	
	printf("Digite a opcao desejada: ");
	scanf("%d",&op);

		switch(op){
			case 1: principal_jogo();
			break;
			case 2: acabar();
			break;
			default: printf("\n Tecla indefinida!\n");
			printf("\n");
			break;
		}	
	
	return 0;
}

//imprime uma mensagem para o usuário, agradecendo por jogar
void acabar(){
	
	printf("\n%s%s	+---------------------------------------+%s%s\n",BB,FW,OL,RS);
	printf("%s%s	|                                       |%s%s\n",BB,FW,OL,RS);
	printf("%s%s	|          Obrigado Por Jogar!          |%s%s\n",BB,FW,OL,RS);
	printf("%s%s	|                                       |%s%s\n",BB,FW,OL,RS);
	printf("%s%s	+---------------------------------------+%s%s\n\n",BB,FW,OL,RS);
}

//Nesta função 28 peças são mandadas para o monte e são distribuidas a quantidade minima de peças para o jogador e o oponente de forma aleatória.
//Ao começar o jogo verifica-se qual foi o primeiro jogador a jogar, o que definirá a ordem de jogadas do restante do jogo
//Possíveis resultados para o término do jogo: O oponente ficar sem peça, o jogador ficar sem peças ou não ter mais peças para serem compradas no monte e então é contado o somatório das peças de cada jogador, com a função conta para saber quem ganhou 
void principal_jogo(){

	Peca *primeiro, *ultimo;
	int contador1, contador2, contador3, v_opo, v_jogad, aux1, aux2;

	monte = inicia(monte); // as 28 peças são colocadas no monte
	jogador = dispersar(&jogador, &monte, 7, 0); // o jogador recebe 7 peças aleatórias
	oponente = dispersar(&oponente, &monte, 7, 0);// o oponente recebe 7 peças aleatórias
	inicio_jogo(&jogador, &oponente);
	contador1 = contabiliza(oponente);
	contador2 = contabiliza(jogador);//verificam se o oponento ou o jogador jogou primeiro 
	contador3 = 0;
	
	if(contador1 < contador2){
		v_opo = 2; //proximo a jogar
		v_jogad = 1; //primeiro a jogar
	}else{
		v_opo = 1;//primeiro a jogar
		v_jogad = 2;//proximo a jogar 
	}
	while(contador1 != 0 && contador2 != 0 && contador3 < 2){
		primeiro = tabuleiro;//analisa a primeira peça no início do jogo e após a jogada do jogador
		ultimo = final_de_lista(tabuleiro);//analisa a ultima peça no início do jogo e após a jogada do jogador
		if(v_opo < v_jogad){
			aux2 = oponente_jog(&oponente, primeiro, ultimo);
				if(contabiliza(oponente)==0) break;
			apresenta_jogo();
			primeiro = tabuleiro;//analisa a primeira peça logo após a jogada do oponente
			ultimo = final_de_lista(tabuleiro);//analisa a ultima peça logo após a jogada do oponente
			aux1 = jogador_jog(primeiro, ultimo);
		}
		else{
			apresenta_jogo();
			aux1 = jogador_jog(primeiro, ultimo);
				if(contabiliza(jogador) == 0) break;
			primeiro = tabuleiro;//analisa a primeira peça logo após a jogada do jogador
			ultimo = final_de_lista(tabuleiro);//analisa a última peça logo após a jogada do jogador
			aux2 = oponente_jog(&oponente, primeiro, ultimo);
		}
		if(aux1 == 0 && aux2 == 0){
			contador3 = 2;
		}
		contador1 = contabiliza(oponente);
		contador2 = contabiliza(jogador);
		if(contador1 == 0 || contador2 == 0) break;
	}
	apresenta_jogo();//funcao responsavel por mostrar o jogo
	final_jogo();//acaba o jogo
	getchar();
	free(monte);//libera memória
	free(jogador);//libera memória
	free(tabuleiro);//libera memória
	free(oponente);//libera memória
	getchar();
	acabar();//funcao para chamar a mensagem "Obrigada por jogar"
}
//Dá início ao jogo automaticamente. 
//Percorre as peças do jogador e do oponente a fim de encontrar o maior carretão entre elas, caso não encontre carretões chama a função maior
void inicio_jogo(Peca **percorre, Peca **corre){
	Peca *usu, *usu1, *op, *op1;
	Peca *val, *val1, *val2, *val3;
	Peca *auxJ, *auxO;
	int totalj = -1;
	int totalo = -1;
	auxO = oponente;
	auxJ = jogador;
	usu = usu1 = val = val1 = *percorre;
	op = op1 = val2 = val3 = *corre;

	while(usu != NULL){ //percorrendo as peças do jogador
		if(usu->E == usu->D && usu->E > totalj){//verifica em cada peça se o numero da esquerda da peça é igual ao numero da direita da peça, e o número da peça da esquerda for o maior possível entre todas as outras peças o carretão foi encontrado
			val = usu1;
			val1 = usu;
			totalj = usu->D;//totalj guarda a posição do carretão do jogador
		}
		usu1 = usu;//guarda o anterior da lista
		usu = usu->prox;//aponta para o proximo da lista do jogador
	}
	while(op != NULL){//percorrendo as peças do oponente
		if(op->E == op->D && op->E > totalo){//verifica em cada peça se o numero da esquerda da peça é igual ao numero da direita da peça, e o número da peça da esquerda for o maior possível entre todas as outras peças o carretão foi encontrado
			val3 = op1;
			val2 = op;
			totalo = op->D;//totalo guarda a poisção do carretão do oponente
		}
		op1 = op;//guarda o anterior da lista
		op = op->prox;//aponta para o proximo da lista do oponente
	}
	if(totalo > totalj){//verifica se o maior carretão é do oponente ou do jogador
		printf("O Carretão de Maior Valor é do: Oponente[%d|%d] \n",totalo,totalo);
		printf("O Oponente começa a partida...\n");
	}
	if(totalj > totalo){//verifica se o maior carretão é o do jogador ou do oponente
		printf("O Carretão de Maior Valor é do: Jogador[%d|%d] \n",totalj,totalj);
		printf("O Jogador começa a partida...\n");
	}
	if(totalj == totalo){//quando um carretão não é encontrado, ou seja, quando todos os carretões estão no monte (-1 == -1) se o indice do carretão nunca mudou significa que ele nunca encontrou um carretão
		printf("O Carretão de maior valor é do: Nenhum Carretão!!! \n");
		printf("Não há Carretões... Então Escolhendo a Maior Soma Entre as Peças:\n");
	}
	printf("Pressione Enter para continuar! \n");
	getchar();
	getchar();
	if(totalj > totalo){//verifica se o maior carretão é o do jogador
		if(val == val1)
			auxJ = val->prox;
		val->prox = val1->prox;//arruma a ordem da lista de onde uma peça foi retirada
		val1->prox = NULL;
		*percorre = auxJ;
		tabuleiro = dispersar(&tabuleiro, &val1, 1, 1);
	}
	if(totalo > totalj){//verifica se o maior carretão é do oponente
		if(val3 == val2)
			auxO = val3->prox;
		val3->prox = val2->prox;//arruma a ordem da lista de onde uma peça foi retirada
		val2->prox = NULL;
		*corre = auxO;
		tabuleiro = dispersar(&tabuleiro, &val2, 1, 1);
		
	}
	if(totalj == totalo){//se não houver carretões a funcao maior é chamada para calcular a peça de maior valor entre o jogador e o oponente
		conta_maior(&jogador, &oponente);
	}
}
void apresenta_jogo(){
	printf("\nMonte: %d\n",contabiliza(monte));
	para_baixo(monte, 1);
	printf("\n\n");
	printf("Peças do Oponente:\n");
	para_baixo(oponente, 2);
	printf("\n\n");
	printf("Peças da Mesa:\n");
	apresenta(tabuleiro, 1);
	printf("\n\n");
	printf("Peças do Jogador:\n");
	apresenta(jogador, 2);
	printf("\n\n");
}

//percorre lista e apresenta todos os valores que estão na lista
void apresenta(Peca *percorre, int verifica){
	
	Peca *p;
	p = percorre;

	if(p == NULL)
		printf("Não há pecas!");

		while(p != NULL){// percorre a lista até chgar no ultimo elemento
			if(verifica == 1){
				printf("{%d|%d}",p->E, p->D);
			}
			if(verifica == 2){
				printf("%s{%d|%d}%s ",FB,p->E, p->D,RS);
			}
			p = p->prox; //aponta para o proximo No
		}
		printf("\n");
}
