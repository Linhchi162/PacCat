﻿
#include "Game.h"


Game::Game()
{}

Game::~Game()
{}

bool Game::Init()
{
	TTF_Init();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
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


	LoadResources();

	resetButton = new Button(renderer, resetButtonTexture, resetButtonRect);
	menuButton = new Button(renderer, menuButtonTexture, menuButtonRect);
	DisapearButton = new Button(renderer, DisappearButtonTexture, DisappearButtonRect);


	gamelevel = new GameLevel();
	gamelevel->LoadLevel();
	menu = new Menu(renderer);
	cat = new Cat(this, renderer);
	timer = new Timer();

	timer->start();
	timeLimit = 300000;


	InitLevel();

	return true;

}


void Game::LoadResources() {
	// Load textures
	wallTexture = LoadTexture("./assets/Wall.png", renderer);
	groundTexture = LoadTexture("./assets/ground.png", renderer);
	boxTexture = LoadTexture("./assets/box.png", renderer);
	goalTexture = LoadTexture("./assets/goal.png", renderer);

	// Load Button
	resetButtonTexture = LoadTexture("./assets/Replay.png", renderer);
	menuButtonTexture = LoadTexture("./assets/Home.png", renderer);
	DisappearButtonTexture = LoadTexture("./assets/Home.png", renderer);

	//Load font
	font = TTF_OpenFont("./assets/Daydream.ttf", 40);


	//LoadScreen
	youWin = LoadTexture("./assets/Win.png", renderer);
	levelclear = LoadTexture("./assets/levelClear.png", renderer);

	// Load sounds
	nextLevelSound = Mix_LoadMUS(NEXT_LEVEL_PATH);
	nextLevelMeowSound = Mix_LoadWAV(NEXT_LEVEL_MEOW_PATH);
	WinSound = Mix_LoadMUS(WIN_SOUND_PATH);
	
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}

		// When menu screen is visible
		if (isMenuVisible) {
			menu->HandleEvent(&event);
			if (menu->IsLevelScreenVisible())
			{
				
				isMenuVisible = true;
				if (menu->IsLevelChoosed()) {
					GoToLevel();
					menu->SetLevelScreen(false);
					isMenuVisible = false;	
				}
				
				
			}
	
			if (menu->IsResumeClicked())
			{
				menu->SetResumeClicked(false);
				SDL_Delay(200);
				isMenuVisible = false;
			}
		}
		else {
			// Reset Button
			if (resetButton->IsClicked()) {
				DestroyBoxes();
				InitLevel();
			}
			// Return Menu Button
			if (menuButton->IsClicked())
			{
				InGame = true;
				isMenuVisible = true;

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

void Game::GameLoop() {
	while (isRunning) {

		HandleSound();
		HandleEvents();
		if (isMenuVisible) {
			// Render the menu Screen

			SDL_SetRenderDrawColor(renderer, NULL, NULL, NULL, NULL);
			SDL_RenderClear(renderer);
			menu->Render();
			if (InGame)
			{
				menu->RenderResume();
			}
			SDL_RenderPresent(renderer);
			// Switch to Game Screen when Start Button is pressed
			if (menu->IsStartPressed()) {
				SDL_Delay(200);
				menu->SetStartPressed(false);

				ResetGame();

				InGame = false;
				isMenuVisible = false;
			}

		}

		else {
			Update();
			Render();

		}

	}
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

	for (int i = 0; i < boxes.size(); i++)
	{
		delete boxes[i];
	}
	boxes.erase(boxes.begin(), boxes.end());
}
void Game::HandleSound()
{

	if (menu->IsMuted())
	{
		TurnOffMusic();
	}
	else
	{
		TurnOnMusic();
	}
}
void Game::TurnOnMusic()
{
	Mix_Volume(-1, MIX_MAX_VOLUME);

}
void Game::TurnOffMusic()
{
	Mix_Volume(-1, 0);
	Mix_HaltMusic();

}


void Game::InitLevel() {
	// Reset Player and add new box

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
	timer->start();
	timeLimit = 300000;
}

void Game::GoToLevel()
{

	DestroyBoxes();
	gamelevel->ResetLevelTo(menu->LevelNumber());
	gamelevel->LoadLevel();

	InitLevel();
	

}


void Game::GoToNextLevel() {
	DestroyBoxes();

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
void Game::ResetGame()
{
	DestroyBoxes();
	gamelevel->ResetLevel();
	gamelevel->LoadLevel();
	InitLevel();
}
void Game::RenderLevelCompletScreen()
{
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, levelclear, NULL, &ScreenDst);
	SDL_RenderPresent(renderer);
}
void Game::RenderAllLevelCompletScreen()
{
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, youWin, NULL, &ScreenDst);
	SDL_RenderPresent(renderer);
}
void Game::RenderYouLoseScreen()
{
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, youWin, NULL, &ScreenDst);
	SDL_RenderPresent(renderer);
}
void Game::Update()
{
	Uint32 currentTime = timer->getTicks();
	int elapsed = timeLimit - currentTime;

	if (elapsed <= 0) {
		RenderYouLoseScreen();
		SDL_Delay(2000);


		ResetGame();

		isMenuVisible = true;

		return;
	}

	if (AllGoalsComplete())
	{
		if (gamelevel->GetCurrentLevel() < gamelevel->GetTotalLevel())
		{
			// Draw the Level clear screen before updating to the next level
			RenderLevelCompletScreen();

			if (!menu->IsMuted()) {
				Mix_PlayChannel(-1, nextLevelMeowSound, 0);
				Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
				Mix_VolumeChunk(nextLevelMeowSound, MIX_MAX_VOLUME * 3);
				Mix_PlayMusic(nextLevelSound, 0);
			}
			// Wait for an additional 1 second before changing to the next level
			SDL_Delay(1000);
			GoToNextLevel();

		}
		else
		{
			// Draw the Win Screen
			RenderAllLevelCompletScreen();


			// Sound 
			if (!menu->IsMuted()) {
				Mix_PlayMusic(WinSound, 0);
				Mix_PlayChannel(-1, nextLevelMeowSound, 0);
			}

			//  Wait for an additional 3 second 
			SDL_Delay(3000);

			// reset the game
			ResetGame();
			
			InGame = false;
			isMenuVisible = true;
		}
	}

}

