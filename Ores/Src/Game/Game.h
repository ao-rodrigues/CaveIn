#pragma once

#include "Systems/OreClickSystem.h"
#include "Systems/HoverCursorSystem.h"
#include "Systems/OreGridSystem.h"
#include"Systems/OreMovementSystem.h"
#include "Systems/ScoreSystem.h"
#include "Systems/PointsPopupSystem.h"
#include "Systems/PushTimerSystem.h"

class Game
{
public:
	Game() {}
	void init();
	void update();

private:
	void loadMusic();
	void loadCursor();
	void loadBackground();
	void loadCharacters();

	OreClickSystem* _oreClickSystem = nullptr;
	HoverCursorSystem* _hoverCursorSystem = nullptr;
	OreGridSystem* _oreGridSystem = nullptr;
	OreMovementSystem* _oreMovementSystem = nullptr;
	ScoreSystem* _scoreSystem = nullptr;
	PointsPopupSystem* _pointsPopupSystem = nullptr;
	PushTimerSystem* _pushTimerSystem = nullptr;
};