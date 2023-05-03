#include "GameLevel.h"

void GameLevel::LoadLevel() {
	int rowCount = 0;
	int colCount = 0;

	string path = "Levels/level" + to_string(currentLevel) + ".txt";

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
		currentLevel++;
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
