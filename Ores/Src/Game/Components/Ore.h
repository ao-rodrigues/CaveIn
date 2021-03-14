#pragma once
#include "../../Engine/ECS/ECS.h"
#include "../OreData.h"

#include "../../Engine/Math/Vector2.h"

class Sprite;
class Transform;
class Animation;
class HoverCursor;

class Ore : public Component
{
public:
	Ore(OreData oreData, HoverCursor& hoverCursor, Vector2 gridCoords)
		: _oreData(oreData)
		, _hoverCursor(hoverCursor)
		, _gridCoords(gridCoords)
	{
	}

	void init()
	{
		// TODO safety check if entity has needed components
		_transform = &entity->getComponent<Transform>();
		_sprite = &entity->getComponent<Sprite>();
	}

	void update() override;

	inline OreData getOreData() { return _oreData; }

private:
	OreData _oreData;
	Vector2 _gridCoords;
	Sprite* _sprite = nullptr;
	Transform* _transform = nullptr;
	HoverCursor& _hoverCursor;
	bool _hover = false;
	bool _clicked = false;
};
