#pragma once
# include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:


	Vector2D position;
	Vector2D Velocity;


	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;



	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(int sc)
	{
		position.x = 0.0f;
		position.y = 0.0f;
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	void init() override
	{
		Velocity.x = 0;
		Velocity.y = 0;
	}
	void update()override
	{
		position.x += Velocity.x * speed;
		position.y += Velocity.y * speed;

	}
};
