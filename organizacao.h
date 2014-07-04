#ifndef ORGANIZACAO_H_INCLUDED
#define ORGANIZACAO_H_INCLUDED

#include "tipos.h"

bool inverteMatriz(municao *valor, int tam, int pos=0){
	if(pos==(tam+1)/2){
		return true;
	}
	municao bkp = valor[pos];
	valor[pos] = valor[tam-pos-1];
	valor[tam-pos-1] = bkp;
	return (inverteMatriz(valor,tam,pos+1));
}

void quickSort(municao valor[], int esquerda, int direita){
	int i, j;
	municao  x, y;
	j = direita;
	i = esquerda;
	x = valor[(esquerda + direita) / 2];

	while(i <= j)
	{
		while(valor[i].mod < x.mod && i < direita)
		{
			i++;
		}
		while(valor[j].mod > x.mod && j > esquerda)
		{
			j--;
		}
		if(i <= j)
		{
			y = valor[i];
			valor[i] = valor[j];
			valor[j] = y;

			i++;
			j--;
		}
	}
	if(j > esquerda)
	{
		quickSort(valor, esquerda, j);
	}
	if(i < direita)
	{
		quickSort(valor,  i, direita);
	}

}

void quickSortTipo(municao valor[], int esquerda, int direita)
{
	int i, j;
	municao  x, y;
	i = esquerda;
	j = direita;
	x = valor[(esquerda + direita) / 2];

	while(i <= j)
	{
		while(valor[i].tipo < x.tipo && i < direita)
		{
			i++;
		}
		while(valor[j].tipo > x.tipo && j > esquerda)
		{
			j--;
		}
		if(i <= j)
		{
			y = valor[i];
			valor[i] = valor[j];
			valor[j] = y;

			i++;
			j--;
		}
	}
	if(j > esquerda)
	{
		quickSortTipo(valor, esquerda, j);
	}
	if(i < direita)
	{
		quickSortTipo(valor,  i, direita);
	}
}


#endif