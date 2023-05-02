#pragma once
#ifndef _KEYBOARDCONTROLLER_HEADER_INCLUDED_
#define _KEYBOARDCONTROLLER_HEADER_INCLUDED_
#include "Game.h"

class KeyboardController
{
public:
	bool Up;
	bool Down;
	bool Left;
	bool Right;

	void Update()
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				Up = true;
				Down = Left = Right = false;
				break;
			case SDLK_DOWN:
				Down = true;
				Up = Left = Right = false;
				break;
			case SDLK_LEFT:
				Left = true;
				Right = Up= Down = false;
				break;
			case SDLK_RIGHT:
				Right = true;
				Left = Up = Down = false;
				break;
			default:
				break;
			}
		}
	}
};
#endif