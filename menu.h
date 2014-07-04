#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>

#include "objetos.h"
#include "tipos.h"
#include "play.h"
#include <iostream>

using namespace std;

int trilha(char *nome, ALLEGRO_PLAYMODE mode,ALLEGRO_SAMPLE_ID *id=NULL){
	ALLEGRO_SAMPLE *audio=NULL;
	audio = al_load_sample(nome);
	
	al_play_sample(audio,0.2,0.0,1.0,mode,id);
	if(!audio){
		cout<<"Não carregou essa porra de fundo.wav";
		return -1;
	}
}
void escreveCanhao(ALLEGRO_FONT *fonte,canhao *canhaoRato, int ini_pos_x, int ini_pos_y, int th, int t){
	al_draw_textf(fonte,al_map_rgb(255,0,0),ini_pos_x+10,ini_pos_y+th-60,ALLEGRO_ALIGN_LEFT, "Dano Total: %d",(int)canhaoRato[t].danoTotal);
	al_draw_textf(fonte,al_map_rgb(255,0,0),ini_pos_x+10,ini_pos_y+th-40,ALLEGRO_ALIGN_LEFT, "Peso Total: %d",(int)canhaoRato[t].peso);
	al_draw_textf(fonte,al_map_rgb(255,0,0),ini_pos_x+10,ini_pos_y+th-80,ALLEGRO_ALIGN_LEFT, "Quantidade: %d",(int)canhaoRato[t].quantidade);
	al_draw_textf(fonte,al_map_rgb(255,0,0),ini_pos_x+10,ini_pos_y+th-20,ALLEGRO_ALIGN_LEFT, "Dano Medio: %d",(int)canhaoRato[t].danoMedio);
}

