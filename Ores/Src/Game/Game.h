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
#include "Systems/HighScoreSystem.h"

class Game
{
public:
	Game() {}
	void init();
	void update();

private:
	/// <summary>
	/// Loads the game cursor.
	/// </summary>
	void loadCursor();

	/// <summary>
	/// Loads the environment.
	/// </summary>
	void loadEnvironment();

	/// <summary>
	/// Loads the FPS counter.
	/// </summary>
	void loadFPSCounter();

	/// <summary>
	/// Updates the FPS counter.
	/// </summary>
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
	HighScoreSystem* _highScoreSystem = nullptr;
	FallingOresSystem* _fallingOresSystem = nullptr;
	PointsPopupSystem* _pointsPopupSystem = nullptr;
	PushTimerSystem* _pushTimerSystem = nullptr;
	PushColumnSystem* _pushColumnSystem = nullptr;
	ClearEventsSystem* _clearEventsSystem = nullptr;
};