#pragma once

#include <SDL.h>
#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Text.h"
#include "../../Engine/ECS/Components/Transform.h"

class PointsPopup : public Component
{
public:
	PointsPopup(float lifetime)
		: _lifetime(lifetime)
	{
		_spawnTime = SDL_GetTicks();
	}

	void init() override
	{
		_text = &entity->getComponent<Text>();
		_transform = &entity->getComponent<Transform>();

		_defaultColor = _text->getTextColor();
		_defaultPosition = _transform->position;
	}

	/// <summary>
	/// Resets the popup.
	/// </summary>
	void reset()
	{
		_text->setTextColor(_defaultColor);
		_transform->position = _defaultPosition;
	}

	/// <summary>
	/// Returns the lifetime of this Popup.
	/// </summary>
	/// <returns>The lifetime in seconds</returns>
	inline float getLifetime() { return _lifetime; }

	/// <summary>
	/// Returns the spawn time of this Popup.
	/// </summary>
	/// <returns>The spawn time in milliseconds</returns>
	inline unsigned int getSpawnTime() { return _spawnTime; }

	/// <summary>
	/// Returns the Text component attached to the same Entity as this PointsPopup component.
	/// </summary>
	/// <returns>A reference to the Text component</returns>
	inline Text& getText() { return *_text; }

	/// <summary>
	/// Returns the Transform component attached to the same Entity as this PointsPopup component.
	/// </summary>
	/// <returns>A reference to the Transformn component</returns>
	inline Transform& getTransform() { return *_transform; }


private:
	float _lifetime = 0.f;
	unsigned int _spawnTime = 0u;
	Text* _text = nullptr;
	Transform* _transform = nullptr;
	SDL_Color _defaultColor;
	Vector2 _defaultPosition;
};