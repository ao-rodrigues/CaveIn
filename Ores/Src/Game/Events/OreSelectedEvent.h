#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Math/Vector2.h"

class OreSelectedEvent : public Component
{
public:
	OreSelectedEvent(Vector2 gridCoords, int typeIndex)
		: gridCoords(gridCoords)
		, typeIndex(typeIndex)
	{ }

	Vector2 gridCoords;
	int typeIndex;
};
