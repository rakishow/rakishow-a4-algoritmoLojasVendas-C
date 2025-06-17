#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>

/*
[1] Função para item mais vendido do dia

[2] Função para item menos vendido do dia
*/


typedef struct cadastroItem {
	
	int codigo;
	int quantidade;
	double precoUnitario;
	double total;
	char* nomeItem;
	char* marca;
	
	int dias;
	int mes;
	int ano;
}cadItem, *pCadItem, **ppCadItem;


void item_maisVendido(int tamanho, ppCadItem vendas, int dia, int mes, int ano)
{
    if (tamanho == 0) {
        printf("Nenhuma venda cadastrada ainda.\n");
        return;
    }

    int maxQtd = -1;
    int idxMax = -1;


    int codigosVerificados[100];
    int codigosCount = 0;

	int i;
    for (i = 0; i < tamanho; i++) {
        if (vendas[i]->dias == dia &&
            vendas[i]->mes == mes &&
            vendas[i]->ano == ano) {

            int jaVerificado = 0;
            int k;
            for (k = 0; k < codigosCount; k++) {
                if (codigosVerificados[k] == vendas[i]->codigo) {
                    jaVerificado = 1;
                    break;
                }
            }

            if (jaVerificado) continue;

            codigosVerificados[codigosCount++] = vendas[i]->codigo;

            int soma = 0;
            int j;
            for (j = 0; j < tamanho; j++) {
                if (vendas[j]->dias == dia &&
                    vendas[j]->mes == mes &&
                    vendas[j]->ano == ano &&
                    vendas[j]->codigo == vendas[i]->codigo) {

                    soma += vendas[j]->quantidade;
                }
            }

            if (soma > maxQtd) {
                maxQtd = soma;
                idxMax = i;
            }
        }
    }

    if (idxMax == -1) {
        printf("Nenhuma venda nesse dia.\n");
        return;
    }

    printf("\n========== ITEM MAIS VENDIDO ==========\n");
    printf("Data................: %02d/%02d/%04d\n", dia, mes, ano);
    printf("Codigo..............: %d\n",   vendas[idxMax]->codigo);
    printf("Marca...............: %s\n",   vendas[idxMax]->marca);
    printf("Nome................: %s\n",   vendas[idxMax]->nomeItem);
    printf("Quantidade vendida..: %d\n",   maxQtd);
    printf("=======================================\n");
}

void item_menosVendido(int tamanho, ppCadItem vendas, int dia, int mes, int ano)
{
    if (tamanho == 0) {
        printf("Nenhuma venda cadastrada ainda.\n");
        return;
    }

    int minQtd = __INT_MAX__;
    int idxMin = -1;

    int codigosVerificados[100];
    int codigosCount = 0;
	
	int i;
    for (i = 0; i < tamanho; i++) {
        if (vendas[i]->dias == dia &&
            vendas[i]->mes == mes &&
            vendas[i]->ano == ano) {

            int jaVerificado = 0;
            int k;
            for (k = 0; k < codigosCount; k++) {
                if (codigosVerificados[k] == vendas[i]->codigo) {
                    jaVerificado = 1;
                    break;
                }
            }

            if (jaVerificado) continue;

            codigosVerificados[codigosCount++] = vendas[i]->codigo;

            int soma = 0;
            int j;
            for (j = 0; j < tamanho; j++) {
                if (vendas[j]->dias == dia &&
                    vendas[j]->mes == mes &&
                    vendas[j]->ano == ano &&
                    vendas[j]->codigo == vendas[i]->codigo) {

                    soma += vendas[j]->quantidade;
                }
            }

            if (soma < minQtd) {
                minQtd = soma;
                idxMin = i;
            }
        }
    }

    if (idxMin == -1) {
        printf("Nenhuma venda nesse dia.\n");
        return;
    }

    printf("\n========= ITEM MENOS VENDIDO ==========\n");
    printf("Data................: %02d/%02d/%04d\n", dia, mes, ano);
    printf("Codigo..............: %d\n",   vendas[idxMin]->codigo);
    printf("Marca...............: %s\n",   vendas[idxMin]->marca);
    printf("Nome................: %s\n",   vendas[idxMin]->nomeItem);
    printf("Quantidade vendida..: %d\n",   minQtd);
    printf("=======================================\n");
}


void total_clientes(int tamanho, ppCadItem vendas, int dia, int mes, int ano){
	int i;
	int clientes = 0;
	for(i =0; i < tamanho; i++){
		
	if(vendas[i]->dias == dia && vendas[i]->mes == mes && vendas[i]->ano == ano){
	clientes++;
	}
	
	}
	printf("Quantidade de clientes que realizaram compras: %d", clientes);
}

