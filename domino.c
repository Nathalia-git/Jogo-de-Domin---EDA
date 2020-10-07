#include"domino.h"

int main (){
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


void acabar(){
	
	printf("\n%s%s	+---------------------------------------+%s%s\n",BB,FW,OL,RS);
	printf("%s%s	|                                       |%s%s\n",BB,FW,OL,RS);
	printf("%s%s	|          Obrigado Por Jogar!          |%s%s\n",BB,FW,OL,RS);
	printf("%s%s	|                                       |%s%s\n",BB,FW,OL,RS);
	printf("%s%s	+---------------------------------------+%s%s\n\n",BB,FW,OL,RS);
}
//imprime uma mensagem para o usuário, agradecendo por jogar
