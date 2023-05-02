#pragma once

#include <vector>
#include"Box.h"
#include"Settings.h"
#include"GameLevel.h"
#include"Cat.h"


class Game
{
public:


	Game();
	~Game();


	SDL_Texture* LoadTexture(string path);
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
	bool CanPushBox(Box* box, int x, int y);


	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* wallTexture = nullptr;
	SDL_Texture* groundTexture = nullptr;
	SDL_Texture* boxTexture = nullptr;
	SDL_Texture* goalTexture = nullptr;

	class GameLevel* gamelevel;
	class Cat* cat;

	vector<Box*> boxes;


	bool isRunning = true;

};

