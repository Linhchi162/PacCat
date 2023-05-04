#pragma once

#include <vector>
#include"Box.h"
#include"GameLevel.h"
#include"Cat.h"
#include"Menu.h"
#include <SDL_mixer.h>

class Game
{
public:


	Game();
	~Game();


	
	bool Init();
	void GameLoop();
	void Shutdown();
	bool BoxUpdated(int moveX, int moveY, int pX, int pY);
	bool HitWall(int x, int y);
	


private:

	
	void HandleEvents();
	void Update();
	void Draw();

	bool HitGoal(int x, int y);
	bool AllGoalsComplete();
	void DestroyBoxes();
	void InitLevel();
	void GoToNextLevel();
	void GoToPreviousLevel();
	bool CanPushBox(Box* box, int x, int y);


	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* resetTexture = nullptr;
	SDL_Texture* menuTexture = nullptr;
	SDL_Texture* wallTexture = nullptr;
	SDL_Texture* groundTexture = nullptr;
	SDL_Texture* boxTexture = nullptr;
	SDL_Texture* goalTexture = nullptr;
	SDL_Texture* youWin = nullptr;
	SDL_Texture* levelclear = nullptr;

	const char* NEXT_LEVEL_MEOW_PATH = "./assets/nextLevelmeow.wav";
    Mix_Chunk* nextLevelMeowSound = nullptr;

	const char* NEXT_LEVEL_PATH = "./assets/nextLevel.wav";
    Mix_Music* nextLevelSound = nullptr;

	const char* WIN_SOUND_PATH = "./assets/Win.wav";
	Mix_Music* WinSound = nullptr;

	class GameLevel* gamelevel;
	class Cat* cat;
	class Menu* menu;
	class Button* resetButton;
	class Button* menuButton;

	vector<Box*> boxes;
	bool isMenuVisible = true;
	bool isRunning = true;
	bool allGoalsComplete = false;

};

