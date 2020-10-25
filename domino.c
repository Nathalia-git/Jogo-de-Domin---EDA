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
//Possíveis resultados para o término do jogo: O oponente ficar sem peça, o jogador ficar sem peças ou não ter mais peças para serem compradas no monte e então é contado o somatório das peças de cada jogador, com a função somatorio para saber quem ganhou 
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

//ao escolher a peça a ser jogada pelo jogador na mesa, se a peça escolhida for uma peça errada, essa retorna para a lista de peças do jogador
int jogador_jog(Peca *inicio, Peca *fim){
	Peca *p, *prim, *ult;
	int aux = 0;
	prim = inicio;
	ult = fim;
	p = seleciona();//indica a peça que foi escolhida para jogar

	if(p == NULL) return(0);
	else{//faz a comparação entre a peça jogada com as "esquerdas" e as "direitas" das peças da mesa
		while(aux == 0){
			if(p->E == prim->E){
				p = arrevesar_peca(p);
				tabuleiro = dispersar(&prim, &p, 1, 1);
				return(1);
			}
			else if(p->D == prim->E){
				tabuleiro = dispersar(&prim, &p, 1, 1);
				return(1);
			}
			else if(p->E == ult->D){ 
				tabuleiro = coloca_fim(&tabuleiro, &p);
				return(1);
			}
			else if(p->D == ult->D){ 
				p = arrevesar_peca(p);
				tabuleiro = coloca_fim(&tabuleiro, &p);
				return(1);
			}
			else{ 
			jogador = dispersar(&jogador,&p,1,1);
			apresenta_jogo();
			apresenta_jogo();
			aux = 0;
			p = seleciona();
			}
		}
	}
	return(1);
}
//percorre as peças do oponente a procura de uma peça que se encaixe com as peças da mesa, caso não encontre o oponente irá comprar no monte, se não houver como comprar é retornado 0 e pula a vez.
int oponente_jog(Peca **opon, Peca *inicio, Peca *fim){
	Peca *compara, *aux1, *aux2;
	int ok = 0, n;

	aux1 = NULL;
	compara = *opon;

	while(compara != NULL){
		ok = confere_peca(compara, inicio, fim);//usa a função para comparar se faz sentido com as outras peças
		if(ok == 1){//caso encontre uma peça que se encaixe com as peças da mesa
			if(aux1 == NULL){//se for a primeira da lista analisa onde pode encaixar
				if(compara->E == inicio->E){
					*opon = compara->prox;
					aux2 = arrevesar_peca(compara);
					aux2->prox = inicio;
					inicio = aux2;
					tabuleiro = inicio;
					return(1);
				}
				if(compara->D == inicio->E){
					*opon = compara->prox;
					aux2 = compara;
					aux2->prox = inicio;
					inicio = aux2;
					tabuleiro = inicio;
					return(1);
				}
				if(compara->E == fim->D){
					*opon = compara->prox;
					aux2 = compara;
					aux2->prox = fim->prox;
					fim->prox = aux2;
					tabuleiro = inicio;
					return(1);
				}
				if(compara->D == fim->D){
					*opon = compara->prox;
					aux2 = arrevesar_peca(compara);
					aux2->prox = fim->prox;
					fim->prox = aux2;
					tabuleiro = inicio;
					return(1);
				}
			}	
			else{//caso a peça que se encaixe esteja no meio ou no final da lista
				if(compara->E == inicio->E){
					aux1->prox = compara->prox;
					aux2 = arrevesar_peca(compara);
					aux2->prox = inicio;
					inicio = aux2;
					tabuleiro = inicio;
					return(1);
				}
				if(compara->D == inicio->E){
					aux1->prox = compara->prox;
					aux2=compara;
					aux2->prox = inicio;
					inicio = aux2;
					tabuleiro = inicio;
					return(1);
				}
				if(compara->E == fim->D){
					aux1->prox = compara->prox;
					aux2 = compara;
					aux2->prox = fim->prox;
					fim->prox = aux2;
					tabuleiro = inicio;
					return(1);
				}
				if(compara->D == fim->D){
					aux1->prox = compara->prox;
					aux2 = arrevesar_peca(compara);
					aux2->prox = fim->prox;
					fim->prox = aux2;
					tabuleiro = inicio;
					return(1);
				}
			}
		}
		aux1 = compara;
		compara = compara->prox;
	}
	if(ok == 0 && monte != NULL){//se não houver uma peça que se encaixe então o oponente compra peça
		oponente = dispersar(&oponente, &monte, 1, 0);
		inicio = tabuleiro;
		fim = final_de_lista(tabuleiro);
		n = oponente_jog(&oponente, inicio, fim);
		return(n);
	}
	if(ok == 0 && monte == NULL){//pula a vez
		return(0);
	}
	if(compara == NULL) return(0);
}


