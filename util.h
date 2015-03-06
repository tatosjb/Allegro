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
		if(peso<50){
			for(int j=i;j<qtd;j++){
				if(peso+c.tiros[j].peso<50){
					swap(c.tiros[i],c.tiros[j]);
					peso+=c.tiros[i].peso;
					i++;
				}
			}
		}
		return i;
	}
	if(peso+c.tiros[i].peso>60 && tipo == 2){
		if(peso<60){
			for(int j=i;j<qtd;j++){
				if(peso+c.tiros[j].peso<60){
					swap(c.tiros[i],c.tiros[j]);
					peso+=c.tiros[i].peso;
					i++;
				}
			}
		}
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
void efeito(ALLEGRO_AUDIO_STREAM *audio,ALLEGRO_PLAYMODE mode,float vol,bool atvd=true){
	al_set_audio_stream_playing(audio,atvd);
	al_attach_audio_stream_to_mixer(audio,al_get_default_mixer());
	al_set_audio_stream_gain(audio,vol);
	al_set_audio_stream_playmode(audio,mode);
}
#endif // !UTIL_H_INCLUDED
