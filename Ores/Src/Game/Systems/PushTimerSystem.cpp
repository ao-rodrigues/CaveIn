#include "PushTimerSystem.h"

#include "../../Engine/AssetManager.h"
#include "../../Engine/Engine.h"
#include "../../Engine/ECS/Components/Text.h"
#include "../Events/PushEvent.h"
#include "../Events/StartGameEvent.h"
#include "../Events/GameOverEvent.h"
#include "../Events/PauseGameEvent.h"
#include "../Events/ResumeGameEvent.h"


void PushTimerSystem::init()
{
	AssetManager::instance().loadTexture("ProgressBarFgAlt", "Assets/Textures/progress_bar_fg_2_alt.png");

	SDL_Color textColor = { 255, 255, 255, 255 };
	_progressBarLabel = &Engine::instance().createEntity().addComponent<Text>("ScoreFont", 0, "Push:", textColor, 100);
	_progressBarLabel->transform->position = Vector2(420.f, 10.f);
	_progressBarLabel->entity->setEnabled(false);

	_progressBarBg = &Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 0, "ProgressBarBg", 0, 0, 569, 81);
	_progressBarBg->transform->scale = Vector2(0.3f, 0.3f);
	_progressBarBg->transform->position.x = 480.f;
	_progressBarBg->transform->position.y = 5.f;
	_progressBarBg->entity->setEnabled(false);

	_progressBarFg = &Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 1, "ProgressBarFgAlt", 0, 0, 532, 42);
	_progressBarFg->transform->scale = Vector2(0.3f, 0.3f);
	_progressBarFg->transform->position.x = 480.f + 0.3f * (569.f - 532.f) / 2.f;
	_progressBarFg->transform->position.y = 5.f + 0.3f * (81.f - 42.f) / 2.f;
	_progressBarFg->srcWidth = 0;
	_progressBarFg->dstWidth = 0;
	_progressBarFg->entity->setEnabled(false);
}

void PushTimerSystem::update()
{
	if (!_gameRunning)
	{
		auto startGameEvents = _entityManager->getEntitiesWithComponentAll<StartGameEvent>();
		if (startGameEvents.size() > 0)
		{
			_gameRunning = true;
			_lastPushTime = SDL_GetTicks();
			_progressBarLabel->entity->setEnabled(true);
			_progressBarBg->entity->setEnabled(true);
			_progressBarFg->entity->setEnabled(true);
		}
		else
		{
			// Check if game has been resumed
			auto resumeGameEvents = _entityManager->getEntitiesWithComponentAll<ResumeGameEvent>();
			if (resumeGameEvents.size() > 0)
			{
				_gameRunning = true;
				_lastPushTime += SDL_GetTicks() - _pausedTime;
			}
			else
			{
				return;
			}
		}
	}

	// Check if the game has been paused
	auto pauseGameEvents = _entityManager->getEntitiesWithComponentAll<PauseGameEvent>();
	if (pauseGameEvents.size() > 0)
	{
		_gameRunning = false;
		_pausedTime = SDL_GetTicks();
		return;
	}

	// Check if the game is over
	auto gameOverEvents = _entityManager->getEntitiesWithComponentAll<GameOverEvent>(true);
	if (gameOverEvents.size() > 0)
	{
		_gameRunning = false;
		return;
	}

	unsigned int timePassed = SDL_GetTicks() - _lastPushTime;

	_progressBarFg->srcWidth = 532 * timePassed / TIMER_DURATION;
	_progressBarFg->dstWidth = 532 * timePassed / TIMER_DURATION;

	if (timePassed >= TIMER_DURATION)
	{
		// Send push event
		_entityManager->createEntity().addComponent<PushEvent>().entity->setDestroyNextFrame(true);

		// Reset timer
		_lastPushTime = SDL_GetTicks();
		_progressBarFg->srcWidth = 0;
		_progressBarFg->dstWidth = 0;
	}
}