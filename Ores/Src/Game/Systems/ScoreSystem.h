#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Text.h"

constexpr int STARTER_LEVEL_UP_SCORE = 1200;

class ScoreSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;

private:
	int _score = 0;
	int _level = 1;
	int _levelUpScore = STARTER_LEVEL_UP_SCORE;
	float _levelUpScoreIncreaseRate = 0.2f;

	Text* _scoreDisplayText = nullptr;

	void updateScoreDisplay(int newScore);
	void updateLevel(int newScore);
};