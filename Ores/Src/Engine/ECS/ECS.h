#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>

class Entity;
class EntityManager;

using EntityID = std::size_t;
using ArchetypeID = std::size_t;
using ComponentID = std::size_t;

class Component
{
public:
	virtual ~Component() {}

	virtual void init() {}
	virtual void update() {}

	Entity* entity = nullptr;
};

struct Archetype
{
	Archetype()
	{
		id = s_lastArchetypeID++;
	}

	Archetype(const std::unordered_set<ComponentID>& newComponents);

	template<typename T>
	inline bool hasComponent()
	{
		std::size_t compHash = typeid(T).hash_code();
		return components.count(compHash) > 0;
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

	void update();

	inline bool isActive() const { return _isActive; }
	inline void destroy() { _isActive = false; }

	template<typename T>
	inline bool hasComponent() const
	{
		return _componentMap.count(typeid(T).hash_code());
	}

	template<typename T>
	inline T& getComponent() const
	{
		Component* ptr = _componentMap.at(typeid(T).hash_code()).get();
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

	void update();
	void refresh();

	Entity& createEntity();

	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponent();

	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentExact();

private:
	//std::vector<std::unique_ptr<Entity>> _entities;
	std::vector<std::unique_ptr<Archetype>> _archetypes;
	friend class Entity;

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
	T* newComponent = new T(std::forward<TArgs>(args)...);
	newComponent->entity = this;
	std::unique_ptr<Component> compPtr(newComponent);
	ComponentID componentID = typeid(T).hash_code();

	_componentMap.emplace(componentID, std::move(compPtr));

	newComponent->init();

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

	for (auto& archetype : _archetypes)
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
	entityComponents.emplace(typeid(T).hash_code());

	// Check if new archetype already exists and add entity to it if true
	for (auto& archetype : _archetypes)
	{
		bool containsAll = true;

		for (auto& component : entityComponents)
		{
			containsAll = containsAll && archetype->components.count(component);
		}

		if (containsAll)
		{
			entityUPtr->archetypeID = archetype->id;
			archetype->entities.emplace(entityUPtr->id, std::move(entityUPtr));
			return;
		}
	}

	// Archetype doesn't exist yet, create a new one
	Archetype* newArchetype = new Archetype(entityComponents);

	std::unique_ptr<Archetype> archetypeUPtr(newArchetype);

	entityUPtr->archetypeID = archetypeUPtr->id;
	archetypeUPtr->entities.emplace(entityUPtr->id, std::move(entityUPtr));

	_archetypes.emplace_back(std::move(archetypeUPtr));
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponent()
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { typeid(Ts).hash_code()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _archetypes)
	{
		// Check if this archetype has AT LEAST one of the supplied components
		for (auto& component : components)
		{
			// If it does, we add its entities
			if (archetype->components.count(component))
			{
				std::transform(archetype->entities.begin(), archetype->entities.end(), std::back_inserter(entities),
					[](const auto& pair) 
					{
						return pair.second.get();
					});
				break;
			}
		}
	}

	return entities;
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentExact()
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { typeid(Ts).hash_code()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _archetypes)
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