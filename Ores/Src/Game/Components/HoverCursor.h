#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Math/Vector2.h"

class Transform;
class Sprite;

class HoverCursor : public Component
{
public:
	void init() override;

	void use();
	void release();
	void setPosition(Vector2 position);
	void setVisible(bool visible);

private:
	Transform* _transform = nullptr;
	Sprite* _sprite = nullptr;
	bool _inUse = false;
};