#include "PushTimerSystem.h"

#include "../../Engine/AssetManager.h"
#include "../../Engine/Engine.h"
#include "../../Engine/ECS/Components/Text.h"
#include "../Events/PushEvent.h"


void PushTimerSystem::init()
{
	AssetManager::instance().loadTexture("ProgressBarFgAlt", "Assets/Textures/progress_bar_fg_2_alt.png");

	SDL_Color textColor = { 255, 255, 255, 255 };
	Engine::instance().createEntity().addComponent<Text>("ScoreFont", 0, "Push:", textColor).setPosition(Vector2(420.f, 10.f));

	Sprite& progressBarBg = Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 0, "ProgressBarBg", 0, 0, 569, 81);
	progressBarBg.transform->scale = Vector2(0.3f, 0.3f);
	progressBarBg.transform->position.x = 480.f;
	progressBarBg.transform->position.y = 5.f;

	_progressBarFg = &Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 1, "ProgressBarFgAlt", 0, 0, 532, 42);
	_progressBarFg->transform->scale = Vector2(0.3f, 0.3f);
	_progressBarFg->transform->position.x = 480.f + 0.3f * (569.f - 532.f) / 2.f;
	_progressBarFg->transform->position.y = 5.f + 0.3f * (81.f - 42.f) / 2.f;
	_progressBarFg->srcWidth = 0;
	_progressBarFg->dstWidth = 0;
}

void PushTimerSystem::update()
{
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