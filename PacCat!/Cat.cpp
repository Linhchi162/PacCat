#include "Cat.h"

Cat::Cat(Game* g,SDL_Renderer* renderer) {
	game = g;
	texture = LoadTexture("./assets/Cat.png", renderer);
	direction = 0;
	pos.x = 0;
	pos.y = 0;
	posRect = { pos.x, pos.y, TILE_SIZE, TILE_SIZE };
	spriteRect = { 0, 0, TILE_SIZE, TILE_SIZE };

	InitSound();
}

void Cat::Move(int x, int y)
{
	SetDirection(x, y);
	int newCatX = pos.x + x;
	int newCatY = pos.y + y;

	if (game->HitWall(newCatX, newCatY)) {
		return;
	}

	if (!game->BoxUpdated(x, y, newCatX, newCatY)) {
		return;
	}

	pos.x = newCatX;
	pos.y = newCatY;

	posRect.x = pos.x * TILE_SIZE;
	posRect.y = pos.y * TILE_SIZE;

	PlaySound();
}

void Cat::Draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &spriteRect, &posRect);
}

void Cat::SetDirection(int x, int y) {
	if (x > 0) {
		direction = 0;
	}
	else if (x < 0) {
		direction = 2;
	}
	else if (y > 0) {
		direction = 1;
	}
	else if (y < 0) {
		direction = 3;
	}

	spriteRect.x = direction * TILE_SIZE;
}

void Cat::Reset(int x, int y) {
	direction = 0;
	pos.x = x;
	pos.y = y;
	posRect = { pos.x * TILE_SIZE, pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
	spriteRect = { 0, 0, TILE_SIZE, TILE_SIZE };
}

void Cat::InitSound()
{
	catSound = Mix_LoadWAV(CAT_SOUND_PATH);
	if (catSound == NULL) {
		printf("Unable to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}
}
void Cat::PlaySound() {
	if (catSound != NULL) {
		Mix_PlayChannel(-1, catSound, 0);
	}
}