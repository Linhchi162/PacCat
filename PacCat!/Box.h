#pragma once

#include"Settings.h"

class Box
{
public:
	Box(int x, int y);
	~Box();
	void Update(int x, int y, bool complete);
	Vec GetPos();
	SDL_Rect* GetRect();
	bool GetInGoal();

private:
	Vec pos;
	SDL_Rect rect;
	bool inGoal;
};
