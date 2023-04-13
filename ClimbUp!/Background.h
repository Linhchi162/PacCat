#pragma once
#include"Game.h"

class Background {
public:
	Background();
	~Background();
	void DrawBackground();

private:
	SDL_Rect src, dest;
	SDL_Texture* background;


};
