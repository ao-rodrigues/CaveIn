#pragma once

#include <unordered_set>
#include <SDL.h>
#include "Math/Vector2.h"

class InputManager
{
public:
	static void handleEvent(const SDL_Event& event);

	static bool keyDown(int key) { return _keyDowns.count(key) != 0; }
	static bool keyUp(int key) { return _keyUps.count(key) != 0; }
	static bool mouseButtonDown(int8_t button) { return _mouseButtonDowns.count(button) != 0; }
	static bool mouseButtonUp(int8_t button) { return _mouseButtonUps.count(button) != 0; }
	static Vector2 mousePosition() { return _mousePosition; }
	static Vector2 mouseDelta() { return _mouseDelta; }
	static Vector2 mouseWheel() { return _mouseWheel; }

	static void clearEvents();

private:
	static std::unordered_set<int> _keyDowns;
	static std::unordered_set<int> _keyUps;

	static std::unordered_set<int8_t> _mouseButtonDowns;
	static std::unordered_set<int8_t> _mouseButtonUps;

	static Vector2 _mousePosition;
	static Vector2 _mouseDelta;
	static Vector2 _mouseWheel;
};
