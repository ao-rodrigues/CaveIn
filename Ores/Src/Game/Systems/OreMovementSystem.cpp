#include "OreMovementSystem.h"

#include "../../Engine/Engine.h"
#include "../Components/Ore.h"

void OreMovementSystem::update()
{
	for (auto& oreEntity : _entityManager->getEntitiesWithComponentAll<Ore>())
	{
		Ore& ore = oreEntity->getComponent<Ore>();

		if (ore._transform->position == ore.targetPosition)
		{
			ore.flagNotMoving();
			continue;
		}

		Vector2 moveDir = ore.targetPosition - ore._transform->position;
		ore._transform->position += moveDir * ORE_MOVE_SPEED * Engine::instance().deltaTime();

		if (ore._transform->position.x > ore.targetPosition.x && ore._transform->position.y > ore.targetPosition.y)
		{
			ore._transform->position = ore.targetPosition;
			ore.flagNotMoving();
		}
	}
}