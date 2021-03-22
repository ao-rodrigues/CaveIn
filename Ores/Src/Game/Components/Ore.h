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
		, _oreDimensions(Vector2(static_cast<float>(oreWidth), static_cast<float>(oreHeight)))
		, _moveDuration(moveDuration)
	{
	}

	void init()
	{
		_transform = &entity->getComponent<Transform>();
		_sprite = &entity->getComponent<Sprite>();

		setGridCoords(_gridCoords, true);
	}

	/// <summary>
	/// Returns the Transform component attached to the same Entity as this Ore component.
	/// </summary>
	/// <returns>A reference to the Transform component</returns>
	inline Transform& getTransform() { return *_transform; }

	/// <summary>
	/// Returns the Sprite component attached to the same Entity as this Ore component.
	/// </summary>
	/// <returns>A reference to the Sprite component</returns>
	inline Sprite& getSprite() { return *_sprite; }

	/// <summary>
	/// Returns the ore data packed in a OreData struct.
	/// </summary>
	/// <returns>The ore data</returns>
	inline OreData getOreData() { return _oreData; }

	/// <summary>
	/// Returns the coordinates of this Ore inside the grid.
	/// </summary>
	/// <returns>A Vector2 with the coordinates of this ore inside the grid</returns>
	inline Vector2 getGridCoords() { return _gridCoords; }

	/// <summary>
	/// Returns the dimensions of this Ore.
	/// </summary>
	/// <returns>A Vector2 with the Ore's dimensions in the format (width,height)</returns>
	inline Vector2 getOreDimensions() { return _oreDimensions; }

	/// <summary>
	/// Returns the target position of this Ore.
	/// Useful for when an Ore is moving to a new location.
	/// </summary>
	/// <returns>A Vector2 with the world coordinates of the target position</returns>
	inline Vector2 getTargetPosition() { return _targetPosition; }

	/// <summary>
	/// Sets the new coordinates of this Ore inside the grid
	/// </summary>
	/// <param name="newCoords">The new coordinates</param>
	/// <param name="immediate">If true, the ore will instantly move to the new coordinates, if false, it will animate to the new position</param>
	void setGridCoords(Vector2 newCoords, bool immediate)
	{
		_gridCoords = newCoords;

		if (immediate)
		{
			_transform->position = _gridRoot + _gridCoords * _oreDimensions;

		}

		_targetPosition = _gridRoot + _gridCoords * _oreDimensions;
	}

	/// <summary>
	/// Flags this Ore as being suspended mid-air
	/// </summary>
	inline void flagSuspended()
	{
		_suspended = true;
	}

	/// <summary>
	/// Flags this Ore as not suspended mid-air
	/// </summary>
	inline void flagNotSuspended()
	{
		_suspended = false;
	}

	/// <summary>
	/// Flags this Ore as visited.
	/// </summary>
	inline void flagVisited()
	{
		_visited = true;
	}

	/// <summary>
	///  Flags this Ore as not visited.
	/// </summary>
	inline void flagNotVisited()
	{
		_visited = false;
	}

	/// <summary>
	/// Destroys this Ore.
	/// </summary>
	void destroy()
	{
		entity->destroy();
	}

	/// <summary>
	/// Checks whether this Ore is suspended or not.
	/// </summary>
	/// <returns>True if it is, false if not.</returns>
	inline bool isSuspended() { return _suspended; }

	/// <summary>
	/// Checks whether this Ore has been visited or not.
	/// </summary>
	/// <returns>True if it was, false if not</returns>
	inline bool visited() { return _visited; }

	/// <summary>
	/// Flag that sets whether the mouse is hovering this Ore or not.
	/// </summary>
	bool hover = false;

	/// <summary>
	/// Flag that sets whether this Ore was clicked or not.
	/// </summary>
	bool clicked = false;


private:
	OreData _oreData;

	Vector2 _gridCoords;
	Vector2 _gridRoot;
	Vector2 _oreDimensions;
	Vector2 _targetPosition;

	Sprite* _sprite = nullptr;
	Transform* _transform = nullptr;

	bool _visited = false;

	bool _suspended = false; // Flag to check if this ore is suspended mid-air inside the grid, with no blocks underneath it.
	float _moveDuration = 0.f;
	float _timeElapsed = 0.f;
};
