#include "Game.h"
#include "TextureManager.h"
#include"Components.h"
#include"Map.h"
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& Player(manager.addEntity());
/*không chắc về ý nghĩa cụ thể của từ khóa auto trong c++,
nhưng tôi nghĩ nó có nghĩa là biến 
newPlayer sẽ tự động nhận kiểu dữ liệu từ giá trị 
được gán cho nó*/
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
	Player.addComponent<PositionComponent>();
	Player.addComponent<SpriteComponent>("./assets/player.png");
}

void Game::handleEvents()
{
	SDL_Event event;

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
	manager.refresh();
	manager.update();

	if (Player.getComponent<PositionComponent>().x() > 100)
	{
		Player.getComponent<SpriteComponent>().setTex("./assets/enemy.png");
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();

	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}