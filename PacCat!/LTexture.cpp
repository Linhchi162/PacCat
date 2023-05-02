
#include"LTexture.h"
#include "Game.h"


SDL_Texture * LoadTexture(std::string path,SDL_Renderer* renderer) {
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
