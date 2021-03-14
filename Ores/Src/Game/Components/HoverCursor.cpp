#include "HoverCursor.h"

#include "../../Engine/ECS/Components/Transform.h"
#include "../../Engine/ECS/Components/Sprite.h"

void HoverCursor::init()
{
	_transform = &entity->getComponent<Transform>();
	_sprite = &entity->getComponent<Sprite>();
	_sprite->setVisible(false);
}

void HoverCursor::use()
{
	_inUse = true;
}

void HoverCursor::release()
{
	_inUse = false;
}

void HoverCursor::setPosition(Vector2 position)
{
	if (_inUse) return; 

	_transform->position = position;
}

void HoverCursor::setVisible(bool visible)
{
	if (_inUse) return;

	_sprite->setVisible(visible);
}