//percorre a lista e guarda o valor do último nó
Peca* final_de_lista(Peca *comeco){
	Peca *p;

	p = comeco;

	if(p == NULL) return(0);
	else{
		while(p != NULL){//ponteiro percorre a lista até ser diferente de vazio
			if(p->prox == NULL) return (p);//retorna o último valor da lista
			p = p->prox;//aponta pro próximo nó
		}
	}
}

//cria as 28 peças do jogo
Peca* inicia(Peca *ptr){
	int k, i;
	Peca *new;
	Peca *n;

	n = ptr;

	for(i = 0; i <= 6; i++){
		k = i;
		for (; k <= 6; k++)
		{
			new = malloc(sizeof(Peca));//cria nó para cada peça
			if(new == NULL){
				printf("Memoria Sobrecarregada\n");//sesobrecarregar a memoria imprime a mensagem
				exit(0);
			}
			new->E = i;//valor do lado esquerdo da peça 
			new->D = k;//valor do lado direito da peça
			new->prox = n;//guardando o endereç da proxima peça
			n = new;
		}
	}
	return(n);
}
//distribui as peças aleatoriamente e possibilita a inserção no início da lista
//a funcao indica para onde a peça que retorna pela funcao deve ir, de onde ela deve sair e quantas vezes a função deve ser repetida
Peca* dispersar(Peca **inicio1, Peca **inicio2, int qtd_pecas, int visualizar){
	Peca *aa;
	Peca *aa1;
	Peca *aa2;
	int i, j;
	int marcado, cont;

	aa2 = *inicio1;//ponteiro destino para a peça
	srand(time(0));
	for(i = 0; i < qtd_pecas; i++){
		aa = aa1 = *inicio2; 
		cont = contabiliza(aa);
		if(visualizar == 1){
			marcado = (cont - 1); 
		}else{
			marcado = rand()%cont;
		}
		for(j = 0; j < marcado; j++){//percorrendo a lista
			aa1 = aa;
			aa = aa->prox;
		}
		if(marcado > 0 && marcado < cont){//percorrendo o meio da lista
			if(aa2 == NULL){//se não houver peças neste local
				aa1->prox = aa->prox;
				aa2 = aa;
				aa2->prox = NULL;//primeiro a ser inserido, consequentemente o ultimo da lista
			}else{
				aa1->prox = aa->prox;
				aa->prox = aa2;
				aa2 = aa;
			}
		}
		if(marcado == 0){
			if(aa2 == NULL){//inicio lista
				aa2 = aa;
				(*inicio2) = (*inicio2)->prox;
				aa2->prox = NULL;
			}else{
				(*inicio2) = (*inicio2)->prox;
				aa->prox = aa2;
				aa2 = aa;
			}
		}
		if(marcado == cont){//final da lista
			if(aa2 == NULL){
				aa2 = aa;
				aa2->prox = NULL;
			}else{
				aa1->prox = aa->prox;
				aa->prox = aa2;
				aa2 = aa;
			}
		}
		cont--;
	}
	return(aa2);
}

//conta a quantidade de peças da lista
int contabiliza(Peca *percorre){
	Peca *p;

	p = percorre;
	int contador;
	contador = 0;
	
	while(p != NULL){//percorre a lista até chegar no seu ultimo nó
		p = p->prox;//aponta para o proximo 
		contador++;//acumula a quantidade de peças da lista
	}
	return(contador);
}

