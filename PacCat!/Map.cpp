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
