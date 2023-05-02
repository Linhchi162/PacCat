
#include"Collision.h"
#include"KeyboardController.h"
#include"Math.h"
#include"PacManController.h"
#include <string>



SDL_Event Game::event;
Map* Game::map = nullptr;
SDL_Renderer* Game::renderer = nullptr;





PacmanController* pacman;

bool Game::isRunning = false;


Game::Game()
{}

Game::~Game()
{}
/*void RegisterComponents()
{
	engine.RegisterComponent<Transform>();
	engine.RegisterComponent<TextureRenderer>();
	engine.RegisterComponent<Collider>();
	engine.RegisterComponent<KeyboardController>();
	engine.RegisterComponent<PacmanController>();
}

void RegisterSystems()
{
	renderSystem = engine.RegisterSystem<RenderSystem>();
	collisionSystem = engine.RegisterSystem<CollisionSystem>();
}

void SetSystemsSignatures()
{
	Signature renderSignature;
	renderSignature.set(engine.GetComponentType<TextureRenderer>());
	engine.SetSystemSignature<RenderSystem>(renderSignature);

	Signature collideSignature;
	collideSignature.set(engine.GetComponentType<Collider>());
	engine.SetSystemSignature<Collider>(collideSignature);
}

void InitPacman()
{
	Entity pacmanEntity = engine.CreateEntity();

	engine.AddComponent(pacmanEntity, Transform{ PACMAN_START_XPOS, PACMAN_START_YPOS, Game::TILE_SIZE, Game::TILE_SIZE });
	engine.AddComponent(pacmanEntity, TextureRenderer{ TextureManager::LoadTexture("assets/Pacman/lookingRight.png") });
	engine.AddComponent(pacmanEntity, Collider{ { 0, 0, COLLIDER_BOX_SIZE, COLLIDER_BOX_SIZE} });
	engine.AddComponent(pacmanEntity, KeyboardController{ false, false, false, false });
	engine.AddComponent(pacmanEntity, PacmanController(pacmanSpeed, engine, pacmanEntity));

	pacman = &engine.GetComponent<PacmanController>(pacmanEntity);
}*/

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
	//engine.Init();

	//RegisterComponents();
	//RegisterSystems();
	//SetSystemsSignatures();


	map = new Map();


	//engine.CreateEntity();

	//InitPacman();
	

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
/*bool Game::IsPacmanInGhostHouse()
{
	int pacmanTileX = 0;
	int pacmanTileY = 0;

	CoordinatesToTiles(pacmanTileX, pacmanTileY, pacman->GetPosX(), pacman->GetPosY());

	return (pacmanTileX == 8 || pacmanTileX == 9 || pacmanTileX == 10) // Currently fixed. Changes in map might require changes here!
		&& (pacmanTileY == 8 || pacmanTileY == 9 || pacmanTileY == 10);
}*/



void Game::update()
{
	pacman->Update();


	/*collisionSystem->CheckForCollisions();*/

}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	//renderSystem->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}