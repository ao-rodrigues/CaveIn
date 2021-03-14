#pragma once
#include "../../Engine/ECS/ECS.h"
#include "../OreData.h"

class Sprite;
class Transform;
class Animation;
class HoverCursor;

class Ore : public Component
{
public:
	Ore(OreData oreData, HoverCursor& hoverCursor)
		: _oreData(oreData)
		, _hoverCursor(hoverCursor)
	{
	}

	void init()
	{
		// TODO safety check if entity has needed components
		_transform = &entity->getComponent<Transform>();
		_sprite = &entity->getComponent<Sprite>();
	}

	void update() override;

private:
	OreData _oreData;
	Sprite* _sprite = nullptr;
	Transform* _transform = nullptr;
	HoverCursor& _hoverCursor;
	bool _hover = false;
	bool _clicked = false;
};
