#include "Game.h"
#include "TextureManager.h"
#include"Components.h"
#include"Map.h"
#include"Vector2D.h"
#include"Collision.h"
#include"Background.h"
Map* map;
Background* background;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


std::vector<ColliderComponent*> Game::colliders;

auto& Player(manager.addEntity());
auto& wall(manager.addEntity());


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
	background = new Background();

	Player.addComponent<TransformComponent>(2);
	Player.addComponent<SpriteComponent>("./assets/player.png");
	Player.addComponent<KeyboardController>();
	Player.addComponent<ColliderComponent>("player");
	
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("./assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
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
	Vector2D playerPos = Player.getComponent<TransformComponent>().position;
	manager.refresh();
	manager.update();
	for (auto cc : colliders)
	{
	  Collision::AABB(Player.getComponent<ColliderComponent>(), *cc);
	}
}


void Game::render()
{
	SDL_RenderClear(renderer);
	background->DrawBackground();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
void:: Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
}