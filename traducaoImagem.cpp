#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "constantes.h"
#include "estruturas.h"


using namespace std;



void gera_binario(vector<ponto> pintado, int Direita, int Esquerda, int Baixo, int Cima, imagemBinaria* atual, bool imprime)
{
	FILE *fout = fopen("zero.txt", "a");
	FILE *fout2 = fopen("Y.txt", "a");

	int deltaX = abs(Direita - Esquerda);
	int deltaY = abs(Cima - Baixo);
	int sz = pintado.size();
	for (int i = 0; i < sz; i++)
	{
		int X;
		if (deltaX!=0)
			 X = (N - 1)*(pintado[i].x - Esquerda)/deltaX;
		else 
			X = N/2;

		int Y;
		if (deltaY!=0)
			Y = (M-1)*(abs(pintado[i].y - Cima))/deltaY;
		else 
			Y = M/2;

		atual->matriz[Y][X] = 1;
	}

	if (imprime)
	{
		int y;
		scanf("%d",&y);
		fprintf(fout2,"%d\n",y);
		for (int i=0;i<N;i++)
		{
			for (int j=0;j<M;j++)
			{
				printf("%d ",atual->matriz[i][j]);
				fprintf(fout,"%d ",atual->matriz[i][j]);
			}
			printf("\n");
			fprintf(fout,"\n");
		}
		printf("\n\n");
		fprintf(fout,"\n\n");
		fclose(fout);
		fclose(fout2);
	}

}
