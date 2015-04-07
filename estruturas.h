#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "constantes.h"

struct resposta
{
	int response;
	double probabilidade;

};

struct imagemBinaria
{
	int matriz[N][M];
};

struct pesos
{
	double w[N*M + 1];
};

struct ponto
{
	int x, y;
};

#endif 