while (!fim){
		//Define os eventos
		al_register_event_source(fila_eventos,al_get_mouse_event_source());
		//carrega fundo inicial
		imgfundo = al_load_bitmap("paisagem.jpg");
		al_draw_bitmap(imgfundo,0,0,0);
		//Enquando fila_eventos n�o for vazia
		while(!al_is_event_queue_empty(fila_eventos)){
			//Verifica o movimento do mouse
			ALLEGRO_EVENT evento;
			//Espera por um evento(�timo para n�o gastar recursos de processamento em v�o.. ;D)
			al_wait_for_event(fila_eventos,&evento);
			if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				//Valida��es Bot�o Jogar
				if(
					evento.mouse.x > w/2-al_get_bitmap_width(botaojogar)/2 && evento.mouse.x < w/2+al_get_bitmap_width(botaojogar)/2 &&
					evento.mouse.y > 300 && evento.mouse.y < 300 + al_get_bitmap_height(botaojogar)
					)
				{
					botaojogar = al_load_bitmap("jogarsel.png");
					al_draw_bitmap(botaojogar,w/2-100,300,0);
				}else
				{
					//Bot�o Jogar
					botaojogar = al_load_bitmap("jogar.png");
					al_draw_bitmap(botaojogar,w/2-100,300,0);
				}

				//Valida��es Bot�o Sair
				if(
					evento.mouse.x > w/2-al_get_bitmap_width(botaosair)/2 && evento.mouse.x < w/2+al_get_bitmap_width(botaosair)/2 &&
					evento.mouse.y > 320+al_get_bitmap_height(botaojogar) && evento.mouse.y < 300 + al_get_bitmap_height(botaosair) + al_get_bitmap_height(botaojogar)
					)
				{
					botaojogar = al_load_bitmap("sairsel.png");
					al_draw_bitmap(botaojogar,w/2-100,300,0);
				}else
				{
					//Bot�o Sair
					botaosair = al_load_bitmap("sair.png");
					al_draw_bitmap(botaosair,w/2-100,al_get_bitmap_height(botaojogar)+320,0);
				}
			}
		}
		//Desenha os gr�ficos
		al_flip_display();
	}