#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include <iostream>

using namespace std;

const int TILE_SIZE = 64;
const int TILE_ROWS = 10;
const int TILE_COLS = 10;
const int SCREEN_WIDTH = TILE_SIZE * TILE_COLS;
const int SCREEN_HEIGHT = TILE_SIZE * TILE_ROWS;

const SDL_Rect resetButtonRect = { SCREEN_WIDTH / 2 - 310, SCREEN_HEIGHT / 2 - 310, 64, 64 };
const SDL_Rect menuButtonRect = { SCREEN_WIDTH / 2 - 310, SCREEN_HEIGHT / 2 - 210, 64, 64 };
const SDL_Rect  DisappearButtonRect = { SCREEN_WIDTH / 2 - 310, SCREEN_HEIGHT / 2 - 110, 64, 64 };
const SDL_Rect ScreenDst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };



struct Vec {
	int x;
	int y;
};

