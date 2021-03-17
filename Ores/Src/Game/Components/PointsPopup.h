#pragma once

#include <SDL.h>
#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Text.h"

class PointsPopup : public Component
{
public:
	PointsPopup(float lifetime)
		: lifetime(lifetime)
	{
		spawnTime = SDL_GetTicks();
	}

	void init() override
	{
		if (!entity->hasComponent<Text>())
		{
			std::cerr << "PointsPopup requires component Text!" << std::endl;
		}

		text = &entity->getComponent<Text>();
	}

	float lifetime = 0.f;
	float spawnTime = 0.f;
	Text* text = nullptr;
};