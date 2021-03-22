#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Button.h"

/// <summary>
/// This system handles the "Push Column" button
/// </summary>
class PushColumnSystem : public System
{
public:
	using System::System;
	void init() override;
	virtual void update() override;

private:
	Button* _pushColumnButton = nullptr;
	bool _gameRunning = false;
};
