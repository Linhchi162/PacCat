
#include "Game.h"


Game::Game()
{}

Game::~Game()
{}

bool Game::Init()
{
if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		cout << "SDL failed to initialize: " << SDL_GetError() << endl;
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		cout << "SDL_Image failed to initialize: " << IMG_GetError() << endl;
		return false;
	}

	window = SDL_CreateWindow("PacCat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window) {
		cout << "Window failed to initialize: " << SDL_GetError() << endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		cout << "Renderer failed to initialize: " << SDL_GetError() << endl;
		return false;
	}

	gamelevel = new GameLevel();
	gamelevel->LoadLevel();


	wallTexture = LoadTexture("Assets/wall.png");
	groundTexture = LoadTexture("Assets/ground.png");
	boxTexture = LoadTexture("Assets/box.png");
	goalTexture = LoadTexture("Assets/goal.png");


	cat = new Cat(this);

	InitLevel();

	return true;
}

void Game::GameLoop() {
	while (isRunning) {
		HandleEvents();
		Update();
		Draw();
	}

}


void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				cat->Move(1, 0);
				break;
			case SDLK_LEFT:
				cat->Move(-1, 0);
				break;
			case SDLK_DOWN:
				cat->Move(0, 1);
				break;
			case SDLK_UP:
				cat->Move(0, -1);
				break;
			case SDLK_r:
				DestroyBoxes();
				InitLevel();
				break;
			case SDLK_s:
				GoToNextLevel();
				break;
			default:
				break;
			}
		}
}



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