#pragma once

#include "../../Engine/ECS/ECS.h"

class WriteScoreEvent : public Component
{
public:
	WriteScoreEvent(int score, int level)
		: score(score)
		, level(level)
	{ }

	int score = 0;
	int level = 1;
};