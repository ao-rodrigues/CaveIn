#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Sprite.h"

constexpr unsigned int TIMER_DURATION = 10000;

class PushTimerSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;

private:
	unsigned int _lastPushTime = 0;
	Sprite* _progressBarFg = nullptr;
};
