#pragma once

#include <SDL.h>
#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Text.h"
#include "../../Engine/ECS/Components/Transform.h"

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
		text = &entity->getComponent<Text>();
		transform = &entity->getComponent<Transform>();

		_defaultColor = text->textColor;
		_defaultPosition = transform->position;
	}

	void reset()
	{
		text->setTextColor(_defaultColor);
		transform->position = _defaultPosition;
	}

	float lifetime = 0.f;
	unsigned int spawnTime = 0u;
	Text* text = nullptr;
	Transform* transform = nullptr;

private:
	SDL_Color _defaultColor;
	Vector2 _defaultPosition;
};