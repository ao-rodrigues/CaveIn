#include "FallingOresSystem.h"

#include <stdlib.h>

#include "../../Engine/Engine.h"

#include "../Events/OreDestroyedEvent.h"
#include "../Events/OreDestroyedInLevelUpEvent.h"

#include "../../Engine/ECS/Components/Sprite.h"
#include "../Components/FallingOre.h"

constexpr float THROW_FORCE = 15.f;
constexpr float GRAVITY_FORCE = 9.f;
constexpr unsigned int FALLING_ORE_LIFETIME = 1500;
constexpr float MIN_ROT_SPEED = 80.f;
constexpr float MAX_ROT_SPEED = 90.f;


void FallingOresSystem::init()
{
	srand(time(0));
}

void FallingOresSystem::update()
{
	for (auto& event : _entityManager->getEntitiesWithComponentAny<OreDestroyedEvent, OreDestroyedInLevelUpEvent>())
	{
		if (event->hasComponent<OreDestroyedEvent>())
		{
			OreDestroyedEvent& oreDestroyedEvent = event->getComponent<OreDestroyedEvent>();
			spawnFallingOre(oreDestroyedEvent.oreData, oreDestroyedEvent.position);
		}
		else if (event->hasComponent<OreDestroyedInLevelUpEvent>())
		{
			OreDestroyedInLevelUpEvent& oreDestroyedEvent = event->getComponent<OreDestroyedInLevelUpEvent>();
			spawnFallingOre(oreDestroyedEvent.oreData, oreDestroyedEvent.position);
		}
	}

	for (auto& fallingOreEntity : _entityManager->getEntitiesWithComponentAll<FallingOre>())
	{
		FallingOre& fallingOre = fallingOreEntity->getComponent<FallingOre>();
		Vector2 currVelocity = fallingOre.getVelocity();
		currVelocity += Vector2::down() * GRAVITY_FORCE * Engine::instance().deltaTime();
		fallingOre.setVelocity(currVelocity);

		Transform& oreTransform = fallingOre.getTransform();
		oreTransform.position += currVelocity;

		float newRotation = fallingOre.getRotationSpeed() * Engine::instance().deltaTime();
		oreTransform.rotation += fallingOre.rotatesLeft() ? 360.f - newRotation : newRotation;

		if (SDL_GetTicks() - fallingOre.getSpawnTime() >= fallingOre.getLifetime())
		{
			fallingOre.entity->destroy();
		}
	}
}

void FallingOresSystem::spawnFallingOre(OreData oreData, Vector2 position)
{
	// Calculates whether the ore will be thrown left or right
	float dir = static_cast<float>(rand() / static_cast<float>(RAND_MAX)) > 0.5f ? 1.f : -1.f;

	// Calculates a velocity value for X between 0.5 and 1
	float x = 0.5f + static_cast<float>(rand() / static_cast<float>(RAND_MAX / (1.f - 0.5f)));

	// Calculates a velocity value for X between -1 and -0.5 (negative Y means UP)
	float y = -1.f + static_cast<float>(rand() / static_cast<float>(RAND_MAX / (-0.5f + 1.f)));

	// Rotation speed between MIN_ROT_SPEED and MAX_ROT_SPEED
	float rotSpeed = MIN_ROT_SPEED + static_cast<float>(rand() / static_cast<float>(RAND_MAX / (MAX_ROT_SPEED - MIN_ROT_SPEED)));
	bool rotateRight = static_cast<float>(rand() / static_cast<float>(RAND_MAX)) > 0.5f;

	Entity& fallingOre = Engine::instance().createEntity();
	fallingOre.addComponent<Sprite>(RenderLayer::Foreground, 10, oreData.textureID, 0, 0, 32, 32);
	fallingOre.addComponent<FallingOre>(Vector2(x * dir, y), rotSpeed, rotateRight, FALLING_ORE_LIFETIME);
	fallingOre.getComponent<Transform>().position = position;
}
