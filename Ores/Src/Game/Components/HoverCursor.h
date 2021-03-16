#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Math/Vector2.h"

#include "../../Engine/ECS/Components/Transform.h"
#include "../../Engine/ECS/Components/Sprite.h"

class HoverCursor : public Component
{
public:
	void init() override
	{
		_transform = &entity->getComponent<Transform>();
		_sprite = &entity->getComponent<Sprite>();
		_sprite->setVisible(false);
	}

	void setPosition(Vector2 position)
	{
		_transform->position = position;
	}

	void setVisible(bool visible)
	{
		_sprite->setVisible(visible);
	}

private:
	Transform* _transform = nullptr;
	Sprite* _sprite = nullptr;
};