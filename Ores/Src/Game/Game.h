#pragma once

#include "Systems/MenuSystem.h"
#include "Systems/CharacterSystem.h"
#include "Systems/OreClickSystem.h"
#include "Systems/HoverCursorSystem.h"
#include "Systems/OreGridSystem.h"
#include"Systems/OreMovementSystem.h"
#include "Systems/ScoreSystem.h"
#include "Systems/PointsPopupSystem.h"
#include "Systems/PushTimerSystem.h"
#include "Systems/SoundSystem.h"
#include "Systems/FallingOresSystem.h"
#include "Systems/ClearEventsSystem.h"
#include "Systems/PushColumnSystem.h"

class Game
{
public:
	Game() {}
	void init();
	void update();

private:
	void loadCursor();
	void loadEnvironment();
	void loadCharacters();
	void loadFPSCounter();
	void updateFPSCounter();

	Text* _fpsCounter = nullptr;

	MenuSystem* _menuSystem = nullptr;
	CharacterSystem* _characterSystem = nullptr;
	OreClickSystem* _oreClickSystem = nullptr;
	HoverCursorSystem* _hoverCursorSystem = nullptr;
	OreGridSystem* _oreGridSystem = nullptr;
	OreMovementSystem* _oreMovementSystem = nullptr;
	ScoreSystem* _scoreSystem = nullptr;
	SoundSystem* _soundSystem = nullptr;
	FallingOresSystem* _fallingOresSystem = nullptr;
	PointsPopupSystem* _pointsPopupSystem = nullptr;
	PushTimerSystem* _pushTimerSystem = nullptr;
	PushColumnSystem* _pushColumnSystem = nullptr;
	ClearEventsSystem* _clearEventsSystem = nullptr;
};