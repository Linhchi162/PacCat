#pragma once

#include <vector>
#include"GameLevel.h"
#include"Cat.h"
#include"Menu.h"
#include"Box.h"

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
	void Render();

	bool HitGoal(int x, int y);
	bool AllGoalsComplete();
	void DestroyBoxes();
	void InitLevel();
	void GoToNextLevel();
	void GoToPreviousLevel();
	bool CanPushBox(Box* box, int x, int y);


	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool isMenuVisible = true;
	bool isRunning = true;
	bool allGoalsComplete = false;

	//-----------------Button--------------------//
	SDL_Texture* resetButtonTexture = nullptr;
	SDL_Texture* menuButtonTexture = nullptr;
	class Button* resetButton;
	class Button* menuButton;



	//-----------------Object--------------------//
	SDL_Texture* wallTexture = nullptr;
	SDL_Texture* groundTexture = nullptr;
	SDL_Texture* boxTexture = nullptr;
	SDL_Texture* goalTexture = nullptr;
	class GameLevel* gamelevel;
	class Cat* cat;
	class Menu* menu;
	vector<Box*> boxes;


	//-----------------Screen--------------------//
	SDL_Texture* youWin = nullptr;
	SDL_Texture* levelclear = nullptr;

	

	//------------------SoundPath----------------------//
	const char* NEXT_LEVEL_MEOW_PATH = "./assets/nextLevelmeow.wav";
	const char* NEXT_LEVEL_PATH = "./assets/nextLevel.wav";
	const char* WIN_SOUND_PATH = "./assets/Win.wav";


	//--------------------Chunk,Music------------------//
    Mix_Chunk* nextLevelMeowSound = nullptr;
    Mix_Music* nextLevelSound = nullptr;
	Mix_Music* WinSound = nullptr;


};

