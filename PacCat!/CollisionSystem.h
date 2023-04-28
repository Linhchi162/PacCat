#pragma once

#include "ECS.h"
#include "Game.h"

class CollisionSystem : public System
{
private:
	int offsetX = 6;
	int offsetY = 6;

	void UpdateColliders()
	{
		for (auto const& entity : entities)
		{
			if (!engine.HasComponent<Collider>(entity))
			{
				continue;
			}

			auto& collider = engine.GetComponent<Collider>(entity);

			auto& transform = engine.GetComponent<Transform>(entity);

			
			collider.colliderRect.x = transform.xPos + offsetX;
			collider.colliderRect.y = transform.yPos + offsetY;
		}
	}

	bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
	{
		return
			rectA.x + rectA.w >= rectB.x &&
			rectB.x + rectB.w >= rectA.x &&
			rectA.y + rectA.h >= rectB.y &&
			rectB.y + rectB.h >= rectA.y;
	}

public:
	void CheckForCollisions()
	{
		UpdateColliders();

		for (auto const& entityA : entities)
		{
			if (!engine.HasComponent<Collider>(entityA))
			{
				continue;
			}

			auto colliderA = &engine.GetComponent<Collider>(entityA);

			if (colliderA->isActive == false)
			{
				continue;
			}

			for (auto const& entityB : entities)
			{
				if (entityA == entityB)
				{
					continue;
				}

				if (!engine.HasComponent<Collider>(entityB))
				{
					continue;
				}

				auto colliderB = &engine.GetComponent<Collider>(entityB);

				if (colliderB->isActive == false)
				{
					continue;
				}

				if (AABB(colliderA->colliderRect, colliderB->colliderRect))
				{
					colliderA->collidedWith = entityB;
					colliderB->collidedWith = entityA;
				}
			}
		}
	}
};

