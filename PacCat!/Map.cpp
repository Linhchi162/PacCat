#include "Map.h"



Map::Map()
{
	tWall = NULL;
	tFood = NULL;
	mWidth = 0;
	mHeight = 0;
	foodNumber = 0;

	lastAllowcateFoodTime = 0;
	specialFoodType = 0;
	hasSpecialFood = false;
	allowcateSpecialFoodCount = 0;
	specialFoodTime = 15000;
	lastSpecialFoodTime = 0;

	specialFoodX = 10;
	specialFoodY = 15;

	specialFoodPoint.clear();
	specialFoodPoint.push_back(100);
	specialFoodPoint.push_back(300);
	specialFoodPoint.push_back(500);
	specialFoodPoint.push_back(700);
	specialFoodPoint.push_back(1000);
	specialFoodPoint.push_back(2000);
	specialFoodPoint.push_back(3000);
	specialFoodPoint.push_back(5000);

	map.clear();
	cornerMap.clear();
}
Map::~Map()
{
	if (tWall != NULL)
	{
		tWall->Free();
		tWall = NULL;
	}
	if (tFood != NULL)
	{
		tFood->Free();
		tFood = NULL;
	}
	mWidth = 0;
	mHeight = 0;
	map.clear();
}
bool Map::LoadTexture(SDL_Renderer* mainRenderer)
{
	tWall = NULL;
	tFood = NULL;

	tWall = new TextureManager();
	if (!tWall->LoadFromFile(mainRenderer, "res/image/wall.png"))
		return false;
	tWall->SetTileSize(WALL_WIDTH, WALL_HEIGHT);

	tFood = new TextureManager();
	if (!tFood->LoadFromFile(mainRenderer, "res/image/food.png"))
		return false;
	tFood->SetTileSize(FOOD_WIDTH, FOOD_HEIGHT);

	return true;
}
bool Map::SetWall(int x, int y, bool value)
{
	if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		return false;
	else map[x * mHeight + y] = value;
	return true;
}

bool Map::GetWall(int x, int y)
{
	if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		return false;
	else return map[x * mHeight + y];
}

bool Map::SetFood(int x, int y, int value)
{
	if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
	{
		return false;
	}
	else
	{
		// if foodstate is not equal to value settle to
		if ((foodMap[x * mHeight + y]) != value && (value == 0 || value == 1))
		{
			if (foodMap[x * mHeight + y] == 0)
			{
				foodNumber++;
			}
			else
			{
				foodNumber--;
			}
		}
		foodMap[x * mHeight + y] = value;
		return true;
	}
}
int Map::GetFood(int x, int y)
{
	if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		return 0;
	else return foodMap[x * mHeight + y];
}
int Map::EatSpecialFoodAt(int x, int y)
{
	if (x == specialFoodX && y == specialFoodY && hasSpecialFood)
	{
		hasSpecialFood = false;
		return specialFoodPoint[specialFoodType];
	}
	else
	{
		return 0;
	}
}
void Map::ClearSpecialFood()
{
	hasSpecialFood = false;
}
bool Map::SetCorner(int x, int y, int value)
{
	if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		return false;
	else cornerMap[x * mHeight + y] = value;
	return true;
}
int Map::GetCorner(int x, int y)
{
	if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		return -2;
	else return cornerMap[x * mHeight + y];
}


bool Map::LoadMap(std::string path, int mapWidth, int mapHeight)
{
	std::ifstream mapFile(path.c_str());
	if (mapFile.fail())
	{
		printf("Unable to load map file!\n");
		return false;
	}
	int totalTile = mapWidth * mapHeight;

	map.resize(totalTile);

	mWidth = mapWidth;
	mHeight = mapHeight;
	int tileType = 0;
	for (int j = 0; j < mHeight; j++)
	{
		for (int i = 0; i < mWidth; i++)
		{
			mapFile >> tileType;

			if (mapFile.fail())
			{
				printf("Error loading map: Unexpected end of file!\n");
				mapFile.close();
				return false;
			}

			if (tileType != 0)
			{
				// is wall
				SetWall(i, j, true);
			}
			else
			{
				// not a wall
				SetWall(i, j, false);
			}
		}
	}
	mapFile.close();
	return (AnalizeMap() && AllowcateFood());
}