#include "OreClickSystem.h"

#include "../../Engine/InputManager.h"

#include "../Components/Ore.h"
#include "../../Engine/ECS/Components/Sprite.h"
#include "../Components/HoverCursor.h"

#include "../Events/HoverCursorAttachEvent.h"
#include "../Events/HoverCursorReleaseEvent.h"
#include "../Events/OreSelectedEvent.h"
#include "../Events/StartGameEvent.h"
#include "../Events/GameOverEvent.h"
#include "../Events/ResumeGameEvent.h"
#include "../Events/PauseGameEvent.h"

void OreClickSystem::update()
{
	if (!_gameRunning)
	{
		auto startGameEvents = _entityManager->getEntitiesWithComponentAll<StartGameEvent>();
		if (startGameEvents.size() > 0)
		{
			_gameRunning = true;
		}
		else
		{
			// Check if game has been resumed
			auto resumeGameEvents = _entityManager->getEntitiesWithComponentAll<ResumeGameEvent>();
			if (resumeGameEvents.size() > 0)
			{
				_gameRunning = true;
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
		return;
	}

	// Check if the game is over
	auto gameOverEvents = _entityManager->getEntitiesWithComponentAll<GameOverEvent>(true);
	if (gameOverEvents.size() > 0)
	{
		_gameRunning = false;
		return;
	}

	Vector2 mousePos = InputManager::mousePosition();

	for (auto& oreEntity : _entityManager->getEntitiesWithComponentAll<Ore>())
	{
		handleMouseInteractions(oreEntity->getComponent<Ore>(), mousePos);
	}
}

void OreClickSystem::handleMouseInteractions(Ore& ore, const Vector2& mousePos)
{
	Sprite& sprite = ore.getSprite();
	Transform& transform = ore.getTransform();

	if (mousePos.x > sprite.dstRect()->x && mousePos.x < sprite.dstRect()->x + sprite.dstRect()->w
		&& mousePos.y > sprite.dstRect()->y && mousePos.y < sprite.dstRect()->y + sprite.dstRect()->h)
	{
		
		ore.hover = true;

		// Create hover attach event
		_entityManager->createEntity().addComponent<HoverCursorAttachEvent>(transform.position);
	}
	else if (ore.hover)
	{
		ore.hover = false;

		// Create hover release event
		_entityManager->createEntity().addComponent<HoverCursorReleaseEvent>();
	}

	if (ore.hover && InputManager::mouseButtonPressed(SDL_BUTTON_LEFT))
	{
		ore.clicked = true;
	}

	if (InputManager::mouseButtonUp(SDL_BUTTON_LEFT) && ore.clicked)
	{
		ore.clicked = false;

		// Create hover cursor release event
		_entityManager->createEntity().addComponent<HoverCursorReleaseEvent>();

		// Create ore destroyed event
		_entityManager->createEntity().addComponent<OreSelectedEvent>(ore.getGridCoords(), ore.getOreData().typeIndex);
	}
}
