#ifndef PLAY_H_INCLUDED
#define PLAY_H_INCLUDED

#include <iostream>
#include <time.h>

#include "tipos.h"
#include "util.h"
int inline mira(ALLEGRO_DISPLAY *display, int x, int y, ALLEGRO_EVENT_QUEUE *fila_eventos){
	ALLEGRO_BITMAP *pBar, *status;
	int bx, by=10, px, t=5;
	int val=100,mod=2;
	pBar = al_load_bitmap("mira.jpg");
	status = al_load_bitmap("line.jpg");
	bx=x-10-al_get_bitmap_width(pBar);
	px=bx+al_get_bitmap_width(pBar)/2;
	al_flush_event_queue(fila_eventos);
	al_register_event_source(fila_eventos,al_get_keyboard_event_source());
	ALLEGRO_EVENT evento;
	do{
		Sleep(5);
		al_wait_for_event_timed(fila_eventos,&evento,0.0005);
		al_draw_bitmap(pBar,bx,by,0);
		if(px>=bx+al_get_bitmap_width(pBar) || px<=bx){
			t*=-1;
		}
		if(val==100 || val==0){
			mod*=-1;
		}
		px+=t;
		val+= mod;
		al_draw_bitmap(status,px,by+1,0);
		al_flip_display();
	}while(evento.keyboard.keycode != ALLEGRO_KEY_SPACE);
	return val;
}
void inline life(int x, int y,castle cast){
	al_set_clipping_rectangle(x-322,y-22,304,24);
	al_clear_to_color(al_map_rgb(255,255,50));
	al_set_clipping_rectangle(x-20-cast.vidaAtual()*300/cast.vida,y-20,cast.vidaAtual()*300/cast.vida,20);
	al_clear_to_color(al_map_rgb(255,0,0));
	al_reset_clipping_rectangle();
}

