

	int main()
	{

	

	//_____________________________________________

	// --------- Inicialização de addons e Instalações ---------
	al_install_keyboard();
	al_install_mouse();

	//_____________________________________________

	// --------- Fila e demais dispositivos ---------
	fila_eventos = al_create_event_queue();
	al_init_primitives_addon();


	//____________0_________________________________


	//--------- Registro de Sources ------
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(display));
	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	//_____________________________________________


	//--------- Loop Principal ------
	//al_hide_mouse_cursor(display);
	while(!fim)
	{
		bool reinicia = false;

		ALLEGRO_EVENT evento;

		al_wait_for_event(fila_eventos, &evento);
		//--------- Eventos e Lógica------
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				fim = true;
			}

			switch(evento.keyboard.keycode)
			{
				case ALLEGRO_KEY_C:
				reinicia = true;
				break;

				case ALLEGRO_KEY_P:
				int deltaX = abs(Direita - Esquerda);
				int deltaY = abs(Cima - Baixo);
				int sz = pintado.size();
				for (int i = 0; i < sz; i++)
					{
						int X;
						if (deltaX!=0)
							 X = 7*(pintado[i].x - Esquerda)/deltaX;
						else X = 4;
						int Y;
						if (deltaY!=0)
						Y = 11*(abs(pintado[i].y - Cima))/deltaY;
						else Y = 6;
						
						matriz[Y][X] = 1;
					}
						for (int i=0;i<12;i++)
						{
							for (int j=0;j<8;j++)
								printf("%d ",matriz[i][j]);
							printf("\n");
						}
				printf("end\n");
				reinicia = true;
				treinamento();
				break;
					
			}

		}

		else if (evento.type == ALLEGRO_EVENT_KEY_UP)
		{

				reinicia = false;
		}

		else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			fim = true;
		}

		else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			
			pos_x = evento.mouse.x;
			pos_y = evento.mouse.y;
		}

		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
		
			if (evento.mouse.button & 1)
			{
				pos_x = evento.mouse.x;
				pos_y = evento.mouse.y;
				desenhar_ponto = true;
				
			}


		}

		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (evento.mouse.button & 1)
			{
				pos_x = evento.mouse.x;
				pos_y = evento.mouse.y;
				desenhar_ponto = false;
			}
		}

		
		
	//_____________________________________________


	//--------- DESENHO ------
		if (desenhar_ponto)
		{
				ponto novo;
				novo.x = pos_x;
				novo.y = pos_y;
				Esquerda = min(Esquerda, pos_x);
				Direita = max(Direita, pos_x);
				Cima = min(Cima, pos_y);
				Baixo = max(Baixo, pos_y);

				pintado.push_back(novo);
		 	al_draw_filled_ellipse(evento.mouse.x, evento.mouse.y, 5, 5, al_map_rgb(0,0,0));
		}


		al_flip_display();
		if (reinicia)
		{
			al_rest(0.3);
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_filled_rectangle(largura_tela/2 - largura_tela/100, 0, largura_tela/2 + largura_tela/100, altura_tela, al_map_rgb(0, 0, 0));
			al_draw_filled_rectangle(0, altura_tela - altura_tela/5 , largura_tela, altura_tela, al_map_rgb(0, 0, 0));
			memset(matriz,0,sizeof(matriz));
			pintado.clear();
			Esquerda = INF;
			Direita = 0;
			Cima = INF;
			Baixo = 0;

			 
		}
		
	}
	//_____________________________________________


	//--------- Finalização do Programa ------
	al_destroy_display(display);
	al_destroy_event_queue(fila_eventos);


	//_____________________________________________

	return 0;

}