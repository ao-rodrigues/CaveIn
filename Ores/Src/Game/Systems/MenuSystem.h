#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Text.h"
#include "../../Engine/ECS/Components/Sprite.h"

class MenuSystem : public System
{
public:

	using System::System;

	void init() override;
	virtual void update() override;

private:
	enum GameState
	{
		MainMenu,
		Tutorial,
		Playing,
		Paused,
		GameOver
	};

	void updateMainMenu();
	void updateTutorialMenu();
	void handlePlayingEvents();
	void updatePausedMenu();
	void updateGameOverMenu();

	Text* _title = nullptr;
	Entity* _startGameButton = nullptr;
	Entity* _tutorialPanel = nullptr;
	Entity* _tutorialBanner = nullptr;
	Entity* _resumeButton = nullptr;
	Entity* _pausedBanner = nullptr;
	Entity* _gameOverBanner = nullptr;
	Entity* _retryButton = nullptr;

	GameState _currentState = GameState::MainMenu;

	void setState(GameState newState);
};