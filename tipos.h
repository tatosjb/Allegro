#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

#define CHUMBO	0
#define ACO		1
#define FERRO	2

struct castle{
	int vida;
	int dano;
	void  set(){
		vida = 5000;
		dano = 0;
	}
	void addDano(int d){
		dano +=d;
	}
	int vidaAtual(){
		return vida-dano;
	}

};
struct municao{
	int dano, peso, tipo;
	double mod;
};
struct canhao{
	int quantidade;
	int peso;
	int danoTotal;
	int danoMedio;
	int tipo;
	municao *tiros;
};


#endif // !TIPOS_H_INCLUDED
