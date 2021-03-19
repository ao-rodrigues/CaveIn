#pragma once

#include "../ECS.h"
#include "../../Math/Vector2.h"

class Transform : public Component
{
public:
	Transform() 
	{
		scale.x = 1.f;
		scale.y = 1.f;
	}

	Transform(float xPos, float yPos)
	{
		position.x = xPos;
		position.y = yPos;
		scale.x = 1.f;
		scale.y = 1.f;
	}

	Transform(float xPos, float yPos, float xScale, float yScale)
	{
		position.x = xPos;
		position.y = yPos;
		scale.x = xScale;
		scale.y = yScale;
	}

	~Transform()
	{

	}

	Vector2 position;
	Vector2 scale = { 1, 1 };
	float rotation = 0.f;
};