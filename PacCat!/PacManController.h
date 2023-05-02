#pragma once
#ifndef _PACMANCONTROLLER_HEADER_INCLUDED_
#define _PACMANCONTROLLER_HEADER_INCLUDED_
#include "KeyboardController.h"
#include "Collision.h"
#include"TextureManager.h"

class PacmanController
{
private:
	Transform* transform;
	TextureRenderer* sr;
	KeyboardController* keyboardController;

	SDL_Texture* lookingUp;
	SDL_Texture* lookingDown;
	SDL_Texture* lookingLeft;
	SDL_Texture* lookingRight;


	SDL_RendererFlip pacFlip;
	/*point PacPrePos;
	point PacPos = { 14 * 16,8 * 16 };*/

	int PacSpeed = 16;

	int direction[2];
	
	void InteractWithTile();

public:
	PacmanController() = default;
	~PacmanController();
	PacmanController(const int& speed);

	bool CanMove();
	void Update();
	void GetUserInput();
	void PacDie();
	void Move();

};
#endif