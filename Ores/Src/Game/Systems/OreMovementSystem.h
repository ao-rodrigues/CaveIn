#pragma once

#include "../../Engine/ECS/ECS.h"

constexpr float ORE_MOVE_SPEED = 20.f;

class OreMovementSystem : public System
{
public:
	using System::System;

	virtual void update() override;
};
