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

void escreveCanhao(ALLEGRO_FONT *fonte,canhao *canhaoRato, int ini_pos_x, int ini_pos_y, int th, int t){
	al_draw_textf(fonte,al_map_rgb(255,0,0),ini_pos_x+10,ini_pos_y+th-60,ALLEGRO_ALIGN_LEFT, "Dano Total: %d",(int)canhaoRato[t].danoTotal);
	al_draw_textf(fonte,al_map_rgb(255,0,0),ini_pos_x+10,ini_pos_y+th-40,ALLEGRO_ALIGN_LEFT, "Peso Total: %d",(int)canhaoRato[t].peso);
	al_draw_textf(fonte,al_map_rgb(255,0,0),ini_pos_x+10,ini_pos_y+th-80,ALLEGRO_ALIGN_LEFT, "Quantidade: %d",(int)canhaoRato[t].quantidade);
	al_draw_textf(fonte,al_map_rgb(255,0,0),ini_pos_x+10,ini_pos_y+th-20,ALLEGRO_ALIGN_LEFT, "Dano Medio: %d",(int)canhaoRato[t].danoMedio);
}

bool final(bool vitoria, ALLEGRO_DISPLAY *display, int x, int y,ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_AUDIO_STREAM *control, ALLEGRO_FONT *fonte){
	char *msg;
	bool fim=false,botao[4]={false,false,false,false};
	ALLEGRO_BITMAP *fd = NULL;
	fonte = al_load_font("fonte.ttf",50,0);
	if(vitoria){
		msg = "Minnie agora passa bem!";
	}else{
		msg = "Minnie continua no castelo!";
	}
	control = al_load_audio_stream("end.ogg",2,1024);
	al_attach_audio_stream_to_mixer(control,al_get_default_mixer());
	al_set_audio_stream_playing(control,true);
	al_set_audio_stream_gain(control,0.3);
	al_set_audio_stream_playmode(control,ALLEGRO_PLAYMODE_LOOP);

	fd = al_create_bitmap(x,y);
	for(int i=0;i<30;i++){
		Sleep(20);
		al_set_target_bitmap(fd);
		al_clear_to_color(al_map_rgb(255,255,255));
		al_clear_to_color(al_map_rgba(0,0,0,i));
		al_set_target_bitmap(al_get_backbuffer(display));
		al_draw_bitmap(fd,0,0,0);
		al_flip_display();
	}
	al_draw_text(fonte,al_map_rgb(255,255,255),x/2,y/2-150,ALLEGRO_ALIGN_CENTRE,msg);
	al_draw_text(fonte,al_map_rgb(255,255,255),x/2-10,y-150,ALLEGRO_ALIGN_CENTRE,"Jogar Outra");
	al_draw_text(fonte,al_map_rgb(255,255,255),x/2-10,y-100,ALLEGRO_ALIGN_CENTRE,"Sair");
	al_flip_display();

	while(!fim){
		al_register_event_source(fila_eventos,al_get_mouse_event_source());
		while(!al_event_queue_is_empty(fila_eventos) && !fim){
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos,&evento);
			if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				botao[0]=
					evento.mouse.y > y-150 && evento.mouse.y < y-150+al_get_font_line_height(fonte) &&
					evento.mouse.x > x/2 -al_get_text_width(fonte,"Jogar Outra")/2-10 && evento.mouse.x < x/2+al_get_text_width(fonte,"Jogar Outra")/2
					;
				botao[1]=
					evento.mouse.y > y-100 && evento.mouse.y < y-100+al_get_font_line_height(fonte) &&
					evento.mouse.x > x/2 -al_get_text_width(fonte,"Sair")/2-10 && evento.mouse.x < x/2+al_get_text_width(fonte,"Sair")/2
					;
				if(botao[0] && !botao[2]){
					botao[2] = true;
					al_draw_text(fonte,al_map_rgb(0,0,0),x/2-10,y-150,ALLEGRO_ALIGN_CENTRE,"Jogar Outra");
				}else if(!botao[0] && botao[2]){
					botao[2] = false;
					al_draw_text(fonte,al_map_rgb(255,255,255),x/2-10,y-150,ALLEGRO_ALIGN_CENTRE,"Jogar Outra");
				}
				if(botao[1] && !botao[3]){
					botao[3] = true;
					al_draw_text(fonte,al_map_rgb(0,0,0),x/2-10,y-100,ALLEGRO_ALIGN_CENTRE,"Sair");
				}else if(!botao[1] && botao[3]){
					botao[3] = false;
					al_draw_text(fonte,al_map_rgb(255,255,255),x/2-10,y-100,ALLEGRO_ALIGN_CENTRE,"Sair");
				}
				if(botao[0] || botao[1]){
					al_set_system_mouse_cursor(display,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				}else{
					al_set_system_mouse_cursor(display,ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
				}
				al_flip_display();
			}
			if(evento.mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if(botao[0]){
					al_destroy_bitmap(fd);
					al_destroy_audio_stream(control);
					return false;
				}
				if(botao[1]){
					al_destroy_bitmap(fd);
					al_destroy_audio_stream(control);
					return true;
				}
			}
		}
	}
	return true;
}