//conta a maior peça entre o jogador e o oponente, caso não haja carretões escolhe a peça de maior valor, se houver um empate o oponente tem preferencia na jogada
void conta_maior(Peca **percorre, Peca **corre){
	Peca *usu, *usu1, *op, *op1;
	Peca *val, *val1, *val2, *val3;
	Peca *auxJ, *auxO;
	auxO = oponente;
	auxJ = jogador; 
	int somaj = 0, somao = 0;
	usu = usu1 = val = val1 = *percorre;
	op = op1 = val2 = val3 = *corre;

	while(usu != NULL){
		if(usu->E != usu->D && (usu->E + usu->D) > somaj){
			val = usu1;
			val1 = usu;
			somaj = usu->D + usu->E;
		}
		usu1 = usu;
		usu = usu->prox;
	}
	while(op != NULL){
		if(op->E != op->D && (op->D + op->E) > somao){
			val3 = op1;
			val2 = op;
			somao = op->D + op->E;
		}
		op1 = op;
		op = op->prox;
	}
	if(somao > somaj){
		printf("Valor da Maior Soma é do: Oponente[%d] \n",somao);
		printf("O Oponente começa...\n");
	}
	if(somaj > somao){
		printf("Valor da Maior Soma é do: Jogador[%i] \n",somaj);
		printf("O Jogador começa...\n");
	}
	if(somaj == somao){
		printf("Valor da Maior Soma: Soma Iguais!!! \n");
		printf("Sem Peça Maior... Então Preferencia do Oponente:\n");
	}
	printf("Pressione enter para continuar!\n");
	getchar();
	if(somaj > somao){//verifica se a maior soma é a do jogador
		if(val == val1)
			auxJ = val->prox;
		val->prox = val1->prox;//arruma a lista já que uma peça foi removida
		val1->prox = NULL;
		*percorre = auxJ;
		tabuleiro = dispersar(&tabuleiro, &val1, 1, 1);
	}
	if(somao > somaj){//verifica se a maior soma é a do oponente
		if(val3 == val2){
			auxO = val3->prox;
		val3->prox = val2->prox;
		val2->prox = NULL;
		*corre = auxO;
		tabuleiro = dispersar(&tabuleiro, &val2, 1, 1);
		}
	}
	if(somaj == somao){//se houver duas peças que são maiores a preferencia é dada para o oponente
		if(val3 == val2){
			auxO = val3->prox;
		val3->prox = val2->prox;//arruma a lista já que uma peça foi removida
		val2->prox = NULL;
		*corre = auxO;
		tabuleiro = dispersar(&tabuleiro, &val2, 1, 1);
		}
	}
}

//responsavel por inverter os lados da pessa, a esquerda da peça passa a ser a direita e assim vice e versa
Peca* arrevesar_peca(Peca *peca){
	Peca *aux_peca;

	aux_peca = malloc(sizeof(Peca));
	aux_peca->D = peca->E;
	aux_peca->E = peca->D;
	return(aux_peca);
}

//guarda a peça escolhida que vai ser usada em outra função
//se o jogador escolher uma peça que não se encontra nas suas peças é emitida uma mensagem para jogar novamente
//se o jogador quiser comprar peças e o monte estiver vazio então é retornado 0 mostrando que a vez do jogador foi pulada
Peca* seleciona(){
	Peca *aux, *aux1, *ultimo, *primeiro;
	int numero_peca = 0, P, i = 1, n ,contador;

	apresenta_posicao(jogador);
	numero_peca = contabiliza(jogador);
	contador = contabiliza(monte);

	printf("\nEscolha a peça para jogar na mesa, digite 0 para comprar peça e -1 para sair do jogo:");
	scanf("%d", &P);
	while(P > numero_peca || (P < 1 && P != -1 && P != 0)){
		apresenta_jogo();//apresenta na tela a situacao atual do jogo
		apresenta_posicao(jogador);//apresenta as peças com a posição que será escolhida
		printf("\n");
		printf("Opçao Invalida! Por favor, Digite Novamente :"); // se o digito não condizer com 0, -1, e o numero da peça imprime uma mensagem de erro
		scanf("%i",&P);
		printf("\n");
	}
	if(P == -1){//se digitar -1 sai do jogo
		exit(1);
	}
	if(P == 0){//compra peça no monete
		if(contador == 0){//caso não haja peça no monte retorna 0
			return(NULL);
		}else{
			jogador = dispersar(&jogador, &monte, 1, 0);//nenhuma peça é jogada, peça aleatoria é comprada
			apresenta_jogo();//mostra a situação atual do jogo
			primeiro = tabuleiro;
			ultimo = final_de_lista(tabuleiro);
			n = jogador_jog(primeiro, ultimo);
			return(NULL);
		}
	}else{
		aux = aux1 = jogador;
		while(i != P){
			aux1 = aux;
			aux = aux->prox;
			i++;
		}
		if(aux1 == aux){
			jogador = jogador->prox;
			aux->prox = NULL;
		}
		if(aux1 != aux){
			aux1->prox = aux->prox;
			aux->prox = NULL;
		}
		return(aux);
	}
}

