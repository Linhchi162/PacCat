#pragma once
#include "Game.h"

class Cat
{
public:
	Cat(class Game* g,SDL_Renderer* renderer);
	void Move(int x, int y);
	void Reset(int x, int y);
	void Draw(SDL_Renderer* renderer);

private:
	void SetDirection(int x, int y);
	int direction;
	Vec2 pos;
	SDL_Texture* texture;
	SDL_Rect posRect, spriteRect;
	class Game* game;
};