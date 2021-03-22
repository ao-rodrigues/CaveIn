#include "PushColumnSystem.h"
#include "../../Engine/AssetManager.h"
#include "../../Engine/Engine.h"
#include "../../Engine/ECS/Components/Sprite.h"
#include "../../Engine/ECS/Components/Transform.h"
#include "../../Engine/ECS/Components/Text.h"
#include "../Events/PushEvent.h"
#include "../../Engine/Math/Vector2.h"
#include "../Events/StartGameEvent.h"
#include "../Events/PauseGameEvent.h"
#include "../Events/ResumeGameEvent.h"
#include "../Events/GameOverEvent.h"

void PushColumnSystem::init()
{
	AssetManager::instance().loadTexture("PushColButtonDefault", "Assets/Textures/button.png");
	AssetManager::instance().loadTexture("PushColButtonHover", "Assets/Textures/button_hover.png");
	AssetManager::instance().loadTexture("PushColButtonDown", "Assets/Textures/button_down.png");

	AssetManager::instance().loadFont("PushButtonFont", "Assets/Fonts/Alagard.ttf", 24);

	Engine& engine = Engine::instance();
	
	Entity& buttonEntity = engine.createEntity();
	Sprite& buttonSprite = buttonEntity.addComponent<Sprite>(RenderLayer::UI, 0, "PushColButtonDefault", 0, 0, 300, 87);

	SDL_Color textColor = { 255, 255, 255, 255 };
	Text& buttonText = buttonEntity.addComponent<Text>("PushButtonFont", 1, "Push", textColor, 100);
	_pushColumnButton = &buttonEntity.addComponent<Button>("PushColButtonDefault", "PushColButtonHover", "PushColButtonDown");

	// Calculate the (x,y) values to center the text inside the button
	float textX = (buttonSprite.dstRect()->w / 2.f) - (buttonText.dstRect()->w / 2.f);
	float textY = (buttonSprite.dstRect()->h / 2.f) - (buttonText.dstRect()->h / 2.f);

	buttonText.setRelativePosition(Vector2(textX, textY));

	Transform& buttonTransform = buttonEntity.getComponent<Transform>();
	buttonTransform.scale = Vector2(0.7f, 0.7f);
	buttonTransform.position = Vector2(engine.getWorldDimensions().x - 230.f, engine.getWorldDimensions().y - 130.f);
}

void PushColumnSystem::update()
{
	if (!_gameRunning)
	{
		auto startGameEvents = _entityManager->getEntitiesWithComponentAll<StartGameEvent>();
		if (startGameEvents.size() > 0)
		{
			_gameRunning = true;
			_pushColumnButton->entity->setEnabled(true);
		}
		else
		{
			// Check if game has been resumed
			auto resumeGameEvents = _entityManager->getEntitiesWithComponentAll<ResumeGameEvent>();
			if (resumeGameEvents.size() > 0)
			{
				_gameRunning = true;
				_pushColumnButton->entity->setEnabled(true);
			}
			else
			{
				_pushColumnButton->entity->setEnabled(false);
				return;
			}
		}
	}

	// Check if the game has been paused
	auto pauseGameEvents = _entityManager->getEntitiesWithComponentAll<PauseGameEvent>();
	if (pauseGameEvents.size() > 0)
	{
		_gameRunning = false;
		_pushColumnButton->entity->setEnabled(false);
		return;
	}

	// Check if the game is over
	auto gameOverEvents = _entityManager->getEntitiesWithComponentAll<GameOverEvent>();
	if (gameOverEvents.size() > 0)
	{
		_gameRunning = false;
		_pushColumnButton->entity->setEnabled(false);
		return;
	}

	if (_pushColumnButton->buttonReleased() && _pushColumnButton->wasPressed())
	{
		// Send push column event
		_entityManager->createEntity().addComponent<PushEvent>().entity->setDestroyNextFrame(true);
	}
}