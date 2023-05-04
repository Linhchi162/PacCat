#pragma once

#include"Settings.h"

class Box
{
public:
	Box(int x, int y);
	~Box();
	SDL_Rect* GetRect();
	bool GetInGoal();
	void Update(int x, int y, bool complete);
	Vec GetPos();
	

private:
	Vec pos;
	SDL_Rect rect;
	bool inGoal;
};
