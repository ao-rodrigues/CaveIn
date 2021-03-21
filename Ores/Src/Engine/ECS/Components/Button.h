#pragma once

#include "../ECS.h"
#include "Sprite.h"

class Button : public Component
{
public:
	Button() 
		: _defaultTextureID("")
		, _hoverTextureID("")
		, _downTextureID("")
	{}

	Button(const std::string& defaultTextureID, const std::string& hoverTextureID, const std::string& downTextureID)
		: _defaultTextureID(defaultTextureID)
		, _hoverTextureID(hoverTextureID)
		, _downTextureID(downTextureID)
	{ }

	void init() override
	{
		_sprite = &entity->getComponent<Sprite>();
	}

	inline std::string getDefaultTextureID() { return _defaultTextureID; }
	inline void setDefaultTextureID(const std::string& defaultTextureID) { _defaultTextureID = defaultTextureID; }

	inline std::string getHoverTextureID() { return _hoverTextureID; }
	inline void setHoverTextureID(const std::string hoverTextureID) { _hoverTextureID = hoverTextureID; }

	inline std::string getDownTextureID() { return _downTextureID; }
	inline void setDownTextureID(const std::string& downTextureID) { _downTextureID = downTextureID; }

	inline bool wasPressed() { return _pressed; }
	inline void setPressed(bool pressed) { _pressed = pressed; }

	inline Sprite& getSprite() { return *_sprite; }

	/// <summary>
	/// Checks whether the mouse is hovering the button or not.
	/// </summary>
	/// <returns>True if the mouse is hovering, false if not.</returns>
	bool mouseHovering();

	/// <summary>
	/// Checks whether the button is currently being held down.
	/// </summary>
	/// <returns>True if it is, false if not.</returns>
	bool buttonDown();

	/// <summary>
	/// Checkes whether this button was released this frame.
	/// </summary>
	/// <returns>True if it was, false if not.</returns>
	bool buttonReleased();

private:
	std::string _defaultTextureID;
	std::string _hoverTextureID;
	std::string _downTextureID;

	bool _pressed = false;

	Sprite* _sprite = nullptr;
};
