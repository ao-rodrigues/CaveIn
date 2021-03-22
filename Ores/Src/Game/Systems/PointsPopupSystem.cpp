#include "PointsPopupSystem.h"

#include "../Events/OreDestroyedEvent.h"
#include "../Components/PointsPopup.h"
#include "../OreData.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Math/Math.h"

void PointsPopupSystem::init()
{
	AssetManager::instance().loadFont("PopupFont", "Assets/Fonts/Alagard.ttf", 16);
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
	}

	auto popupEntities = _entityManager->getEntitiesWithComponentAll<PointsPopup>();
	for (auto& entity : popupEntities)
	{
		PointsPopup& popup = entity->getComponent<PointsPopup>();

		Vector2 newPosition = popup.getText().getTransform().position;
		newPosition.y -= POPUP_MOVE_SPEED * Engine::instance().deltaTime();

		popup.getText().getTransform().position = newPosition;

		float timePassed = (SDL_GetTicks() - popup.getSpawnTime()) / 1000.f;
		if (timePassed > popup.getLifetime())
		{
			entity->destroy();
			continue;
		}

		SDL_Color newColor = popup.getText().getTextColor();
		newColor.a = static_cast<int>(lerp(255.f, 0.f, timePassed / popup.getLifetime()));
		popup.getText().setTextColor(newColor);
	}
}

void PointsPopupSystem::spawnPopup(OreData oreData, Vector2 position)
{
	Entity& newPopup = Engine::instance().createEntity();
	SDL_Color popupColor = { 58, 240, 119, 255 };
	newPopup.addComponent<Text>("PopupFont", 1, std::to_string(oreData.destructionPoints), popupColor, 100).getTransform().position = position;
	newPopup.addComponent<PointsPopup>(1.7f);
}