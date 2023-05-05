#pragma once

#include "Settings.h"
#include <fstream>
#include <string>

class GameLevel
{
public:
	void LoadLevel();
	void UpdateLevel();
	void PreviousLevel();
	void ResetLevel();


	int GetCurrentLevel();
	int GetTotalLevel();

	char levelMap[TILE_ROWS][TILE_COLS] = { '0' };

private:
	ifstream levelFile;
	int currentLevel = 1;
	int totalLevels = 10;
};