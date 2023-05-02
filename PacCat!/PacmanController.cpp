#include "PacmanController.h"
#include "Math.h"


const static float treshHold = 0.1; 
int yTileInd = 0;
int xTileInd = 0;


PacmanController::PacmanController(const int& speed)
{
	transform = new Transform();
	sr = new TextureRenderer();
	keyboardController = new KeyboardController();


	keyboardController->Up = false;
	keyboardController->Left = false;
	keyboardController->Down = false;
	keyboardController->Right = false;

	transform->xPos = PACMAN_START_XPOS;
	transform->yPos = PACMAN_START_YPOS;
	transform->width = TILE_SIZE;
	transform->height = TILE_SIZE;
	sr->defaultTexture = LoadTexture("assets/Pacman/lookingRight.png");
	  
	this->PacSpeed = speed;
	this->direction[0] = 0;
	this->direction[1] = 0;

	lookingUp = LoadTexture("assets/Pacman/lookingUp.png");
	lookingDown = LoadTexture("assets/Pacman/lookingDown.png");
	lookingLeft = LoadTexture("assets/Pacman/lookingLeft.png");
	lookingRight = LoadTexture("assets/Pacman/lookingRight.png");
}
PacmanController::~PacmanController()
{
	delete transform;
	delete sr;
	delete keyboardController;
	transform = nullptr;
	sr = nullptr;
	keyboardController = nullptr;
}
void PacmanController::InteractWithTile()
{
	CoordinatesToTiles(xTileInd, yTileInd, transform->xPos, transform->yPos);

	if (direction[0] == 0 && direction[1] == 1 || direction[0] == 0 && direction[1] == -1) // Down/Up
	{
		CoordinatesToTiles(xTileInd, yTileInd, transform->xPos, transform->yPos + HALF_TILE_SIZE);
	}
	else // Left/Right
	{
		CoordinatesToTiles(xTileInd, yTileInd, transform->xPos + HALF_TILE_SIZE, transform->yPos);
	}

	int* tileValue = &Game::map->tiles[yTileInd % tilesCountY][xTileInd % tilesCountX];

	if (*tileValue == 2)
	{
		*tileValue = 0;

		//Game::IncrementScore();
	}
	else if (*tileValue == 3)
	{
		*tileValue = 0;
		//Game::FrightenGhosts();
	}
}

void PacmanController::GetUserInput()
{
	CoordinatesToTiles(xTileInd, yTileInd, transform->xPos, transform->yPos);

	if (keyboardController->Up) {
		float dist = distFromEdge(transform->xPos,TILE_SIZE);
		if (dist <= treshHold && dist >= -treshHold && Game::map->tiles[yTileInd - 1][xTileInd] != 1)
		{
			transform->xPos = xTileInd * TILE_SIZE;
			sr->defaultTexture = lookingUp;
			direction[0] = 0;
			direction[1] = -1;
		}
	}

	else if (keyboardController->Left) {
		float dist = distFromEdge(transform->yPos, TILE_SIZE);
		if (dist <= treshHold && dist >= -treshHold && Game::map->tiles[yTileInd][xTileInd - 1] != 1)
		{
			transform->yPos = yTileInd * TILE_SIZE;
			sr->defaultTexture = lookingLeft;
			direction[0] = -1;
			direction[1] = 0;
		}
	}

	else if (keyboardController->Down) {
		float dist = distFromEdge(transform->xPos, TILE_SIZE);
		if (dist <= treshHold && dist >= -treshHold && Game::map->tiles[yTileInd + 1][xTileInd] != 1)
		{
			transform->xPos = xTileInd * TILE_SIZE;
			sr->defaultTexture = lookingDown;
			direction[0] = 0;
			direction[1] = 1;
		}
	}

	else if (keyboardController->Right) {
		float dist = distFromEdge(transform->yPos, TILE_SIZE);
		if (dist <= treshHold && dist >= -treshHold && Game::map->tiles[yTileInd][xTileInd + 1] != 1)
		{
			transform->yPos = yTileInd * TILE_SIZE;
			sr->defaultTexture = lookingRight;
			direction[0] = 1;
			direction[1] = 0;
		}
	}
}

bool PacmanController::CanMove()
{
	if ((direction[0] == 1 && direction[1] == 0) || (direction[0] == 0 && direction[1] == 1)) // Down/right 
	{
		CoordinatesToTiles(xTileInd, yTileInd, transform->xPos + direction[0] * TILE_SIZE, transform->yPos + direction[1] * TILE_SIZE);
	}
	else // Up/left 
	{
		CoordinatesToTiles(xTileInd, yTileInd, transform->xPos + direction[0], transform->yPos + direction[1]);
	}

	if (Game::map->tiles[yTileInd % tilesCountY][xTileInd % tilesCountX] == 1) {
		return false;
	}

	return true;
}

void PacmanController::Move()
{
	transform->xPos += direction[0] * PacSpeed;
	transform->yPos += direction[1] * PacSpeed;

	InteractWithTile();
}

void PacmanController::Update()
{
	/*if (collider->collidedWith) // Except Pacman, there are only ghosts with colliders. Heavy collision systems are not needed.
	{
		Game::PacmanCollidingWith(collider->collidedWith);
		collider->collidedWith = NULL;
	}*/


	if (this == nullptr)
	{
		std::cout << "this is not initialized" << std::endl;
	}
	else
	{
		keyboardController->Update();
	}
	GetUserInput();

	if (CanMove())
	{
		Move();
	}
}
