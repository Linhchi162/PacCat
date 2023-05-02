#pragma once
#ifndef _TEXTUREMANAGER_HEADER_INCLUDED_
#define _TEXTUREMANAGER_HEADER_INCLUDED_
#include <SDL.h>
#include"Game.h"
	 SDL_Texture* LoadTexture(const char* fileName);
	 void Draw(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest);
#endif
