#pragma once

#include "../../Engine/ECS/ECS.h"

class MenuSystem : public System
{
public:
	enum GameState
	{
		MainMenu,
		Playing,
		Paused
	};

	using System::System;

	void init() override;
	virtual void update() override;
};