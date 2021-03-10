#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template<typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t MAX_COMPONENTS = 64;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

class Component
{
public:
	virtual ~Component() {}

	virtual void init() {}
	virtual void update() {}
	virtual void render() {}

	Entity* entity = nullptr;
};

class Entity
{
public:

	void update()
	{
		for (auto& c : _components) c->update();
	}

	void render() 
	{
		for (auto& c : _components) c->render();
	}

	inline bool isActive() const { return _isActive; }
	inline void destroy() { _isActive = false; }

	template<typename T>
	bool hasComponent() const
	{
		return _componentBitset[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... args)
	{
		T* newComp = new T(std::forward<TArgs>(args)...);
		newComp->entity = this;
		std::unique_ptr<Component> compPtr{ newComp };
		_components.emplace_back(std::move(compPtr));

		_componentArray[getComponentTypeID<T>()] = newComp;
		_componentBitset[getComponentTypeID<T>()] = true;

		newComp->init();
		return *newComp;
	}

	template<typename T>
	T& getComponent() const
	{
		Component* ptr = _componentArray[getComponentTypeID<T>()];
		return *static_cast<T*>(ptr);
	}

private:
	bool _isActive = true;
	std::vector<std::unique_ptr<Component>> _components;

	ComponentArray _componentArray;
	ComponentBitset _componentBitset;
};

class EntityManager
{
public:
	void update()
	{
		for (auto& e : _entities) e->update();
	}

	void render()
	{
		for (auto& e : _entities) e->render();
	}

	/**
	* Removes all inactive entities
	*/
	void refresh()
	{
		_entities.erase(std::remove_if(_entities.begin(), _entities.end(),
			[](const std::unique_ptr<Entity>& entity)
			{
				return !entity->isActive();
			}
		), _entities.end());
	}

	Entity& createEntity()
	{
		Entity* newEntity = new Entity();
		std::unique_ptr<Entity> ptr(newEntity);
		_entities.emplace_back(std::move(ptr));

		return *newEntity;
	}

private:
	std::vector<std::unique_ptr<Entity>> _entities;
};