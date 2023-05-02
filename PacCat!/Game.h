#pragma once
#ifndef _GAME_HEADER_INCLUDED_
#define _GAME_HEADER_INCLUDED_
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include"Box.h"
#include<string>



class Game
{
public:


	Game();
	~Game();

	bool Init();
	void GameLoop();
	void Shutdown();
	bool BoxUpdated(int moveX, int moveY, int pX, int pY);



private:

	SDL_Texture* LoadTexture(string path);
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* wallTexture = nullptr;
	SDL_Texture* groundTexture = nullptr;
	SDL_Texture* boxTexture = nullptr;


	class LevelManager* levelManager;

	vector<Box*> boxes;


	bool isRunning = true;

};

#endif