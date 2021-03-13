#include "ECS.h"

/**
* /////////////////////////////////////////////////////////////////
* ************************ Archetype ******************************
* /////////////////////////////////////////////////////////////////
*/

ArchetypeID Archetype::s_lastArchetypeID = 0u;

Archetype::Archetype(const std::unordered_set<ComponentID>& newComponents)
{
	id = s_lastArchetypeID++;
	//std::unique_ptr<Entity> uPtr(entity);
	//entities.emplace(entity->id, std::move(uPtr));
	components = newComponents;
}


/**
* /////////////////////////////////////////////////////////////////
* ************************** Entity *******************************
* /////////////////////////////////////////////////////////////////
*/

EntityID Entity::s_lastEntityID = 0u;

Entity::Entity(ArchetypeID archetypeID, EntityManager* manager)
	: archetypeID(archetypeID)
	, manager(manager)
{
	id = s_lastEntityID++;
}

void Entity::update()
{
	for (auto& c : _componentMap) c.second->update();
}


/**
* /////////////////////////////////////////////////////////////////
* *********************** EntityManager ***************************
* /////////////////////////////////////////////////////////////////
*/

EntityManager::EntityManager()
{
	Archetype* emptyArchetype = new Archetype();
	std::unique_ptr<Archetype> uPtr(emptyArchetype);

	// Create an "empty" archetype that stores all entities with no components
	_archetypes.emplace_back(std::move(uPtr));
}

void EntityManager::update()
{
	for (auto& arch : _archetypes)
	{
		for (auto& e : arch->entities) e.second->update();
	}
}

void EntityManager::refresh()
{
	/*
for (auto& arch : _archetypes)
{
	arch->entities.erase(std::remove_if(arch->entities.begin(), arch->entities.end(),
		[](const std::unique_ptr<Entity>& entity)
		{
			return !entity->isActive();
		}
	), arch->entities.end());
}
*/

	for (auto& arch : _archetypes)
	{
		for (auto& entry : arch->entities)
		{
			if (!entry.second->isActive())
			{
				arch->entities.erase(entry.first);
			}
		}
	}
}

Entity& EntityManager::createEntity()
{
	Entity* newEntity = new Entity(_archetypes[0]->id, this);
	newEntity->manager = this;
	std::unique_ptr<Entity> ptr(newEntity);
	//_entities.emplace_back(std::move(ptr));

	// Store in no-components archetype
	_archetypes[0]->entities.emplace(ptr->id, std::move(ptr));

	return *newEntity;
}