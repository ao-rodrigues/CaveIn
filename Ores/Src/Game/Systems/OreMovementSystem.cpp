#include "OreMovementSystem.h"

#include "../../Engine/Engine.h"
#include "../Components/Ore.h"

void OreMovementSystem::update()
{
	for (auto& oreEntity : _entityManager->getEntitiesWithComponentAll<Ore>())
	{
		Ore& ore = oreEntity->getComponent<Ore>();

		if (ore.getTransform().position == ore.getTargetPosition())
		{
			continue;
		}

		Vector2 moveDir = ore.getTargetPosition() - ore.getTransform().position;
		ore.getTransform().position += moveDir * ORE_MOVE_SPEED * Engine::instance().deltaTime();

		if (ore.getTransform().position.x > ore.getTargetPosition().x && ore.getTransform().position.y > ore.getTargetPosition().y)
		{
			ore.getTransform().position = ore.getTargetPosition();
		}
	}
}