void escolheArma(ALLEGRO_DISPLAY *display, int w, int h,ALLEGRO_EVENT_QUEUE *fila_eventos){

	ALLEGRO_BITMAP *cChumbo=NULL, *cAco = NULL, *cFerro=NULL,*cChumboSel=NULL, *cAcoSel = NULL, *cFerroSel=NULL, *imgfundo=NULL;
	fila_eventos = al_create_event_queue();
	ALLEGRO_FONT *fonte=NULL;
	bool fim=false,botao1=false,botao2=false,botao3=false;;
	char texto[2];
	municao *tiros;
	int tw = 300, th = 400, espaco=20, qtd=3,ini_pos_x=0,ini_pos_y=0;
	canhao *canhaoRato = new canhao[3];
	geraCanhao(canhaoRato,50);
	fonte = al_load_font("fonte.ttf",20,0);
	if(!fonte){
		cout<<"Error 404 Font Not Found";
	}
	//Reseta fundo
	imgfundo = al_load_bitmap("paisagem.jpg");
	al_draw_bitmap(imgfundo,0,0,0);
	//Carrega canhões
	cChumbo = al_load_bitmap("cchumbo.jpg");
	cAco = al_load_bitmap("caco.jpg");
	cFerro = al_load_bitmap("cferro.jpg");
	cChumboSel = al_load_bitmap("cchumbosel.jpg");
	cAcoSel = al_load_bitmap("cacosel.jpg");
	cFerroSel = al_load_bitmap("cferrosel.jpg");
	//Desenha canhão de Chumbo
	ini_pos_x = w/2-(tw*qtd+(espaco*(qtd-1)))/2;
	ini_pos_y = h/2 - th/2;
	al_draw_bitmap(cChumbo,ini_pos_x,ini_pos_y,0);
	escreveCanhao(fonte,canhaoRato,ini_pos_x,ini_pos_y,th,CHUMBO);
	//Desenha canhão de Aço
	ini_pos_x = ini_pos_x+tw+espaco;
	al_draw_bitmap(cAco,ini_pos_x,ini_pos_y,0);
	escreveCanhao(fonte,canhaoRato,ini_pos_x,ini_pos_y,th,ACO);
	//Desenha canhão de Ferro
	ini_pos_x = ini_pos_x+tw+espaco;
	al_draw_bitmap(cFerro,ini_pos_x,ini_pos_y,0);	
	escreveCanhao(fonte,canhaoRato,ini_pos_x,ini_pos_y,th,FERRO);
	//Altera display
	al_flip_display();
	do{
		//al_flush_event_queue(fila_eventos);
		al_register_event_source(fila_eventos,al_get_keyboard_event_source());
		al_register_event_source(fila_eventos,al_get_mouse_event_source());
		al_flip_display();
		if(fim){
			break;
		}
		while(!al_is_event_queue_empty(fila_eventos) && !fim){
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos,&evento);
			if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
				if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					fim=true;
					break;
				}
			}
			if(evento.type == ALLEGRO_EVENT_MOUSE_AXES && !fim){
				//Verifica mouse sobre botão 1
				ini_pos_x = w/2-(tw*qtd+(espaco*(qtd-1)))/2;
				botao1 = 
					evento.mouse.x >= ini_pos_x && evento.mouse.x <= ini_pos_x+tw &&
					evento.mouse.y >= ini_pos_y && evento.mouse.y <= ini_pos_y+th;
				if(botao1){
					al_draw_bitmap(cChumboSel,ini_pos_x,ini_pos_y,0);
				}else{
					al_draw_bitmap(cChumbo,ini_pos_x,ini_pos_y,0);
				}
				escreveCanhao(fonte,canhaoRato,ini_pos_x,ini_pos_y,th,CHUMBO);
				//Verifica mouse sobre botão 2
				ini_pos_x += tw+espaco;
				botao2=
					evento.mouse.x >= ini_pos_x && evento.mouse.x <= ini_pos_x+tw &&
					evento.mouse.y >= ini_pos_y && evento.mouse.y <= ini_pos_y+th;
				if(botao2){
					al_draw_bitmap(cAcoSel,ini_pos_x,ini_pos_y,0);
				}else{
					al_draw_bitmap(cAco,ini_pos_x,ini_pos_y,0);
				}
				escreveCanhao(fonte,canhaoRato,ini_pos_x,ini_pos_y,th,ACO);
				//Verifica mouse sobre botão 3
				ini_pos_x += tw+espaco;
				botao3=
					evento.mouse.x >= ini_pos_x && evento.mouse.x <= ini_pos_x+tw &&
					evento.mouse.y >= ini_pos_y && evento.mouse.y <= ini_pos_y+th;
				if(botao3){
					al_draw_bitmap(cFerroSel,ini_pos_x,ini_pos_y,0);
				}else{
					al_draw_bitmap(cFerro,ini_pos_x,ini_pos_y,0);
				}
				escreveCanhao(fonte,canhaoRato,ini_pos_x,ini_pos_y,th,FERRO);
				//Define cursor
				if(botao1 || botao2 || botao3){
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				}else{
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
				}
			}
			if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && !fim){
				cout<<evento.type<<"\t"<< ALLEGRO_EVENT_MOUSE_BUTTON_DOWN<<endl;
				cout<<evento.type<<"\t"<< ALLEGRO_EVENT_MOUSE_BUTTON_DOWN<<endl;
				if(botao1){
					cout<<"Botao 1"<<endl;
					al_flush_event_queue(fila_eventos);
				}
				if(botao2){
					cout<<"Botao 2"<<endl;
					al_flush_event_queue(fila_eventos);
				}
				if(botao3){
					cout<<"Botao 3"<<endl;
					al_flush_event_queue(fila_eventos);
				}
			}
		}
	}while(!fim);
	for(int i=0;i<3;i++)
		delete canhaoRato[i].tiros;
	delete canhaoRato;
}
void resetScream(int h, int w, ALLEGRO_BITMAP *imgfundo=NULL,ALLEGRO_BITMAP *botaojogar=NULL,ALLEGRO_BITMAP *botaosair=NULL){
	al_draw_bitmap(imgfundo,0,0,0);
	al_draw_bitmap(botaojogar,w/2-100,300,0);
	al_draw_bitmap(botaosair,w/2-100,al_get_bitmap_height(botaojogar)+320,0);
	al_flip_display();
}

