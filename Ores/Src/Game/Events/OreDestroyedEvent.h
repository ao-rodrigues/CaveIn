#pragma once

#include "../../Engine/ECS/ECS.h"

#include "../OreData.h"
#include "../../Engine/Math/Vector2.h"

class OreDestroyedEvent : public Component
{
public:
	OreDestroyedEvent(OreData oreData, Vector2 position) 
		: oreData(oreData)
		, position(position)
	{}

	OreData oreData;
	Vector2 position;
};