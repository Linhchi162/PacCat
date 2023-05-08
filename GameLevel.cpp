#include "GameLevel.h"

void GameLevel::LoadLevel() {
	
	string path = "Levels/level" + to_string(currentLevel) + ".txt";

	int rowCount = 0;
	int colCount = 0;


	levelFile.open(path);
	if (levelFile.is_open()) {
		char inChar;
		while (levelFile.get(inChar)) {
			if (inChar == '\n') {
				colCount = 0;
				rowCount++;
			}
			else {
				levelMap[colCount][rowCount] = inChar;
				colCount++;
			}
		}
	}

	levelFile.close();
}

void GameLevel::UpdateLevel() {
	if (currentLevel < totalLevels)
	{
		currentLevel++;
	}
}

void GameLevel::PreviousLevel()
{
	if (currentLevel > 1)
	{
		currentLevel--;
	}
}

void GameLevel::ResetLevel() {
	currentLevel = 1;
}

void GameLevel::ResetLevelTo(int x) {
	currentLevel = x;
	LoadLevel();
}

int GameLevel::GetCurrentLevel()
{
	return currentLevel;
}

int GameLevel::GetTotalLevel()
{
	return totalLevels;
}
