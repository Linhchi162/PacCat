#pragma once

#include"Game.h"
#include"ECS.h"
#include"Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

	}
	void update() override
	{
		transform->Velocity.x = 0;
		transform->Velocity.y = 0;
		if (keystates[SDL_SCANCODE_UP]) {
			transform->Velocity.y = -1;
		}
		if (keystates[SDL_SCANCODE_LEFT]) {
			transform->Velocity.x = -1;
		}
		if (keystates[SDL_SCANCODE_DOWN]) {
			transform->Velocity.y = 1;
		}
		if (keystates[SDL_SCANCODE_RIGHT]) {
			transform->Velocity.x = 1;
		}
		
	}
};