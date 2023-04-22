#pragma once
#ifndef _ECS_HEADER_INCLUDED_
#define _ECS_HEADER_INCLUDED_

#include <iostream>
#include <array>
#include <bitset>
#include <queue>
#include <unordered_map>
#include <set>

using Entity = unsigned int;
const Entity MAX_ENTITIES = 5000;

using ComponentType = unsigned short;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;


class EntityManager
{
private:
	std::queue<Entity> availableEntities;
	std::array<Signature, MAX_ENTITIES> signatures;

	unsigned int entitiesCount;

public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			availableEntities.push(entity);
		}

		entitiesCount = 0;
	}

	Entity CreateEntity()
	{
		Entity id = availableEntities.front();
		availableEntities.pop();
		++entitiesCount;

		return id;
	}

	void DestroyEntity(const Entity& entity)
	{
		signatures[entity].reset();

		availableEntities.push(entity);
		--entitiesCount;
	}

	void SetSignature(const Entity& entity, const Signature& signature)
	{
		signatures[entity] = signature;
	}

	Signature GetSignature(const Entity& entity)
	{
		return signatures[entity];
	}
};