double calcular_preco(int tamanho, ppCadItem valor){	


	double desconto = 0.9;
	
	if(valor[tamanho]->quantidade >= 3){
	valor[tamanho]->total = (valor[tamanho]->precoUnitario * desconto) * valor[tamanho]->quantidade;
	}
	else{
		valor[tamanho]->total = valor[tamanho]->precoUnitario * valor[tamanho]->quantidade;
	}
	
	return valor[tamanho]->total;
}


void cadastrar_string(int tamanho, ppCadItem vendas){
	char buffer[100];
	
	printf("Digite a marca do produto: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = '\0';
	
	vendas[tamanho]->marca = malloc(sizeof(buffer) + 1);
	 if (vendas[tamanho]->marca == NULL) {
        printf("Erro de alocação de memoria para marca!\n");
        exit(1);
    }
	strcpy(vendas[tamanho]->marca, buffer);

	
	printf("Digite o nome do produto: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = '\0';
	
	vendas[tamanho]->nomeItem = malloc(sizeof(buffer) + 1);
	if (vendas[tamanho]->nomeItem == NULL) {
        printf("Erro de alocação de memoria para nome do item!\n");
        exit(1);
    }
	strcpy(vendas[tamanho]->nomeItem, buffer);
	
	
	
}

ppCadItem cadastrar_vendas(int tamanho, ppCadItem vendas, int dia, int mes, int ano){
	int cont = 0;
	int i=0;
	
	if(vendas == 0){
	vendas = (ppCadItem) malloc (sizeof(pCadItem));
	}
	else{
		vendas = (ppCadItem) realloc(vendas, (tamanho+1) * sizeof (pCadItem));
	}
	
	vendas[tamanho] = malloc(sizeof (cadItem));
	
	vendas[tamanho]->dias = dia;
	vendas[tamanho]->mes = mes;
	vendas[tamanho]->ano = ano;
	
	printf("Digite o codigo do produto: ");
	scanf("%d", &vendas[tamanho]->codigo);
	getchar();
	cadastrar_string(tamanho, vendas);
	printf("Digite a quantidade de produtos: ");
	scanf("%d", &vendas[tamanho]->quantidade);
	printf("Digite o preco do produto: R$");
	scanf("%lf", &vendas[tamanho]->precoUnitario);
	calcular_preco(tamanho, vendas);
	
	return vendas;
	}
	
	
void faturamento_bruto(int tamanho, ppCadItem vendas, int dia, int mes, int ano){
	int i;
	double faturamento = 0;
	for(i = 0; i < tamanho; i++){
	if(vendas[i]->dias == dia && vendas[i]->mes == mes && vendas[i]->ano == ano){
	faturamento += vendas[i]->total;
	}
	}
	
	printf("\nFaturamento Bruto do dia: R$ %.2lf\n", faturamento);
}
		
void imprimir_vendas(int tamanho ,ppCadItem vendas, int dia, int mes, int ano){
	int i;
	int j = 0;
	int cont = 0;
	

	
	if(cont == 0){
		printf("Nenhuma venda nesse dia\n");
		return;
	}
	
	
	
	for(i = 0; i < tamanho - 1 ; i++){
		for (j = i + 1; j < tamanho; j++) {
			if(vendas[i]->dias == dia && vendas[i]->mes == mes && vendas[i]->ano == ano && 
			   vendas[j]->dias == dia && vendas[j]->mes == mes && vendas[j]->ano == ano){
		 		if (vendas[i]->total < vendas[j]->total){
		 			pCadItem temp = vendas[i];
		 			vendas[i] = vendas[j];
		 			vendas[j] = temp;
				 }
			}
		}
	}
	
	for(i = 0; i < tamanho ; i++){
		if(vendas[i]->dias == dia && vendas[i]->mes == mes && vendas[i]->ano == ano){
		printf("Data da Venda: %d/%d/%d\n", vendas[i]->dias, vendas[i]->mes, vendas[i]->ano );
		printf("Codigo do produto: %d\n",vendas[i]->codigo );
		printf("Marca do produto: %s\n", vendas[i]->marca);
		printf("Nome do produto: %s\n", vendas[i]->nomeItem);
		printf("Quantide do produto: %d\n",vendas[i]->quantidade );
		printf("Preco do produto: R$%.2lf\n", vendas[i]->precoUnitario );
		if(vendas[i]->quantidade >= 3 ){
			printf("Valor total da venda: R$%.2lf (Com 10%% de desconto)\n", vendas[i]->total);
		}
		else{
			printf("Valor total da venda: R$%.2lf\n", vendas[i]->total);
		}
		printf("=====================================\n");
		}

	
}
}

void itens_vendidos(int tamanho, ppCadItem vendas, int dia, int mes, int ano){
	
	
	int i;
	int cont=0;
	
	for(i = 0 ; i <= tamanho ; i++){
		if(vendas[i]->dias == dia && vendas[i]->mes == mes && vendas[i]->ano == ano){
			cont += vendas[i]->quantidade;
		}	
	}
	
	printf("\nTotal de itens vendidos no dia: %d\n", cont);
	
}

void vendas_dia(int tamanho, ppCadItem vendas, int dia, int mes, int ano){
	int i;
	int cont=0;
		for(i = 0; i < tamanho; i++){
		if(vendas[i]->dias == dia && vendas[i]->mes == mes && vendas[i]->ano == ano){
			cont++;
		}
	}
	printf("Total de vendas realizadas: %d\n", cont);
}

void relatorio_final(int tamanho, ppCadItem vendas, int dia, int mes, int ano){
	
	printf("Data do relatorio: %d/%d/%d\n", dia, mes, ano);
	vendas_dia( tamanho, vendas, dia, mes, ano);
	total_clientes( tamanho, vendas, dia, mes, ano);
	faturamento_bruto( tamanho, vendas, dia, mes, ano);
	
}

int main (){
	setlocale (LC_ALL, "portuguese");
	ppCadItem vet = NULL;
	int opcao;
	int tamanho = 0;
	double faturamento = 0;
	
	int sim = 1;
	int totalVendas;
	int dia;
	int mes;
	int ano;
	
	do {
    system("cls");
    printf("========================================\n");
    printf("           SISTEMA DE VENDAS            \n");
    printf("========================================\n");
    printf("[1] Cadastrar nova venda\n");
    printf("[2] Listar vendas do dia\n");
    printf("[3] Faturamento bruto do dia\n");
    printf("[4] Quantidade de clientes do dia\n");
    printf("[5] Item mais vendido do dia\n");
    printf("[6] Item menos vendido do dia\n");
    printf("[7] Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");

    opcao = getch();
    system("cls");

    switch(opcao) {
        case '1':
            printf("Informe a data do dia de trabalho (DD MM AAAA): ");
            scanf("%d %d %d", &dia, &mes, &ano);
            while(sim == 1) {
                vet = cadastrar_vendas(tamanho, vet, dia, mes, ano);
                itens_vendidos(tamanho, vet, dia, mes, ano);
                tamanho++;
                printf("\nDeseja cadastrar nova venda? (1 = Sim / 0 = Nao): ");
                scanf("%d", &sim);
				printf("\n");
            }
            
            relatorio_final(tamanho, vet, dia, mes, ano);
            getch();
          	sim = 1;
          	break;

        case '2':
            printf("Informe a data do relatorio (DD MM AAAA): ");
            scanf("%d %d %d", &dia, &mes, &ano);
            imprimir_vendas(tamanho, vet, dia, mes, ano);
            printf("\nPressione qualquer tecla para voltar ao menu...");
            getch();
            break;

        case '3':
            printf("Informe a data (DD MM AAAA): ");
            scanf("%d %d %d", &dia, &mes, &ano);
            faturamento_bruto(tamanho, vet, dia, mes, ano);
            
            printf("\nPressione qualquer tecla para voltar ao menu...");
            getch();
            break;

        case '4':
            printf("Informe a data (DD MM AAAA): ");
            scanf("%d %d %d", &dia, &mes, &ano);
            total_clientes(tamanho, vet, dia, mes, ano);
            printf("\n\nPressione qualquer tecla para voltar ao menu...");
            getch();
            break;

        case '5':
		printf("Informe a data (DD MM AAAA): ");
		scanf("%d %d %d", &dia, &mes, &ano);
		item_maisVendido(tamanho, vet, dia, mes, ano);
		printf("\nPressione qualquer tecla para voltar ao menu...");
		getch();
		break;

        case '6':
		printf("Informe a data (DD MM AAAA): ");
		scanf("%d %d %d", &dia, &mes, &ano);
		item_menosVendido(tamanho, vet, dia, mes, ano);
		printf("\nPressione qualquer tecla para voltar ao menu...");
		getch();
		break;

        case '7':
            printf("Saindo do sistema...\n");
            sleep(1);
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            getch();
            break;
    }

} while(opcao != '7');

}

