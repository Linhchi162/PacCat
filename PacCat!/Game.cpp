#include "Game.h"
#include"TextureManager.h"
#include"Components.h"
#include"CollisionSystem.h"
#include"KeyboardController.h"
#include"Math.h"
#include"PacManController.h"
#include <string>
#include"Map.h"


int scoreForWinning = -1; // negative => the number of dots on map. Change this value to a positive int to 
// explicitly set the amount of score to be required for winning.

const unsigned COLLIDER_BOX_SIZE = 20; // these collider boxes are used for Pacman/Ghosts colliding logic




const unsigned Game::TILE_SIZE = 32; // Textures are 32x32p. Having higher tile size will decrease quality and might affect speeds.
const unsigned Game::HALF_TILE_SIZE = Game::TILE_SIZE / 2;
const unsigned Game::WINDOW_WIDTH = tilesCountX * Game::TILE_SIZE; // tilesCount is stored in the Map file
const unsigned Game::WINDOW_HEIGHT = tilesCountY * Game::TILE_SIZE;


const int pacmanSpeed = 2;

SDL_Event Game::event;
Map* Game::map = nullptr;
SDL_Renderer* Game::renderer = nullptr;





PacmanController* pacman;

bool Game::isRunning = false;


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}


	map = new Map();

}


void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}



void Game::update()
{

}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}