void menu(){
	// Variável representando a janela principal
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *imgfundo = NULL, *botaojogar=NULL, *botaosair=NULL, *botaojogarSel=NULL, *botaosairSel=NULL;
	ALLEGRO_EVENT_QUEUE *fila_eventos=NULL;

	int w = 1000,h = 480;
	bool fim = false;


	// Criação da janela
	janela = al_create_display(w, h);
	al_set_window_title(janela,"Mikey caça princesa");
	al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	botaosair = al_create_bitmap(100,50);
	fila_eventos =	al_create_event_queue();
	al_register_event_source(fila_eventos,al_get_mouse_event_source());
	int na_area_central = 0;

	//carrega fundo inicial
	imgfundo = al_load_bitmap("paisagem.jpg");
	al_draw_bitmap(imgfundo,0,0,0);
	//carrega botões
	//Jogar
	botaojogarSel = al_load_bitmap("jogarSel.png");
	botaojogar = al_load_bitmap("jogar.png");
	al_draw_bitmap(botaojogar,w/2-100,300,0);
	//Sair
	botaosairSel = al_load_bitmap("sairSel.png");	
	botaosair = al_load_bitmap("sair.png");
	al_draw_bitmap(botaosair,w/2-100,al_get_bitmap_height(botaojogar)+320,0);
	bool botao1=true, botao2=true;
	trilha("fundo.ogg",ALLEGRO_PLAYMODE_LOOP);
	while (!fim){
		//Desenha os gráficos
		al_flip_display();
		//Define os eventos
		al_register_event_source(fila_eventos,al_get_mouse_event_source());
		//Enquando fila_eventos não for vazia
		while(!al_is_event_queue_empty(fila_eventos)){
			al_flip_display();
			//Verifica o movimento do mouse
			ALLEGRO_EVENT evento;
			//Espera por um evento(Ótimo para não gastar recursos de processamento em vão.. ;D)
			al_wait_for_event(fila_eventos,&evento);
			if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				//Redesenha mapa
				al_draw_bitmap(imgfundo,0,0,0);
				//Validações Botão Jogar
				botao1 = 
					evento.mouse.x > w/2-al_get_bitmap_width(botaojogar)/2 && evento.mouse.x < w/2+al_get_bitmap_width(botaojogar)/2 &&
					evento.mouse.y > 300 && evento.mouse.y < 300 + al_get_bitmap_height(botaojogar);
				if(botao1){
					al_draw_bitmap(botaojogarSel,w/2-100,300,0);
				}else{
					//Botão Jogar
					al_draw_bitmap(botaojogar,w/2-100,300,0);
				}

				//Validações Botão Sair
				botao2 = evento.mouse.x > w/2-al_get_bitmap_width(botaosair)/2 && evento.mouse.x < w/2+al_get_bitmap_width(botaosair)/2 &&
					evento.mouse.y > 320+al_get_bitmap_height(botaojogar) && evento.mouse.y < 320 + al_get_bitmap_height(botaosair) + al_get_bitmap_height(botaojogar);
				if(botao2){
					al_draw_bitmap(botaosairSel,w/2-100,al_get_bitmap_height(botaojogar)+320,0);
				}else{
					//Botão sair
					al_draw_bitmap(botaosair,w/2-100,al_get_bitmap_height(botaojogar)+320,0);
				}
				if(botao1 || botao2){
					al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				}else{
					al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
				}
			}else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
				//Leva para a escolha dos canhões
				if (botao1 && !botao2){
					al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
					escolheArma(janela,w,h,fila_eventos);
					al_flush_event_queue(fila_eventos);
					resetScream(h,w,imgfundo,botaojogar,botaosair);
					break;
				}
				//Verifica o fim do jogo
				if (!botao1 && botao2){
					// finaliza a janela
					fim = true;
					break;
				}
			}
		}
	}
	al_destroy_display(janela);
}
#endif //MENU_H_INCLUDED