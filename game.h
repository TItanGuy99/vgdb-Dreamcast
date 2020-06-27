/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include <fstream>
#include <iostream>             //if we want to write out something, probobly it can be deleted if you don't want
#include <vector>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "base.h"
#include "player.h"
//#include "bullet.h"
//#include "enemy.h"
#include "obstacle.h"
#include "vmu.h"
#ifndef GAME_H
#define GAME_H
#include <kos.h>

class game:public baseclass{
	SDL_Joystick *joystick;
	int counter, total_counter, half_total, buttonCount;
	bool showjaguar;
	SDL_Surface *screen, *jaguar, *m_screen, *v_letter, *g_letter, *d_letter, *b_letter, *vgdb_logo;
	SDL_Rect camera, v_rect, g_rect, d_rect, b_rect, logo_rect;
	SDL_Surface* load_image(const char* filename); 
	void animation();
	void handleEvents();
	bool running;
	static const int SCREEN_WIDTH=320;
	static const int SCREEN_HEIGHT=240;
	player* player1;
        public:
        game();
        ~game();
        void start();
};

#endif
