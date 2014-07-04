#ifndef PLAY_H_INCLUDED
#define PLAY_H_INCLUDED


void playAGame(ALLEGRO_DISPLAY *display,ALLEGRO_EVENT_QUEUE *fila_eventos, int w, int h, int tw, int th){
	ALLEGRO_BITMAP *fundo, *tiro, *castelo, *canhao, *chao;
	chao = al_load_bitmap("chao.jpg");
	fundo = al_load_bitmap("bggame.jpg");
	tiro = al_load_bitmap("tiro.png");
	castelo = al_load_bitmap("castelo.png");
	canhao = al_load_bitmap("canhao.png");


}


#endif // !PLAY_H_INCLUDED