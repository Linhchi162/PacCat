
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

	TTF_Init();

	font = TTF_OpenFont("./assets/arial.ttf", 50);

	gamelevel = new GameLevel();
	gamelevel->LoadLevel();

	
	resetTexture = LoadText("Reset", { 0, 255, 255 }, font, renderer);

	youWin = LoadTexture("./assets/background.png", renderer);
	wallTexture = LoadTexture("./assets/wall.png", renderer);
	groundTexture = LoadTexture("./assets/ground.png", renderer);
	boxTexture = LoadTexture("./assets/box.png", renderer);
	goalTexture = LoadTexture("./assets/goal.png", renderer);

	menu = new Menu(renderer);
	cat = new Cat(this, renderer);
	SDL_Rect resetButtonRect = { SCREEN_WIDTH / 2 - 300, 300, 50, 20 };
	resetButton = new Button(renderer, resetTexture, resetButtonRect);
	

	InitLevel();

	return true;
}

void Game::GameLoop() {
	while (isRunning) {
	
		HandleEvents();
		if (isMenuVisible) {
			SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
			SDL_RenderClear(renderer);
			menu->Render();   // Vẽ màn hình menu
			SDL_RenderPresent(renderer);
		}
		else {
			Update();
			Draw();
			
		}
		
	}

}


void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		// Nếu đang hiển thị màn hình menu, kiểm tra sự kiện để chuyển sang màn hình chơi game
		if (isMenuVisible) {
			if (menu->HandleEvent(&event)) {
				isMenuVisible = false;  // Chuyển sang màn hình chơi game
			}
		}
		else{
			if (resetButton->IsClicked()) {
				DestroyBoxes();
				InitLevel();
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
				case SDLK_n:
					GoToNextLevel();
					break;
				case SDLK_p:
					GoToPreviousLevel();
				default:
					break;
				}
				
			}
		}
	}



	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
}



void Game::Update()
{

}

void Game::Draw()
{
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);


	for (int r = 0; r < TILE_ROWS; r++) {
		for (int c = 0; c < TILE_COLS; c++) {
			SDL_Rect rect = { c * TILE_SIZE, r * TILE_SIZE, TILE_SIZE, TILE_SIZE };

			if (gamelevel->levelMap[c][r] == 'x') {
				SDL_RenderCopy(renderer, wallTexture, NULL, &rect);
			}
			else if (gamelevel->levelMap[c][r] == 'g') {
				SDL_RenderCopy(renderer, goalTexture, NULL, &rect);
			}
			else {
				SDL_RenderCopy(renderer, groundTexture, NULL, &rect);
			}
		}
	}

	// vẽ box
	for (int i = 0; i < boxes.size(); i++) {
		SDL_RenderCopy(renderer, boxTexture, NULL, boxes[i]->GetRect());
	}

	cat->Draw(renderer);
	resetButton->Render();
	SDL_RenderPresent(renderer);
}

bool Game::HitWall(int x, int y) {
	return gamelevel->levelMap[x][y] == 'x';
}
bool Game::CanPushBox(Box* box, int x, int y) {

	// Exit if trying to push into wall
	if (HitWall(x, y)) {
		return false;
	}

	// Exit if trying to push into another box
	for (int i = 0; i < boxes.size(); i++) {
		if (boxes[i] == box) {
			continue;
		}
		else if (x == boxes[i]->GetPos().x && y == boxes[i]->GetPos().y) {
			return false;
		}
	}

	return true;
}
bool Game::BoxUpdated(int moveX, int moveY, int pX, int pY) {
	Box* boxToPush = nullptr;

	// Find box attempting to push
	for (int i = 0; i < boxes.size(); i++) {
		if (pX == boxes[i]->GetPos().x && pY == boxes[i]->GetPos().y) {
			boxToPush = boxes[i];
		}
	}

	// Check if we can push the box, and if so, update the box
	if (boxToPush != nullptr) {
		int toPushX = pX + moveX;
		int toPushY = pY + moveY;

		if (CanPushBox(boxToPush, toPushX, toPushY)) {
			bool inGoal = HitGoal(toPushX, toPushY);
			boxToPush->Update(toPushX, toPushY, inGoal);
			if (AllGoalsComplete()) {
				GoToNextLevel();
				return false;
			}
		}
		else {
			return false;
		}
	}

	return true;
}
bool Game::HitGoal(int x, int y) {
	return gamelevel->levelMap[x][y] == 'g';
}

bool Game::AllGoalsComplete() {
	for (int i = 0; i < boxes.size(); i++) {
		if (!boxes[i]->GetInGoal()) {
			return false;
		}
	}

	return true;
}
void Game::DestroyBoxes() {
	// Clean vector
	for (int i = 0; i < boxes.size(); i++)
	{
		delete boxes[i];
	}
	boxes.erase(boxes.begin(), boxes.end());
}

void Game::InitLevel() {
	// Reset Player and add new boxes
	for (int r = 0; r < TILE_ROWS; r++) {
		for (int c = 0; c < TILE_COLS; c++) {
			if (gamelevel->levelMap[c][r] == 'p') {
				cat->Reset(c, r);
			}
			else if (gamelevel->levelMap[c][r] == 'b') {
				boxes.emplace_back(new Box(c, r));
			}
		}
	}
}

void Game::GoToNextLevel() {
	DestroyBoxes();

	// Go to next level
	gamelevel->UpdateLevel();
	gamelevel->LoadLevel();

	InitLevel();
}
void Game::GoToPreviousLevel()
{
	DestroyBoxes();
	gamelevel->PreviousLevel();
	gamelevel->LoadLevel();

	InitLevel();


}

void Game::Shutdown() {
	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(groundTexture);
	SDL_DestroyTexture(boxTexture);
	SDL_DestroyTexture(goalTexture);
	SDL_DestroyTexture(resetTexture);
	SDL_DestroyTexture(youWin);
	delete resetButton;
	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

