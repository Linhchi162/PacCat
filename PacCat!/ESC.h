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
class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(const Entity& entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray
{
private:
	std::array<T, MAX_ENTITIES> componentArray;

	// Map from an entity ID to an array index.
	std::unordered_map<Entity, size_t> entityToIndexMap;

	// Map from an array index to an entity ID.
	std::unordered_map<size_t, Entity> indexToEntityMap;

	size_t validEntriesInArray;

public:
	void InsertData(const Entity& entity, T component)
	{
		size_t newIndex = validEntriesInArray;
		entityToIndexMap[entity] = newIndex;
		indexToEntityMap[newIndex] = entity;
		componentArray[newIndex] = component;
		++validEntriesInArray;
	}

	void RemoveData(const Entity& entity)
	{
		size_t indexOfRemovedEntity = entityToIndexMap[entity];
		size_t indexOfLastElement = validEntriesInArray - 1;
		componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

		Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
		entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(indexOfLastElement);

		--validEntriesInArray;
	}

	bool HasData(const Entity& entity)
	{
		return indexToEntityMap[entityToIndexMap[entity]] == entity;
	}

	T& GetData(const Entity& entity)
	{
		return componentArray[entityToIndexMap[entity]];
	}

	void EntityDestroyed(const Entity& entity) override
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}
};




