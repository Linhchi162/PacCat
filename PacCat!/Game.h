#pragma once

#include"GameLevel.h"
#include"Cat.h"
#include"Menu.h"
#include"Box.h"
#include"Timer.h"




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

	void HandleSound();

	void LoadResources();
	void TurnOffMusic();
	void TurnOnMusic();
	void HandleEvents();
	void Update();
	void Render();


	void RenderLevelCompletScreen();
	void RenderAllLevelCompletScreen();
	void RenderYouLoseScreen();
	void TimerRender();
	bool HitGoal(int x, int y);
	bool AllGoalsComplete();
	void DestroyBoxes();

	void InitLevel();

	void GoToLevel();
	void GoToNextLevel();
	void GoToPreviousLevel();
	void ResetGame();

	bool CanPushBox(Box* box, int x, int y);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool isMenuVisible = true;
	bool isRunning = true;
	bool allGoalsComplete = false;
	bool InGame = false; // for Resume Button;

	//-----------------Button--------------------//
	SDL_Texture* resetButtonTexture = nullptr;
	SDL_Texture* menuButtonTexture = nullptr;
	SDL_Texture* DisappearButtonTexture = nullptr;

	SDL_Rect resetButtonRect = { 5, 10, 64, 64 };
	SDL_Rect menuButtonRect = { 5, 90, 64, 64 };
	SDL_Rect DisappearButtonRect = { 5,170, 64, 64 };
	


	class Button* resetButton;
	class Button* menuButton;
	class Button* DisapearButton;



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
	const char* NEXT_LEVEL_MEOW_PATH = "./Sound/nextLevelmeow.wav";
	const char* NEXT_LEVEL_PATH = "./Sound/nextLevel.wav";
	const char* WIN_SOUND_PATH = "./Sound/Win.wav";




	//--------------------Chunk,Music------------------//
	Mix_Chunk* nextLevelMeowSound = nullptr;
	Mix_Music* nextLevelSound = nullptr;
	Mix_Music* WinSound = nullptr;




	//class LevelSelection* lvs;

	TTF_Font* font = nullptr;


	Timer* timer;
	Uint32 timeLimit;
};