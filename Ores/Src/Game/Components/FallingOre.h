#pragma once

#include <SDL.h>

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Transform.h"
#include "../OreData.h"
#include "../../Engine/Math/Vector2.h"

class FallingOre : public Component
{
public:
	FallingOre(Vector2 startingVelocity, float rotationSpeed, bool rotateLeft, unsigned int lifetime)
		: _velocity(startingVelocity)
		, _rotationSpeed(rotationSpeed)
		, _rotateLeft(rotateLeft)
		, _lifetime(lifetime)
	{
		_spawnTime = SDL_GetTicks();
	}

	void init() override
	{
		_transform = &entity->getComponent<Transform>();
	}

	/// <summary>
	/// Returns the current velocity
	/// </summary>
	/// <returns>A Vector2 with the current velocity</returns>
	inline Vector2& getVelocity() { return _velocity; }

	/// <summary>
	/// Sets the current velocity to a new value.
	/// </summary>
	/// <param name="newVelocity">The new velocity value</param>
	void setVelocity(Vector2 newVelocity) { _velocity = newVelocity; }

	/// <summary>
	/// Returns the rotation speed.
	/// </summary>
	/// <returns>Rotation speed</returns>
	inline float getRotationSpeed() { return _rotationSpeed; }

	/// <summary>
	/// Checks whether this falling ore will rotate left.
	/// </summary>
	/// <returns>True if it rotates left, false if it rotates right</returns>
	inline bool rotatesLeft() { return _rotateLeft; }

	/// <summary>
	/// Returns the lifetime of this falling ore.
	/// </summary>
	/// <returns>The lifetime in milliseconds</returns>
	inline unsigned int getLifetime() { return _lifetime; }

	/// <summary>
	/// Returns the time when this ore was spawned.
	/// </summary>
	/// <returns>The spawn time in milliseconds</returns>
	inline unsigned int getSpawnTime() { return _spawnTime; }

	/// <summary>
	/// Returns the Transform component attached to the same Entity as this FallingOre component.
	/// </summary>
	/// <returns>A reference to the Transform component</returns>
	inline Transform& getTransform() { return *_transform; }

private:
	unsigned int _lifetime;
	unsigned int _spawnTime;
	float _rotationSpeed;
	bool _rotateLeft;
	Vector2 _velocity;

	Transform* _transform = nullptr;
};