bool inline playAGame(canhao c,ALLEGRO_AUDIO_STREAM *control,ALLEGRO_DISPLAY *display,ALLEGRO_EVENT_QUEUE *fila_eventos, int x, int y){
	ALLEGRO_BITMAP *tiro=NULL, *castelo=NULL, *canhao=NULL, *chao=NULL,*area=NULL,*lifebar = NULL,*lifefundo=NULL;
	ALLEGRO_AUDIO_STREAM *stiro, *scanhao, *scastelo;
	ALLEGRO_COLOR impt[2];
	ALLEGRO_FONT *fonte;
	castle cast;
	impt[0] = al_map_rgb(10,19,207);
	int cx,cy,ax=NULL,ay=NULL, t=0;
	bool fim=false;

	lifebar = al_create_bitmap(300,20);
	lifefundo = al_create_bitmap(302,22);
	//Carregando arquivos (Para evitar ter de acessar o HD durante a execução do jogo)
	stiro = al_load_audio_stream("Tiro.ogg",4,1024);
	scanhao = al_load_audio_stream("canhao.ogg",4,1024);
	scastelo = al_load_audio_stream("castelo.ogg",4,1024);
	chao = al_load_bitmap("chao.jpg");
	tiro = al_load_bitmap("tiro.png");
	castelo = al_load_bitmap("castelo.jpg");
	canhao = al_load_bitmap("canhao.jpg");
	area = al_create_bitmap(10,10);

	al_set_target_bitmap(area);
	al_clear_to_color(al_map_rgb(10,19,207));
	al_set_target_bitmap(lifefundo);
	al_clear_to_color(al_map_rgb(255,255,0));
	al_set_target_bitmap(lifebar);
	al_clear_to_color(al_map_rgb(255,0,0));
	al_set_target_bitmap(al_get_backbuffer(display));

	//Música de fundo
	control = al_load_audio_stream("fd3.ogg",2,1024);
	al_set_audio_stream_playing(control,true);
	al_attach_audio_stream_to_mixer(control,al_get_default_mixer());
	al_set_audio_stream_gain(control,0.3);
	al_set_audio_stream_playmode(control,ALLEGRO_PLAYMODE_LOOP);
	ax = x-al_get_bitmap_width(castelo);
	ay = rd(170,4)+101;
	//rd 100 à 270
	al_draw_bitmap(chao,0,0,0);
	al_draw_bitmap(area,ax,ay,0);
	cx=50;
	cy=y/2-al_get_bitmap_height(canhao)/2;
	al_draw_bitmap(canhao,cx,cy,0);
	al_draw_bitmap(castelo,x-al_get_bitmap_width(castelo),0,0);

	//Inicia castelo
	cast.set(); //Seta valores

	al_draw_bitmap(area,ax,ay,0);
	life(x,y,cast);//Barra de vida

	fonte = al_load_font("fonte.ttf",20,0);
	al_draw_textf(fonte,al_map_rgba(0,0,0,150),10,10,ALLEGRO_ALIGN_RIGHT,"Munição restante: %d %s",(int)c.quantidade," tiros.");

	al_flip_display();
	al_flush_event_queue(fila_eventos);
	//Efeito
	al_register_event_source(fila_eventos,al_get_keyboard_event_source());
	do{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos,&evento);
		if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
			fim=true;
			break;
		}
		ax=x-al_get_bitmap_width(castelo);
		while(al_is_event_queue_empty(fila_eventos) && !fim){
			if(evento.keyboard.keycode == ALLEGRO_KEY_W || evento.keyboard.keycode == ALLEGRO_KEY_UP){
				if(cy-3>0){
					efeito(scanhao,ALLEGRO_PLAYMODE_LOOP,0.7);
					al_draw_bitmap(chao,0,0,0);
					cy-=3;
				}
			}
			if(evento.keyboard.keycode == ALLEGRO_KEY_S || evento.keyboard.keycode == ALLEGRO_KEY_DOWN){
				if(cy+3<y-al_get_bitmap_height(canhao)){
					efeito(scanhao,ALLEGRO_PLAYMODE_LOOP,0.7);
					al_draw_bitmap(chao,0,0,0);
					cy+=3;
				}
			}
			if(evento.keyboard.type == ALLEGRO_EVENT_KEY_UP){
				evento.keyboard.keycode = NULL;
				al_rewind_audio_stream(scanhao);
				al_set_audio_stream_playing(scanhao,false);
			}
			if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
				int ix=NULL,iy=NULL,dx=NULL,dy=NULL;
				float cax=NULL,cay=NULL,mx=NULL,my=NULL;
				cax = cx+al_get_bitmap_width(canhao);
				cay = cy+al_get_bitmap_height(canhao)/2-12;
				if(mira(display,x,y,fila_eventos)>=rd(100,17)){
					efeito(stiro,ALLEGRO_PLAYMODE_ONCE,0.7);
					dx = ax-cax;
					dy = ay-cay;
					mx = 1;
					my = (float)dy/(float)dx;
					do{
						cax+=mx;
						cay+=my;
						al_draw_bitmap(chao,0,0,0);
						al_draw_bitmap(canhao,cx,cy,0);
						al_draw_bitmap(tiro,cax,cay,0);
						al_draw_bitmap(castelo,x-al_get_bitmap_width(castelo),0,0);
						al_draw_bitmap(area,ax,ay,0);
						al_draw_textf(fonte,al_map_rgba(0,0,0,150),10,10,ALLEGRO_ALIGN_LEFT,"Municao restante: %d %s",(int)c.quantidade-t," tiros.");
						life(x,y,cast);//Barra de vida
						al_flip_display();
						Sleep(1);
					}while(ax>cax);
				}else{
					efeito(stiro,ALLEGRO_PLAYMODE_ONCE,0.7);
					do{
						cax+=1;
						al_draw_bitmap(chao,0,0,0);
						al_draw_bitmap(canhao,cx,cy,0);
						al_draw_bitmap(tiro,cax,cay,0);
						al_draw_bitmap(castelo,x-al_get_bitmap_width(castelo),0,0);
						al_draw_bitmap(area,ax,ay,0);
						al_draw_textf(fonte,al_map_rgba(0,0,0,150),10,10,ALLEGRO_ALIGN_LEFT,"Municao restante: %d %s",(int)c.quantidade-t," tiros.");
						life(x,y,cast);//Barra de vida
						al_flip_display();
						Sleep(1);
					}while(ax>cax);
				}
				impt[1] = al_get_pixel(area,cax+al_get_bitmap_width(area)/2-ax,cay+al_get_bitmap_height(area)/2-ay);
				//impt[1] = al_get_pixel(area,5,5);
				if(impt[1].r == impt[0].r && impt[1].g == impt[0].g && impt[1].b == impt[0].b){
					if(c.tipo == CHUMBO){
						if(cast.vidaAtual()>cast.vida/2 && cast.vidaAtual()-c.tiros[t].dano*1.3<cast.vida/2){
							castelo = al_load_bitmap("castelo2.jpg");
						}
						cast.addDano(c.tiros[t].dano*1.3);
					}else if(c.tipo == ACO && rd(100,t)+2<30){
						if(cast.vidaAtual()>cast.vida/2 && cast.vidaAtual()-c.tiros[t].dano*2<cast.vida/2){
							castelo = al_load_bitmap("castelo2.jpg");
						}
						cast.addDano(c.tiros[t].dano*2);
						cout<<"Dano Crítico";
					}else{
						cast.addDano(c.tiros[t].dano);
					}
					t++;
					ay = rd(170,4)+101;
					//gerencia lifebar
					cout<<cast.vidaAtual()<<endl<<c.quantidade-t<<endl;
					//Redesenha senário
				}else{
					t++;
					ay = rd(170,4)+101;
					//gerencia lifebar
					cout<<cast.vidaAtual()<<endl<<c.quantidade-t<<endl;

				}
			}
			al_rewind_audio_stream(stiro);
			al_set_audio_stream_playing(stiro,false);
			if(t>c.quantidade || cast.vidaAtual() < 1){
				castelo = al_load_bitmap("castelo3.jpg");
				al_draw_bitmap(chao,0,0,0);
				al_draw_bitmap(canhao,cx,cy,0);
				al_draw_bitmap(castelo,x-al_get_bitmap_width(castelo),0,0);
				al_draw_bitmap(area,ax,ay,0);
				al_draw_textf(fonte,al_map_rgba(0,0,0,150),10,10,ALLEGRO_ALIGN_LEFT,"Municao restante: %d %s",(int)c.quantidade-t," tiros.");
				fim=true;
				break;
			}
			al_draw_bitmap(chao,0,0,0);
			al_draw_bitmap(canhao,cx,cy,0);
			al_draw_bitmap(castelo,x-al_get_bitmap_width(castelo),0,0);
			life(x,y,cast);//Barra de vida
			al_draw_bitmap(area,ax,ay,0);
			al_draw_textf(fonte,al_map_rgba(0,0,0,150),10,10,ALLEGRO_ALIGN_LEFT,"Municao restante: %d %s",(int)c.quantidade-t," tiros.");
			al_flip_display();
			Sleep(50);
		}
	}while(!fim && t<c.quantidade);

	al_destroy_audio_stream(control);
	al_flush_event_queue(fila_eventos);
	al_destroy_bitmap(lifebar);
	al_destroy_bitmap(lifefundo);
	al_destroy_bitmap(tiro);
	al_destroy_bitmap(castelo);
	al_destroy_bitmap(canhao);
	al_destroy_bitmap(chao);
	al_destroy_bitmap(area);
	al_destroy_audio_stream(stiro);
	al_destroy_audio_stream(scanhao);
	al_destroy_audio_stream(scastelo);

	if(cast.vidaAtual() < 1){
		return true;
	}

	return false;
}


#endif // !PLAY_H_INCLUDED