#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <iostream>
#include <time.h>
#include "tipos.h"

using namespace std;

int rd(int maximo, int var){
	return ((rand()^clock()^var)%maximo)+1;
}

int danoTotal(canhao c,int qtd,int i=0){
	if(qtd-1<=i){
		return (int)c.tiros[i].dano;
	}
	return c.tiros[i].dano+danoTotal(c,qtd,i+1);
}

int danoMedio(canhao c,int qtd,int i=0){
	if(qtd-1<=i){
		return (int)c.tiros[i].dano;
	}
	return (danoTotal(c,qtd))/qtd;
}

int balancear(canhao c,int qtd,int tipo, int i=0,int peso=0){
	if(peso+c.tiros[i].peso>50 && tipo < 2){
		return i;
	}
	if(peso+c.tiros[i].peso>60 && tipo == 2){
		return i;
	}
	return balancear(c,qtd,tipo,i+1,peso+c.tiros[i].peso);
}

int pesoTotal(municao *m,int qtd,int i=0){
	if(i==qtd-1){
		return m[i].peso;
	}
	return m[i].peso+pesoTotal(m,qtd,i+1);
}

int ajustaDano(int d, int qtd){
	if(qtd==50){
		return d;
	}else{
		return d-((50-qtd)*3/100*d);
	}
}

#endif // !UTIL_H_INCLUDED
