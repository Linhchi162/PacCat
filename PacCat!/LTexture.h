#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<iostream>

SDL_Texture* LoadTexture(std::string path, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL) {
		std::cout << "Failed to load surface: " << IMG_GetError() << std::endl;
	}

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (newTexture == NULL) {
		std::cout << "Failed to conver to texture: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(tempSurface);

	return newTexture;
}
void RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.h = h;
	dst.w = w;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}