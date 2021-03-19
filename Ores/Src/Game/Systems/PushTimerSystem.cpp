#include "PushTimerSystem.h"

#include "../../Engine/AssetManager.h"
#include "../../Engine/Engine.h"
#include "../../Engine/ECS/Components/Text.h"
#include "../Events/PushEvent.h"


void PushTimerSystem::init()
{
	AssetManager::instance().loadTexture("ProgressBarFgAlt", "Assets/Textures/progress_bar_fg_alt.png");

	SDL_Color textColor = { 255, 255, 255, 255 };
	Engine::instance().createEntity().addComponent<Text>("ScoreFont", 0, "Push:", textColor).setPosition(Vector2(350.f, 10.f));

	Sprite& progressbarBg = Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 0, "ProgressBarBg", 125, 25);
	progressbarBg.transform->position.x = 410.f;
	progressbarBg.transform->position.y = 5.f;

	_progressBarFg = &Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 1, "ProgressBarFgAlt", 113, 16);
	_progressBarFg->transform->position.x = 410.f + (125.f - 113.f) / 2.f;
	_progressBarFg->transform->position.y = 5.f + (25.f - 16.f) / 2.f;
	_progressBarFg->srcWidth = 0;
	_progressBarFg->dstWidth = 0;
}

void PushTimerSystem::update()
{
	unsigned int timePassed = SDL_GetTicks() - _lastPushTime;

	_progressBarFg->srcWidth = 113 * timePassed / TIMER_DURATION;
	_progressBarFg->dstWidth = 113 * timePassed / TIMER_DURATION;

	if (timePassed >= TIMER_DURATION)
	{
		// Send push event
		_entityManager->createEntity().addComponent<PushEvent>();

		// Reset timer
		_lastPushTime = SDL_GetTicks();
		_progressBarFg->srcWidth = 0;
		_progressBarFg->dstWidth = 0;
	}
}