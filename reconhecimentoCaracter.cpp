#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include "estruturas.h"
#include "constantes.h"
#include "traducaoImagem.h"
#include "treinamento.h"

using namespace std;

imagemBinaria atual;

pesos thetaZero;

int main()
{
	memset(thetaZero.w, 0, sizeof(thetaZero.w));
	treinamento(&thetaZero);
	// ----------- Variáveis do Jogo -----------

	int Esquerda = INF;
	int Direita = 0;
	int Cima = INF;
	int Baixo = 0;

	int pos_x, pos_y;
	bool fim = false;
	bool desenhar_ponto = false;

	vector <ponto> pintado;
	memset(atual.matriz, 0, sizeof(atual.matriz));

	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_DISPLAY *display = NULL;

	//_____________________________________________

	// --------- Inicialização ALLEGRO e Display ---------

	if (!al_init())
	{
		al_show_native_message_box(NULL, "AVISO!", "ERRO!", "ERRO AO INICIALIZAR A ALLEGRO!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	display = al_create_display(largura_tela, altura_tela);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(largura_tela/2 - largura_tela/fracao_retangulo1, 0, largura_tela/2 + largura_tela/fracao_retangulo1, altura_tela, al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(0, altura_tela - altura_tela/fracao_retangulo2 , largura_tela, altura_tela, al_map_rgb(0, 0, 0));
	al_flip_display();

	if (!display)
	{
		al_show_native_message_box(NULL, "AVISO!", "ERRO!", "ERRO AO tentar abrir janela!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;

	}

	//_____________________________________________

	// --------- Inicialização de addons e Instalações ---------
	al_install_keyboard();
	al_install_mouse();

	//_____________________________________________

	// --------- Fila e demais dispositivos ---------
	fila_eventos = al_create_event_queue();
	al_init_primitives_addon();


	//_____________________________________________


	//--------- Registro de Sources ------
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(display));
	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	//_____________________________________________

	//--------- Loop Principal ------
	//al_hide_mouse_cursor(display);
	int frame = 0;
	double timer = al_get_time();
	while(!fim)
	{
		bool reinicia = false;

		ALLEGRO_EVENT evento;

		//al_wait_for_event(fila_eventos, &evento);
		while (al_get_next_event(fila_eventos, &evento))
		{
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

					case ALLEGRO_KEY_T:
						gera_binario(pintado, Direita, Esquerda, Baixo, Cima, &atual, false);
						reinicia = true;
						int resp;
						resp = responde(atual, thetaZero);
						printf("%d\n",resp);
					break;



					case ALLEGRO_KEY_P:
						gera_binario(pintado, Direita, Esquerda, Baixo, Cima, &atual, true);
						reinicia = true;
						//int resp;
						//resp = responde();
						//printf("%d\n",resp);
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
			al_draw_filled_circle(pos_x, pos_y, 5, al_map_rgb(0,0,0));

			imagemBinaria nova;
			for (int i=0; i<N; i++)
				for (int j =0; j<M; j++)
					nova.matriz[i][j] = atual.matriz[i][j];
			gera_binario(pintado, Direita, Esquerda, Baixo, Cima, &nova, false);
			//reinicia = true;
			int resp;
			resp = responde(nova, thetaZero);
			printf("%d\n",resp);	
		}


		al_flip_display();

		if (reinicia)
		{
			al_rest(0.3);
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_filled_rectangle(largura_tela/2 - largura_tela/fracao_retangulo1, 0, largura_tela/2 + largura_tela/fracao_retangulo1, altura_tela, al_map_rgb(0, 0, 0));
			al_draw_filled_rectangle(0, altura_tela - altura_tela/fracao_retangulo2 , largura_tela, altura_tela, al_map_rgb(0, 0, 0));
			memset(atual.matriz, 0, sizeof(atual.matriz));
			pintado.clear();
			Esquerda = INF;
			Direita = 0;
			Cima = INF;
			Baixo = 0;

		}

		frame++;
		if (al_get_time() - timer > 1.0)
		{
			char buffer[256];
			sprintf(buffer, "FPS: %d\n", frame);
			al_set_window_title(display, buffer);
			frame = 0;
			timer = al_get_time();
		}
	}
	//_____________________________________________


	//--------- Finalização do Programa ------
	al_destroy_display(display);
	al_destroy_event_queue(fila_eventos);

	//_____________________________________________

	return 0;

}

/* vim: set ts=4 sw=4 noet : */
