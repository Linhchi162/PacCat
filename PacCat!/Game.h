#pragma once
#ifndef _GAME_HEADER_INCLUDED_
#define _GAME_HEADER_INCLUDED_
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include"Map.h"



class Game
{
public:



	static Map* map;

	static bool isRunning;
	Game();
	~Game();

	//static void PacmanCollidingWith(const Entity& ghost);
	//static bool IsPacmanInGhostHouse();
	//static void FrightenGhosts();
	//static void IncrementScore();



	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;

private:

	SDL_Window* window;
};

#endif