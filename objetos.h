#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "organizacao.h"
#include "tipos.h"
#include "util.h"

using namespace std;

void inline geraCanhao(canhao *canhaoRato, int qtd){
	for(int i=0;i<3;i++)
		canhaoRato[i].tiros = new municao[qtd];

	for(int t = 0;t<3;t++){
		canhaoRato[t].tipo = t;
		for(int i=0;i<qtd;i++){
			canhaoRato[t].tiros[i].dano = ajustaDano(rd(1000,i),qtd);
			canhaoRato[t].tiros[i].peso = rd(50,i);
			canhaoRato[t].tiros[i].tipo = t;
			canhaoRato[t].tiros[i].mod = (float)canhaoRato[t].tiros[i].dano/(float)canhaoRato[t].tiros[i].peso;
		}
		quickSort(canhaoRato[t].tiros,0,qtd-1);
		inverteMatriz(canhaoRato[t].tiros,qtd);
		canhaoRato[t].quantidade = balancear(canhaoRato[t],qtd,t);
		canhaoRato[t].danoTotal = danoTotal(canhaoRato[t],canhaoRato[t].quantidade);
		canhaoRato[t].danoMedio = danoMedio(canhaoRato[t],canhaoRato[t].quantidade);
		canhaoRato[t].peso = pesoTotal(canhaoRato[t].tiros,canhaoRato[t].quantidade);
	}
}
#endif