bool escolheArma(ALLEGRO_DISPLAY *display, int w, int h,ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_AUDIO_STREAM *control){

	ALLEGRO_BITMAP *cChumbo=NULL, *cAco = NULL, *cFerro=NULL,*cChumboSel=NULL, *cAcoSel = NULL, *cFerroSel=NULL, *imgfundo=NULL;
	fila_eventos = al_create_event_queue();
	ALLEGRO_FONT *fonte=NULL;
	//Controle de áudio
	al_destroy_audio_stream(control);
	control = al_load_audio_stream("fd2.ogg",2,1024);
	al_set_audio_stream_playing(control,true);
	al_attach_audio_stream_to_mixer(control,al_get_default_mixer());
	al_set_audio_stream_gain(control,0.3);
	al_set_audio_stream_playmode(control,ALLEGRO_PLAYMODE_LOOP);

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
	imgfundo = al_load_bitmap("fundo.jpg");
	al_draw_bitmap(imgfundo,0,0,0);
	//Carrega canhões
	cChumbo = al_load_bitmap("cchumbo.png");
	cAco = al_load_bitmap("caco.png");
	cFerro = al_load_bitmap("cferro.png");
	cChumboSel = al_load_bitmap("cchumbosel.png");
	cAcoSel = al_load_bitmap("cacosel.png");
	cFerroSel = al_load_bitmap("cferrosel.png");
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
					al_destroy_audio_stream(control);
					break;
				}
			}
			if(evento.type == ALLEGRO_EVENT_MOUSE_AXES && !fim){
				//Verifica mouse sobre botão 1
				al_draw_bitmap(imgfundo,0,0,0);
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

			al_flip_display();
			if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && !fim){
				cout<<evento.type<<"\t"<< ALLEGRO_EVENT_MOUSE_BUTTON_DOWN<<endl;
				cout<<evento.type<<"\t"<< ALLEGRO_EVENT_MOUSE_BUTTON_DOWN<<endl;
				if(botao1){
					al_set_system_mouse_cursor(display,ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
					al_destroy_audio_stream(control);
					fim = final(playAGame(canhaoRato[CHUMBO],control,display,fila_eventos,w,h),display,w,h,fila_eventos,control,fonte);
					if(fim){
						return true;
					}
					geraCanhao(canhaoRato,50);
					control = al_load_audio_stream("fd2.ogg",2,1024);
					al_draw_bitmap(imgfundo,0,0,0);
					al_set_audio_stream_playing(control,true);
					al_attach_audio_stream_to_mixer(control,al_get_default_mixer());
					al_set_audio_stream_gain(control,0.3);
					al_set_audio_stream_playmode(control,ALLEGRO_PLAYMODE_LOOP);
				}
				if(botao2){
					al_set_system_mouse_cursor(display,ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
					al_destroy_audio_stream(control);
					fim = final(playAGame(canhaoRato[ACO],control,display,fila_eventos,w,h),display,w,h,fila_eventos,control,fonte);
					if(fim){
						return true;
					}
					geraCanhao(canhaoRato,50);
					control = al_load_audio_stream("fd2.ogg",2,1024);
					al_draw_bitmap(imgfundo,0,0,0);
					al_set_audio_stream_playing(control,true);
					al_attach_audio_stream_to_mixer(control,al_get_default_mixer());
					al_set_audio_stream_gain(control,0.3);
					al_set_audio_stream_playmode(control,ALLEGRO_PLAYMODE_LOOP);
				}
				if(botao3){
					al_set_system_mouse_cursor(display,ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
					al_destroy_audio_stream(control);
					fim = final(playAGame(canhaoRato[FERRO],control,display,fila_eventos,w,h),display,w,h,fila_eventos,control,fonte);
					if(fim){
						return true;
					}
					geraCanhao(canhaoRato,50);
					al_draw_bitmap(imgfundo,0,0,0);
					control = al_load_audio_stream("fd2.ogg",2,1024);
					al_set_audio_stream_playing(control,true);
					al_attach_audio_stream_to_mixer(control,al_get_default_mixer());
					al_set_audio_stream_gain(control,0.3);
					al_set_audio_stream_playmode(control,ALLEGRO_PLAYMODE_LOOP);
				}
			}
		}
	}while(!fim);
	for(int i=0;i<3;i++)
		delete canhaoRato[i].tiros;
	delete canhaoRato;
	return false;
}

