#pragma once

#include "../../Engine/ECS/ECS.h"

class ClearEventsSystem : public System
{
public:
	using System::System;

	virtual void update() override;
};
