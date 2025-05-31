#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>


typedef struct cadastroItem {
	
	int codigo;
	int quantidade;
	double precoUnitario;
	char nomeItem;
	char nomeMarca;
	
}cadItem, *pCadItem, **ppCadItem;







int main (){
	
	int opcao;
	
	
	do{
	system("cls");
	printf("Escolha uma opcao abaixo:\n");
	
	printf("1: Cadastrar item\n");
	printf("2: Listar vendas do dia em ordem decrescente de valor (informar data)\n");
	printf("3: Faturamento bruto diario (informar data)\n");
	printf("4: Quantidade de clientes que realizaram compras (informar data)\n");
	printf("5: Item mais vendido (informar data)\n");
	printf("6: Item menos vendido (informar data)\n");
	printf("7: Sair\n");
	
	
	opcao = getch();
	
	
	system("cls");
	switch(opcao){
	
	case '1':
		printf("1\n");
		getch();
		break;
	
	case '2':
		printf("2\n");
		getch();
		break;
	
	case '3':
		printf("3\n");
		getch();
		break;
	
	case '4':
		printf("4\n");
		getch();
		break;
		
	case '5':
		printf("5\n");
		getch();
		break;
		
	case '6':
		printf("6\n");
		getch();
		break;
	
	case '7':
		printf("Saindo...\n");
		sleep(1);
		break;
		
	default:
		printf("Opcao invalida\n");
		getch();
		break;
	}
		
		
	}while(opcao != '7');


}
