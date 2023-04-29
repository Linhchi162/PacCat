#pragma once
#include "Game.h"
#include "KeyboardController.h"

class PacmanController
{
private:
	KeyboardController* keyboardController;

	SDL_Texture* lookingUp;
	SDL_Texture* lookingDown;
	SDL_Texture* lookingLeft;
	SDL_Texture* lookingRight;


	SDL_RendererFlip pacFlip;
	point PacPrePos;
	point PacPos = { 14 * 16,8 * 16 };

	int PacSpeed = 16;

	int direction[2];
	
	void InteractWithTile();

public:
	PacmanController() = default;
	PacmanController(const int& speed);

	bool CanMove();
	void Update();
	void GetUserInput();
	void PacDie();
	void Move();

	float GetPosX() const { return transform->xPos; }
	float GetPosY() const { return transform->yPos; }
};
