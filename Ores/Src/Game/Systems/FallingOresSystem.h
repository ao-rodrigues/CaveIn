#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../OreData.h"
#include "../../Engine/Math/Vector2.h"


class FallingOresSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;

private:
	void spawnFallingOre(OreData oreData, Vector2 position);
};
