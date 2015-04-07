#include <stdio.h>
#include <math.h>
#include <vector>

#include "constantes.h"
#include "estruturas.h"

using namespace std;

double sigmoid(double x) 
{
    double e = 2.718281828;
    return 1.0 / (1.0 + pow(e, -x));
}

resposta responde(imagemBinaria atual, pesos thetaZero)
{

	double z_i = 0;
	int sz = N*M + 1;
	int X[sz];
	X[0] = 1;
	int conta = 1;
	for (int i = 0; i<N; i++)
		for (int j = 0; j < M; j++)
			X[conta++] = atual.matriz[i][j];

	for (int j = 0; j < sz; ++j) 
    {
        z_i += ((thetaZero.w[j]) * X[j]);
	}

	z_i = sigmoid(z_i);
	//printf("Z:%.4lf\n\n",100*(1 - z_i));

	resposta SOLUCAO;

	if (z_i >= 0.5)
	{
		SOLUCAO.response = 0;
		SOLUCAO.probabilidade = 100*z_i;
	}

	else
	{
		SOLUCAO.response = 1;
		SOLUCAO.probabilidade = 100*(1 - z_i);
	} 
	
	return SOLUCAO;
}

vector <int> X[num_exemplos_Zero];

void treinamento(pesos *Thetazero)
{

	FILE *fin = fopen("zero.txt","r");
	FILE *fin2 = fopen("Y.txt","r");
	int a;
	int conta = 0;
	int n_exemplos;
	int y[num_exemplos_Zero + 10];
	
	for (int i = 0; i < num_exemplos_Zero; i++)
		X[i].push_back(0);

	while(fscanf(fin, "%d", &a) != EOF)
	{
		X[conta/(N*M)].push_back(a);
		conta++;
	}

	n_exemplos = conta/(N*M);
	
	double gamma = 0.005;
    int max_iters = 600;
    int iter = 0; 

    pesos novoThetaZero;
    int sz = N*M + 1;

    int conta2 = 0;
	while(fscanf(fin2,"%d",&y[conta2])!=EOF)
		conta2++;
	

	printf("%d\n",n_exemplos);
    while(iter++ <= max_iters)
    {
    
    	for (int k = 0; k < sz; k++)
    	{
    		double gradient = 0;
    		
    		for (int i=0; i < n_exemplos; i++) 
    		{
                double z_i = 0;
                
                for (int j=0; j < sz; ++j) 
                {
                	z_i += ((Thetazero->w[j]) * X[i][j]);
                	
    			}
    			
    			gradient +=  X[i][k] * (sigmoid(z_i) - y[i]);

    		}
    		gradient/=sz;

    		novoThetaZero.w[k] = (Thetazero->w[k]) + gamma * gradient;
    		
    	}
    	
    	 for (int i = 0; i < sz; i++)
    	 	if (Thetazero->w[i]!=novoThetaZero.w[i])
    	 		{
    	 			
    	 			Thetazero->w[i] = novoThetaZero.w[i];
    	 		}
	}


	fclose(fin);
	fclose(fin2);
}