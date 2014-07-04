#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "organizacao.h"
#include "tipos.h"
#include "util.h"

using namespace std;

#define CHUMBO	0
#define ACO		1
#define FERRO	2

#define NORTE	1
#define SUL		2
#define LESTE	3
#define OESTE	4

void geraCanhao(canhao *canhaoRato, int qtd){
	for(int i=0;i<3;i++)
		canhaoRato[i].tiros = new municao[qtd];

	for(int t = 0;t<3;t++){
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


	//--------------------------> Abaixo somente testes em console para verificação das saídas <----------------------

	/*for(int i=0;i<3;i++){
		for(int ii=canhaoRato[i].quantidade; ii >=0;ii--){
			cout <<i<<" - "<<ii<<" Peso: "<<canhaoRato[i].tiros[ii].peso<<endl;
		}
	}*/

	/*for(int tt = 0;tt<3;tt++){
	system("cls");
	for(int i=0;i<qtd;i++){
	cout<<i<<" - Dano: "<<canhaoRato[tt].tiros[i].dano<<endl;
	cout<<i<<" - Peso: "<<canhaoRato[tt].tiros[i].peso<<endl;
	cout<<i<<" - Tipo: "<<canhaoRato[tt].tiros[i].tipo<<endl;
	cout<<i<<" - MOD: "<<(double)canhaoRato[tt].tiros[i].mod<<endl<<endl;
	}
	system("pause");
	}*/
}
#endif