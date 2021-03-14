#pragma once
#include "../../Engine/ECS/ECS.h"
#include "../OreData.h"

class Sprite;
class Transform;

class Ore : public Component
{
public:
	Ore(OreData oreData)
		: oreData(oreData)
	{
	}

	void init()
	{
		// TODO safety check if entity has needed components
		sprite = &entity->getComponent<Sprite>();
		transform = &entity->getComponent<Transform>();
	}

	void update() override;

	OreData oreData;
	Sprite* sprite;
	Transform* transform;

private:
	bool _clicked = false;
};
