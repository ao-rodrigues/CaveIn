#pragma once

#include "../../Engine/ECS/ECS.h"

class HighScoreSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;
};