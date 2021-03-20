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

	inline Vector2& getVelocity() { return _velocity; }
	void setVelocity(Vector2 newVelocity) { _velocity = newVelocity; }

	inline float getRotationSpeed() { return _rotationSpeed; }
	inline bool rotatesLeft() { return _rotateLeft; }

	inline unsigned int getLifetime() { return _lifetime; }
	inline unsigned int getSpawnTime() { return _spawnTime; }
	inline Transform& getTransform() { return *_transform; }

private:
	unsigned int _lifetime;
	unsigned int _spawnTime;
	float _rotationSpeed;
	bool _rotateLeft;
	Vector2 _velocity;

	Transform* _transform = nullptr;
};