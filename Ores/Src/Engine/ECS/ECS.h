#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>

class Entity;
class EntityManager;

using EntityID = std::size_t;
using ArchetypeID = std::size_t;
using ComponentID = std::string;

class Component
{
public:
	virtual ~Component() {}

	virtual void init() {}
	//virtual void update() {}

	Entity* entity = nullptr;
};

class System
{
public:
	System(EntityManager* entityManager)
		: _entityManager(entityManager)
	{ }

	virtual ~System() {}

	/// <summary>
	/// Called upon creation of the system
	/// </summary>
	virtual void init() {}

	/// <summary>
	/// Called every frame in each system
	/// </summary>
	virtual void update() = 0;

protected:
	EntityManager* _entityManager;
};

struct Archetype
{
	Archetype()
	{
		id = s_lastArchetypeID++;
		entities.reserve(10);
	}

	Archetype(std::unordered_set<ComponentID> newComponents);

	template<typename T>
	inline bool hasComponent()
	{
		return components.count(getComponentID<T>()) > 0;
	}

	template<typename T>
	static ComponentID getComponentID()
	{
		return typeid(T).name();
	}

	ArchetypeID id;
	std::unordered_set<ComponentID> components;
	std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;

private:
	static ArchetypeID s_lastArchetypeID;
};

class Entity
{
public:
	EntityID id;
	ArchetypeID archetypeID = 0u;
	EntityManager* manager = nullptr;

	Entity(ArchetypeID archetypeID, EntityManager* manager);
	~Entity()
	{
		_componentMap.clear();
	}

	//void update();

	inline bool isActive() const { return _isActive; }
	inline void destroy() { _isActive = false; }

	template<typename T>
	inline bool hasComponent() const
	{
		return _componentMap.count(Archetype::getComponentID<T>());
	}

	template<typename T>
	inline T& getComponent() const
	{
		Component* ptr = _componentMap.at(Archetype::getComponentID<T>()).get();
		return *static_cast<T*>(ptr);
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... args);


private:
	static EntityID s_lastEntityID;
	bool _isActive = true;
	std::unordered_map<ComponentID, std::unique_ptr<Component>> _componentMap;
};

class EntityManager
{
public:
	EntityManager();
	~EntityManager()
	{
		_entityArchetypes.clear();
	}

	//void update();
	void refresh();

	Entity& createEntity();

	/// <summary>
	/// Returns all entities that contain all of the supplied components.
	/// </summary>
	/// <typeparam name="...Ts">Component type</typeparam>
	/// <returns>Vector with all entities with all of the supplied components</returns>
	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentAll();

	/// <summary>
	/// Returns all entities that contain any of the supplied components.
	/// </summary>
	/// <typeparam name="...Ts">Component type</typeparam>
	/// <returns>Vector with all entities with any of the supplied components</returns>
	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentAny();

	/// <summary>
	/// Returns all entities that contain none of the supplied components.
	/// </summary>
	/// <typeparam name="...Ts">Component type</typeparam>
	/// <returns>Vector with all entities with none of the supplied components</returns>
	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentNone();

	/// <summary>
	/// Returns all entities that contain exactly all of the supplied components.
	/// </summary>
	/// <typeparam name="...Ts">Component type</typeparam>
	/// <returns>Vector with all entities with exactly all of the supplied components</returns>
	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentExact();

private:
	friend class Entity;
	std::vector<std::unique_ptr<Archetype>> _entityArchetypes;

	unsigned int _lastCleanupTime = 0;
	const unsigned int CLEANUP_INTERVAL = 60000;

	template<typename T>
	void updateArchetypes(Entity* entity);
};


/**
* /////////////////////////////////////////////////////////////////
* ************************** Entity *******************************
* /////////////////////////////////////////////////////////////////
*/

