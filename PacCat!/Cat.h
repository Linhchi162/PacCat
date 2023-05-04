#pragma once
#include "Game.h"
#include <SDL_mixer.h>



class Cat
{
public:
	Cat(class Game* g,SDL_Renderer* renderer);
	void Move(int x, int y);
	void Reset(int x, int y);
	void Draw(SDL_Renderer* renderer);
	void InitSound();
	void PlaySound();

private:
	void SetDirection(int x, int y);
	int direction;
	Vec2 pos;
	SDL_Texture* texture;
	SDL_Rect posRect, spriteRect;
	class Game* game;
	const char* CAT_SOUND_PATH = "./assets/catStep.wav";
	Mix_Chunk* catSound;
};