void resetScream(int h, int w, ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *imgfundo=NULL,ALLEGRO_BITMAP *botaojogar=NULL,ALLEGRO_BITMAP *botaosair=NULL){
	al_draw_bitmap(imgfundo,0,0,0);
	al_draw_bitmap(botaojogar,w/2-100,300,0);
	al_draw_bitmap(botaosair,w/2-100,al_get_bitmap_height(botaojogar)+320,0);
	al_draw_text(fonte,al_map_rgb(255,0,0),w-10,10,ALLEGRO_ALIGN_RIGHT,"Pressione F1 para ajuda!");
	al_flip_display();
}

void menu(){
	// Variável representando a janela principal
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *imgfundo = NULL, *botaojogar=NULL, *botaosair=NULL, *botaojogarSel=NULL, *botaosairSel=NULL, *help = NULL;
	ALLEGRO_EVENT_QUEUE *fila_eventos=NULL;
	ALLEGRO_AUDIO_STREAM *control=NULL;
	ALLEGRO_SAMPLE *audio=NULL;
	ALLEGRO_FONT *fonte=NULL;
	int w = 1000,h = 480;
	bool fim = false,botao1=true, botao2=true;

	// Criação da janela
	janela = al_create_display(w, h);
	al_set_window_title(janela,"Go Go Mouse");
	al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	botaosair = al_create_bitmap(100,50);
	fila_eventos =	al_create_event_queue();
	al_register_event_source(fila_eventos,al_get_mouse_event_source());
	int na_area_central = 0;

	help= al_load_bitmap("ajuda.png");//Tutorial
	//carrega fundo inicial
	imgfundo = al_load_bitmap("fundo.jpg");
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
	control = al_load_audio_stream("fundo.ogg",2,1024);
	al_attach_audio_stream_to_mixer(control,al_get_default_mixer());
	al_set_audio_stream_playing(control,true);
	al_set_audio_stream_gain(control,0.3);
	fonte = al_load_font("fonte.ttf",40,0);
	al_draw_text(fonte,al_map_rgb(255,0,0),w-10,10,ALLEGRO_ALIGN_RIGHT,"Pressione F1 para ajuda!");
	//trilha("fundo.ogg",audio,ALLEGRO_PLAYMODE_LOOP);
	while (!fim){
		//Desenha os gráficos
		al_flip_display();
		//Define os eventos
		al_register_event_source(fila_eventos,al_get_mouse_event_source());
		al_register_event_source(fila_eventos,al_get_keyboard_event_source());
		//Enquando fila_eventos não for vazia
		while(!al_is_event_queue_empty(fila_eventos)){
			al_flip_display();
			//Verifica o movimento do mouse
			ALLEGRO_EVENT evento;
			//Espera por um evento(Ótimo para não gastar recursos de processamento em vão.. ;D)
			al_wait_for_event(fila_eventos,&evento);
			if(evento.keyboard.keycode == ALLEGRO_KEY_F1){
				evento.keyboard.keycode = NULL;
				al_draw_bitmap(help,0,0,0);
				al_flip_display();
				Sleep(500);
				al_flush_event_queue(fila_eventos);
				while(evento.keyboard.keycode!=ALLEGRO_KEY_ESCAPE){
					al_wait_for_event(fila_eventos,&evento);
				}
				resetScream(h,w,fonte,imgfundo,botaojogar,botaosair);
			}
			if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				//Redesenha mapa
				al_draw_bitmap(imgfundo,0,0,0);
				al_draw_text(fonte,al_map_rgb(255,0,0),w-10,10,ALLEGRO_ALIGN_RIGHT,"Pressione F1 para ajuda!");
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
				if (botao1){
					al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
					//Chama segundo menu
					fim = escolheArma(janela,w,h,fila_eventos,control);
					//Reseta informações
					if(!fim){
						al_flush_event_queue(fila_eventos);
						resetScream(h,w,fonte,imgfundo,botaojogar,botaosair);
						control = al_load_audio_stream("fundo.ogg",4,1024);
						al_set_audio_stream_playing(control,true);
						al_attach_audio_stream_to_mixer(control,al_get_default_mixer());
						al_set_audio_stream_gain(control,0.3);
						botao1 = false;
						break;
					}
					break;
				}
				//Verifica o fim do jogo
				if (botao2){
					// finaliza a janela
					fim = true;
					break;
				}
			}
		}
	}
	al_destroy_display(janela);
	al_destroy_bitmap(botaojogar);
	al_destroy_bitmap(botaosair);
	al_destroy_bitmap(botaojogarSel);
	al_destroy_bitmap(botaosairSel);
	al_destroy_bitmap(imgfundo);
	al_destroy_bitmap(help);
	al_destroy_event_queue(fila_eventos);
	al_destroy_sample(audio);
}
#endif //MENU_H_INCLUDED