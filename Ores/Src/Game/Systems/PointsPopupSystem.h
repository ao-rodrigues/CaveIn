#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../OreData.h"
#include "../../Engine/Math/Vector2.h"

constexpr float POPUP_MOVE_SPEED = 20.f;

class PointsPopupSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;

private:
	void spawnPopup(OreData oreData, Vector2 position);
};