#include "OreClickSystem.h"

#include "../../Engine/InputManager.h"

#include "../Components/Ore.h"
#include "../../Engine/ECS/Components/Sprite.h"
#include "../Components/HoverCursor.h"

#include "../Events/HoverCursorAttachEvent.h"
#include "../Events/HoverCursorReleaseEvent.h"
#include "../Events/OreSelectedEvent.h"

void OreClickSystem::update()
{
	Vector2 mousePos = InputManager::mousePosition();

	for (auto& oreEntity : _entityManager->getEntitiesWithComponent<Ore>())
	{
		handleMouseInteractions(oreEntity->getComponent<Ore>(), mousePos);
	}
}

void OreClickSystem::handleMouseInteractions(Ore& ore, const Vector2& mousePos)
{
	/*
	if (ore.isMoving())
	{
		_entityManager->createEntity().addComponent<HoverCursorReleaseEvent>();
		return;
	}
	*/

	Sprite* sprite = ore.getSprite();
	Transform* transform = ore.getTransform();

	if (mousePos.x > sprite->dstRect()->x && mousePos.x < sprite->dstRect()->x + sprite->dstRect()->w
		&& mousePos.y > sprite->dstRect()->y && mousePos.y < sprite->dstRect()->y + sprite->dstRect()->h)
	{
		
		ore.hover = true;

		// Create hover attach event
		_entityManager->createEntity().addComponent<HoverCursorAttachEvent>(transform->position);
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
