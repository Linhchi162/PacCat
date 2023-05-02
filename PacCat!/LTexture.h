#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<iostream>


SDL_Texture* LoadTexture(std::string path,SDL_Renderer* renderer);

