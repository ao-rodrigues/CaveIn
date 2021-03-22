#pragma once

#include "../../Engine/ECS/ECS.h"

class ShowHighScoreEvent : public Component
{
public:
	ShowHighScoreEvent(int highScore, int finalScore)
		: highScore(highScore)
		, finalScore(finalScore)
	{ }

	int highScore = 0;
	int finalScore = 0;
};
