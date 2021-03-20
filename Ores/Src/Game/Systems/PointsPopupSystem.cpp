#include "PointsPopupSystem.h"

#include "../Events/OreDestroyedEvent.h"
#include "../Components/PointsPopup.h"
#include "../OreData.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Math/Math.h"

void PointsPopupSystem::init()
{
	AssetManager::instance().loadFont("PopupFont", "Assets/Fonts/Alagard.ttf", 14);
}

void PointsPopupSystem::update()
{
	auto oreDestroyedEvents = _entityManager->getEntitiesWithComponentAll<OreDestroyedEvent>();
	for (auto& event : oreDestroyedEvents)
	{
		OreDestroyedEvent oreDestroyedEvent = event->getComponent<OreDestroyedEvent>();
		OreData oreData = oreDestroyedEvent.oreData;
		Vector2 position = oreDestroyedEvent.position;
		position.x += 5.f;

		spawnPopup(oreData, position);
		//event->destroy();
	}

	auto popupEntities = _entityManager->getEntitiesWithComponentAll<PointsPopup>();
	for (auto& entity : popupEntities)
	{
		PointsPopup& popup = entity->getComponent<PointsPopup>();

		Vector2 newPosition = popup.text->transform->position;
		newPosition.y -= POPUP_MOVE_SPEED * Engine::instance().deltaTime;

		popup.text->setPosition(newPosition);

		float timePassed = (SDL_GetTicks() - popup.spawnTime) / 1000.f;
		if (timePassed > popup.lifetime)
		{
			entity->destroy();
			//std::cout << "Destroyed popup!" << std::endl;
			continue;
		}

		SDL_Color newColor = popup.text->textColor;
		newColor.a = lerp(255.f, 0.f, timePassed / popup.lifetime);
		popup.text->setTextColor(newColor);
	}
}

void PointsPopupSystem::spawnPopup(OreData oreData, Vector2 position)
{
	Entity& newPopup = Engine::instance().createEntity();
	SDL_Color popupColor = { 21, 232, 156, 255 };
	newPopup.addComponent<Text>("PopupFont", 1, std::to_string(oreData.destructionPoints), popupColor).setPosition(position);
	newPopup.addComponent<PointsPopup>(1.5f);
}