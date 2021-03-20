#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../OreData.h"

#include "../../Engine/ECS/Components/Transform.h"
#include "../../Engine/ECS/Components/Sprite.h"
#include "../../Engine/ECS/Components/Audio.h"
#include "../../Engine/Math/Vector2.h"


class Ore : public Component
{
public:
	Ore(OreData oreData, const Vector2& gridRoot, const Vector2& gridCoords, int oreWidth, int oreHeight, float moveDuration)
		: _oreData(oreData)
		, _gridRoot(gridRoot)
		, _gridCoords(gridCoords)
		, _oreDimensions(Vector2(oreWidth, oreHeight))
		, _moveDuration(moveDuration)
	{
	}

	void init()
	{
		_transform = &entity->getComponent<Transform>();
		_sprite = &entity->getComponent<Sprite>();

		setGridCoords(_gridCoords, true);
	}

	inline Transform* getTransform() { return _transform; }
	inline Sprite* getSprite() { return _sprite; }
	inline OreData getOreData() { return _oreData; }

	inline const Vector2& getGridCoords() { return _gridCoords; }
	inline const Vector2& getOreDimensions() { return _oreDimensions; }

	void setGridCoords(Vector2 newCoords, bool immediate)
	{
		_gridCoords = newCoords;

		if (immediate)
		{
			_transform->position = _gridRoot + _gridCoords * _oreDimensions;

		}

		targetPosition = _gridRoot + _gridCoords * _oreDimensions;
	}

	inline void flagSuspended()
	{
		_suspended = true;
		_moving = true;
	}

	inline void flagNotSuspended()
	{
		_suspended = false;
	}

	inline void flagVisited()
	{
		_visited = true;
	}

	inline void flagNotVisited()
	{
		_visited = false;
	}

	inline void flagNotMoving()
	{
		_moving = false;
	}

	void destroy()
	{
		entity->destroy();
	}

	inline bool isSuspended() { return _suspended; }
	inline bool isMoving() { return _moving; }
	inline bool visited() { return _visited; }


	bool hover = false;
	bool clicked = false;

	Vector2 targetPosition;
	Transform* _transform = nullptr;

private:
	OreData _oreData;

	Vector2 _gridCoords;
	Vector2 _gridRoot;
	Vector2 _oreDimensions;

	Sprite* _sprite = nullptr;
	//Audio* _destructionSFX = nullptr;

	bool _visited = false;

	bool _suspended = false; // Flag to check if this ore is suspended mid-air inside the grid, with no blocks underneath it.
	bool _moving = false; // Flag to check if the ore is moving between grid positions. While this is true, the ore cannot be interacted with.
	float _moveDuration = 0.f;
	float _timeElapsed = 0.f;
};
