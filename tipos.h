#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

struct castelo{
	int vida;
	int dano;
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
	municao *tiros;
};


#endif // !TIPOS_H_INCLUDED