void Game::Render()
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

			// make box disappear if Disappear Button is pressed
			if (DisapearButton->m_isPressed)
			{
				for (int i = 0; i < boxes.size(); i++) {
					if (gamelevel->levelMap[c][r] == 'g') {
						SDL_RenderCopy(renderer, goalTexture, NULL, &rect);
					}
					if (gamelevel->levelMap[c][r] == 'b')
						SDL_RenderCopy(renderer, groundTexture, NULL, &rect);
				}

			}
			else {
				// Draw box
				for (int i = 0; i < boxes.size(); i++) {
					SDL_RenderCopy(renderer, boxTexture, NULL, boxes[i]->GetRect());
				}
			}
		}
	}
	cat->Draw(renderer);

	menuButton->Render();
	resetButton->Render();
	DisapearButton->Render();

	TimerRender();

	SDL_RenderPresent(renderer);

}
void Game::TimerRender()
{

	Uint32 currentTime = timer->getTicks();
	int seconds = (timeLimit - currentTime) / 1000;
	int minutes = seconds / 60;

	std::string timeText = "Time Remainning : " + std::to_string(minutes) + ":" + std::to_string(seconds % 60);

	SDL_Color textColor = { 0xF5, 0xDE, 0xB3, 0xFF };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, timeText.c_str(), textColor);

	if (textSurface) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		if (textTexture) {
			SDL_Rect textRect = { 220 , 10, 400, 50 };
			SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
			SDL_DestroyTexture(textTexture);
		}
		SDL_FreeSurface(textSurface);
	}
}

void Game::Shutdown() {


	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(groundTexture);
	SDL_DestroyTexture(boxTexture);
	SDL_DestroyTexture(goalTexture);
	SDL_DestroyTexture(resetButtonTexture);
	SDL_DestroyTexture(youWin);
	SDL_DestroyTexture(levelclear);
	SDL_DestroyTexture(DisappearButtonTexture);
	SDL_DestroyTexture(menuButtonTexture);
	SDL_DestroyTexture(resetButtonTexture);


	Mix_FreeChunk(nextLevelMeowSound);
	Mix_FreeMusic(nextLevelSound);
	Mix_FreeMusic(WinSound);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

