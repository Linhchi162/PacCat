#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "ECS.h"
#include"Map.h"


static Engine engine;

class Game
{
public:
	static const unsigned TILE_SIZE;
	static const unsigned HALF_TILE_SIZE;
	static const unsigned WINDOW_WIDTH;
	static const unsigned WINDOW_HEIGHT;



	static Map* map;

	static bool isRunning;
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;

private:

	int cnt = 0;
	SDL_Window* window;
};