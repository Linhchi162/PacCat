#include "Map.h"
#include"TextureManager.h"
int startingTiles[19][19] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							 {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
							 {1, 2, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1},
							 {1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1},
							 {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
							 {1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
							 {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
							 {1, 2, 1, 2, 1, 1, 2, 1, 1, 0, 1, 1, 2, 1, 1, 2, 1, 2, 1},
							 {1, 2, 1, 2, 1, 1, 2, 1, 0, 0, 0, 1, 2, 1, 1, 2, 1, 2, 1},
							 {1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1},
							 {1, 2, 1, 2, 1, 1, 2, 1, 0, 0, 0, 1, 2, 1, 1, 2, 1, 2, 1},
							 {1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1},
							 {1, 2, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 2, 1},
							 {1, 2, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 1},
							 {1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1},
							 {1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 1},
							 {1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1},
							 {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
							 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

Map::Map()
{
	free = LoadTexture("assets/free.png");
	block = LoadTexture("assets/block.png");
	dot = LoadTexture("assets/dot.png");
	energizer = LoadTexture("assets/energizer.png");

	LoadMap(startingTiles);

	src.x = src.y = 0;
	src.w = dest.w = TILE_SIZE;
	src.h = dest.h = TILE_SIZE;

	dest.x = dest.y = 0;
}

Map::~Map()
{
	delete free;
	delete block;
	delete dot;
	delete energizer;
}

void Map::LoadMap(int tiles[tilesCountX][tilesCountY])
{
	for (int row = 0; row < tilesCountY; ++row)
	{
		for (int col = 0; col < tilesCountX; ++col)
		{
			this->tiles[row][col] = tiles[row][col];
		}
	}
}

void Map::DrawMap()
{
	for (int row = 0; row < tilesCountY; ++row)
	{
		for (int col = 0; col < tilesCountX; ++col)
		{
			DrawTile(tiles[row][col], row, col);
		}
	}
}

void Map::DrawTile(const int& type, const int& row, const int& col)
{
	dest.x = col * TILE_SIZE;
	dest.y = row * TILE_SIZE;

	switch (type)
	{
	case 0:
		Draw(free, src, dest);
		break;
	case 1:
		Draw(block, src, dest);
		break;
	case 2:
		Draw(dot, src, dest);
		break;
	case 3:
		Draw(energizer, src, dest);
	default:
		break;
	}
}