#pragma once

#include <unordered_set>
#include <SDL.h>
#include "Math/Vector2.h"

class InputManager
{
public:
	static void handleEvent(const SDL_Event& event);

	inline static bool keyDown(int key) { return _keysDown.count(key) != 0; }
	inline static bool keyUp(int key) { return _keysUp.count(key) != 0; }
	inline static bool keyPressed(int key) { return _keysPressed.count(key) != 0; }
	inline static bool mouseButtonDown(int8_t button) { return _mouseButtonsDown.count(button) != 0; }
	inline static bool mouseButtonUp(int8_t button) { return _mouseButtonsUp.count(button) != 0; }
	inline static bool mouseButtonPressed(int8_t button) { return _mouseButtonsPressed.count(button) != 0; }
	inline static Vector2 mousePosition() { return _mousePosition; }
	inline static Vector2 mouseDelta() { return _mouseDelta; }
	inline static Vector2 mouseWheel() { return _mouseWheel; }

	static void clearEvents();
	static void clearFrameEvents();

private:
	static std::unordered_set<int> _keysDown;
	static std::unordered_set<int> _keysUp;
	static std::unordered_set<int> _keysPressed;

	static std::unordered_set<int8_t> _mouseButtonsDown;
	static std::unordered_set<int8_t> _mouseButtonsUp;
	static std::unordered_set<int8_t> _mouseButtonsPressed;

	static Vector2 _mousePosition;
	static Vector2 _mouseDelta;
	static Vector2 _mouseWheel;
};
