#pragma once

#include "../../Engine/ECS/ECS.h"

#include "../Components/Ore.h"

class OreClickSystem : public System
{
public:
	using System::System;

	virtual void update() override;

private:
	void handleMouseInteractions(Ore& ore, const Vector2& mousePos);
};