//percorre a lista e mostra para o jogador as suas peças e as posições das peças para serem escolhidas
void apresenta_posicao(Peca *percorre){
	Peca *p;

	p = percorre;
	int contador = 0;
	printf("Peças do Jogador:\n");
	if(p == NULL)
		printf("Sem pecas!");
		while(p != NULL){//percorre a lista até chegar no ultimo no da lista
			printf("%d-%s{%d|%d}%s  ", ++contador,FB,p->E, p->D,RS);//imprime as pecas do jogador
			if(contador%8 == 0)
			printf("\n");
			p = p->prox;//aponta para o proximo
		}
		printf("\n");
}

//percorre a lista e mostra as peças para baixo
//possibilita a escolha das peças no jogo para o oponente
//esconde o valor da peça que será comprada no monte
void para_baixo(Peca *percorre, int verifica){
	Peca* p;
	p = percorre;

	if(p == NULL)
		printf("Não há pecas!");
		while(p != NULL){//percorre a lista até encontrar o ultimo nó da lista
			if(verifica == 1){//para o monte
				printf("%s{*|*}%s ", FG, RS);
			}
			if(verifica == 2){//para o oponente
				printf("%s{*|*}%s ", FR, RS);
			}
			p = p->prox;
		}
		printf("\n");
}

//soma todas as peças de uma lista
int somatorio(Peca *percorre){
	Peca* p;

	p = percorre;
	int soma1 = 0;

	while(p != NULL){
		soma1 += p->E + p->D;
		p = p->prox;
	}
	return (soma1);
}

Peca* coloca_fim(Peca **lst, Peca **colocado){
	Peca *fim, *aux1;

	aux1 = *lst;
	fim = final_de_lista(aux1);
	fim->prox = (*colocado);
	(*colocado)->prox = NULL;
	return(*lst);
}

//confere as pecas do oponente para achar um valor que se encaixe com as pecas na mesa
int confere_peca(Peca* ptr, Peca *comeco, Peca *final){
	Peca *confere;

	confere = ptr;
	while(confere != NULL){
		if(confere->E == comeco->E || confere->D == comeco->E || confere->E == final->D || confere->D == final->D){
			return(1);
		}
		confere = confere->prox;
	}
	return(0);
}
//verifica quem ganhou a partida, caso seja 0 venceu pois não há mais peças, ou se necessario as peças são contadas para determinar quem ganhou
void final_jogo(){

	int contador1 = 0, contador2 = 0, soma = 0, soma1 = 0;

	contador1 = contabiliza(oponente);
	contador2 = contabiliza(jogador);

	if(contador1 == 0)
		printf("%s%s Vencedor Oponente!! Valeu A Tentativa !! %s%s\n\n",BR,FW,OL,RS);
	if(contador2 == 0)
		printf("%s%s Vencedor Jogador!! Meus Parabéns !! %s%s\n\n",BR,FW,OL,RS);
	if(contador1 != 0 && contador2 != 0){
		soma = somatorio(oponente);
		soma1 = somatorio(jogador);
		if(soma < soma1){
			printf("Soma das peças do Oponente: %i\n",soma);
			printf("Soma das peças do jogador: %i\n\n",soma1);
			printf("%s%s Vencedor Oponente !! Valeu A Tentativa !! %s%s\n\n",BR,FW,OL,RS);
		}else{
			if(soma > soma1){
				printf("Soma das peças do Jogador: %i\n",soma1);
				printf("Soma das peças do Oponente: %i\n\n",soma);
				printf("%s%s Vencedor Jogador !! Meus Parabéns !! %s%s\n\n",BR,FW,OL,RS);
			}else{
				printf("%s%s Sem Vencedor !! Deu Empate !! %s%s\n",BR,FW,OL,RS);
			}
		}
	}
	printf("Pressione enter para finalizar...\n");
}
