#include <stdio.h>
#include <stdlib.h>

typedef struct produto
{
	int* Hi;
	int* Lo;
	int CarryOut;
}Produto;

int* CriarBinario(int MAX);

Produto* CriarProduto(int MAX);

void Conversao(int n, int* v, int MAX);

int Soma(int* v1, int* v2,int* result, int MAX);

int* ComplementoA2(int* a, int MAX);

void Shift_Direita(Produto* p, int MAX);

int main()
{
	int x,y,i,MAX;
	int cont = 0;
	printf("Indique a quantidade de bits: ");
	scanf("%d", &MAX);
	Produto* p = CriarProduto(MAX);
	int* a = CriarBinario(MAX);
	int* b = CriarBinario(MAX);
	printf("Digite o Multiplicando: ");
	scanf("%d", &x);
	printf("Digite o Multiplicador: ");
	scanf("%d", &y);
	Conversao(x,a,MAX);
	Conversao(y,b,MAX);
	p->Lo = b;
	while(cont != MAX)
	{
		printf("Inicio %d Produto: \n",cont);
		for (i = 0; i < MAX; i++)
		{
			printf("%d ",p->Hi[i]);
		}
		printf("\t");
		for (i = 0; i < MAX; i++)
		{
			printf("%d ",p->Lo[i]);
		}
		printf("\n");
		printf("CarryOut: %d\n", p->CarryOut);
		printf("\n\n");

		if (p->Lo[MAX-1] != p->CarryOut)
		{
			if (p->CarryOut == 1)
			{
				Soma(a,p->Hi,p->Hi,MAX);
			}
			else
			{
				Soma(ComplementoA2(a,MAX),p->Hi,p->Hi,MAX);
			}
		}
		printf("Before Shift %d Produto: \n",cont);
		for (i = 0; i < MAX; i++)
		{
			printf("%d ",p->Hi[i]);
		}
		printf("\t");
		for (i = 0; i < MAX; i++)
		{
			printf("%d ",p->Lo[i]);
		}
		printf("\n");
		printf("CarryOut: %d\n", p->CarryOut);
		printf("\n\n");
		Shift_Direita(p,MAX);
		printf("%d Produto: \n",cont);
		for (i = 0; i < MAX; i++)
		{
			printf("%d ",p->Hi[i]);
		}
		printf("\t");
		for (i = 0; i < MAX; i++)
		{
			printf("%d ",p->Lo[i]);
		}
		printf("\n");
		printf("CarryOut: %d\n", p->CarryOut);
		printf("\n\n");
		cont++;
	}
	printf("%d Produto: \n",cont);
	for (i = 0; i < MAX; i++)
	{
		printf("%d ",p->Hi[i]);
	}
	printf("\t");
	for (i = 0; i < MAX; i++)
	{
		printf("%d ",p->Lo[i]);
	}
	printf("\n");
	printf("CarryOut: %d\n", p->CarryOut);
	printf("\n\n");

	free(a);
	free(b);
	free(p);
}

int* CriarBinario(int MAX)
{
	int* b = (int*) calloc (MAX, sizeof(int));
	return b;
}

Produto* CriarProduto(int MAX)
{
	Produto* p = (Produto*) malloc(sizeof(Produto));
	p->Hi = CriarBinario(MAX);
	p->Lo = CriarBinario(MAX);
	p->CarryOut = 0;
	return p;
}

void Conversao(int n, int* v, int MAX){
	int i;
	for (i = MAX-1; i >= 0; i--){
		v[i] = n % 2;
		n = n / 2;
	}
}

int Soma(int* v1, int* v2,int* result, int MAX){
	int i,CarryIn = 0;
	for (i = MAX-1; i>=0;i--)
	{
		CarryIn += v1[i] + v2[i];
		if (CarryIn > 1){
			result[i] = (CarryIn == 3)? 1 : 0;
			CarryIn = 1;
		}
		else{
			result[i] = CarryIn;
			CarryIn = 0;
		}
	}
	return CarryIn;
}

int* ComplementoA2(int* a, int MAX)
{
	int i;
	int* um = CriarBinario(MAX);
	int* s = CriarBinario(MAX);
	int* r = CriarBinario(MAX);
	Conversao(1, um, MAX);
	for (i = 0;i < MAX; i++)
	{
		if(a[i] == 1){
			r[i] = 0;
		}
		else{
			r[i] = 1;
		}
	}
	Soma(r, um, s, MAX);
	free(um);
	free(r);
	return s;
}

void Shift_Direita(Produto* p,int MAX){
	int i,aux2,aux = 0;
	for (i = 0; i < MAX; i++)
	{
		aux2 = p->Hi[i];
		p->Hi[i] = aux;
		aux = aux2;
	}
	for (i = 0; i< MAX; i++)
	{
		aux2 = p->Lo[i];
		p->Lo[i] = aux;
		aux = aux2;
	}
	p->CarryOut = aux;
}

