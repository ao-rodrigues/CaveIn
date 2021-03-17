#include "ECS.h"

/**
* /////////////////////////////////////////////////////////////////
* ************************ Archetype ******************************
* /////////////////////////////////////////////////////////////////
*/

ArchetypeID Archetype::s_lastArchetypeID = 0u;

Archetype::Archetype(std::unordered_set<ComponentID>&& newComponents)
{
	id = s_lastArchetypeID++;
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

/*
void Entity::update()
{
	for (auto& c : _componentMap) c.second->update();
}
*/


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
	_entityArchetypes.emplace_back(std::move(uPtr));
}

/*
void EntityManager::update()
{
	for (auto& arch : _archetypes)
	{
		for (auto& e : arch->entities) e.second->update();
	}
}
*/

void EntityManager::refresh()
{
	for (auto& arch : _entityArchetypes)
	{
		for (auto it = arch->entities.begin(); it != arch->entities.end();)
		{
			if (!it->second->isActive())
			{
				it = arch->entities.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

Entity& EntityManager::createEntity()
{
	Entity* newEntity = new Entity(_entityArchetypes[0]->id, this);
	newEntity->manager = this;
	std::unique_ptr<Entity> ptr(newEntity);

	// Store in no-components archetype
	_entityArchetypes[0]->entities.emplace(ptr->id, std::move(ptr));

	return *newEntity;
}