template<typename T, typename... TArgs>
T& Entity::addComponent(TArgs&&... args)
{
	std::unique_ptr<Component> compUniqPtr = std::make_unique<T>(std::forward<TArgs>(args)...);
	compUniqPtr->entity = this;
	compUniqPtr->init();

	T* newComponent = dynamic_cast<T*>(compUniqPtr.get());

	ComponentID componentID = Archetype::getComponentID<T>();
	_componentMap.emplace(componentID, std::move(compUniqPtr));

	manager->updateArchetypes<T>(this);

	return *newComponent;
}

/**
* /////////////////////////////////////////////////////////////////
* *********************** EntityManager ***************************
* /////////////////////////////////////////////////////////////////
*/


template<typename T>
void EntityManager::updateArchetypes(Entity* entity)
{
	ArchetypeID archetypeID = entity->archetypeID;
	std::unordered_set<ComponentID> entityComponents;
	std::unique_ptr<Entity> entityUPtr;

	for (auto& archetype : _entityArchetypes)
	{
		if (archetype->id == archetypeID)
		{
			// Grab the components this entity already has
			entityComponents = archetype->components;
			entityUPtr = std::move(archetype->entities.at(entity->id));
			// Remove entity from old archetype
			archetype->entities.erase(entityUPtr->id);
			break;
		}
	}

	// Add new component type
	entityComponents.emplace(Archetype::getComponentID<T>());

	// Check if new archetype already exists and add entity to it if true
	for (auto& archetype : _entityArchetypes)
	{
		bool containsAll = true;

		for (auto& component : entityComponents)
		{
			containsAll = containsAll && archetype->components.count(component);
		}

		if (containsAll && archetype->components.size() == entityComponents.size())
		{
			entityUPtr->archetypeID = archetype->id;
			archetype->entities.emplace(entityUPtr->id, std::move(entityUPtr));
			return;
		}
	}

	// Archetype doesn't exist yet, create a new one
	Archetype* newArchetype = new Archetype(entityComponents);
	//std::cout << "Created new archetype!" << std::endl;

	std::unique_ptr<Archetype> archetypeUPtr(newArchetype);

	entityUPtr->archetypeID = archetypeUPtr->id;
	archetypeUPtr->entities.emplace(entityUPtr->id, std::move(entityUPtr));

	_entityArchetypes.emplace_back(std::move(archetypeUPtr));
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentAll()
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { Archetype::getComponentID<Ts>()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _entityArchetypes)
	{
		bool containsAll = true;

		// Check if this archetype has ALL of the supplied components
		for (auto& component : components)
		{
			containsAll = containsAll && archetype->components.count(component);
		}

		if (containsAll)
		{
			for (auto& entity : archetype->entities)
			{
				entities.emplace_back(entity.second.get());
			}
		}
	}

	return entities;
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentAny()
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { Archetype::getComponentID<Ts>()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _entityArchetypes)
	{
		bool containsAny = true;

		// Check if this archetype has ANY of the supplied components
		for (auto& component : components)
		{
			containsAny = containsAny || archetype->components.count(component);
		}

		if (containsAny)
		{
			for (auto& entity : archetype->entities)
			{
				entities.emplace_back(entity.second.get());
			}
		}
	}

	return entities;
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentNone()
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { Archetype::getComponentID<Ts>()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _entityArchetypes)
	{
		bool containsNone = true;

		// Check if this archetype has ANY of the supplied components
		for (auto& component : components)
		{
			containsNone = containsNone && !archetype->components.count(component);
		}

		if (containsNone)
		{
			for (auto& entity : archetype->entities)
			{
				entities.emplace_back(entity.second.get());
			}
		}
	}

	return entities;
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentExact()
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { Archetype::getComponentID<Ts>()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _entityArchetypes)
	{
		bool containsAll = true;

		// First check if this archetype contains all of the supplied components
		for (auto& component : components)
		{
			containsAll = containsAll && archetype->components.count(component);
		}

		// Now check if it also contains the EXACT number of components
		if (containsAll && archetype->components.size() == components.size())
		{
			std::transform(archetype->entities.begin(), archetype->entities.end(), entities.end(),
				[](const std::pair<EntityID, std::unique_ptr<Entity>>& pair)
				{
					return pair.second.get();
				});

			return entities;
		}
	}

	return entities;
}