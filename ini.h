#ifndef INI_H_INCLUDED
#define INI_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <iostream>

bool inicializa(){
	// Inicialização de bibliotecas
	if(!al_init()){
		cout<<"Erro ao inicializar allegro";
		return false;
	}
	if(!al_init_image_addon()){
		cout<<"Erro ao inicializar imagem";
		return false;
	}
	if(!al_install_mouse()){
		cout<<"Erro ao inicializar mouse";
		return false;
	}
	if(!al_install_keyboard()){
		cout<<"Erro ao inicializar teclado";
		return false;
	}
	al_init_font_addon();
	if(!al_init_ttf_addon()){
		cout<<"Erro ao inicializar ttf";
		return false;
	}
	if(!al_install_audio()){
		cout<<"Erro ao inicializar audio";
		return false;
	}
	if(!al_init_acodec_addon()){
		cout<<"Erro ao inicializar acodec";
		return false;
	}
	al_reserve_samples(1);
	return true;
}


#endif