#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Math/Vector2.h"

class HoverCursorAttachEvent : public Component
{
public:
	HoverCursorAttachEvent(const Vector2& position)
		: position(position)
	{}

	const Vector2& position;
};