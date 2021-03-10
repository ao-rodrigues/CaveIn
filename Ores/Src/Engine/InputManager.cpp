#include "InputManager.h"

std::unordered_set<SDL_Keycode> InputManager::_keyDowns;
std::unordered_set<SDL_Keycode> InputManager::_keyUps;

std::unordered_set<int8_t> InputManager::_mouseButtonDowns;
std::unordered_set<int8_t> InputManager::_mouseButtonUps;

Vector2 InputManager::_mousePosition;
Vector2 InputManager::_mouseDelta;
Vector2 InputManager::_mouseWheel;

void InputManager::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		_keyDowns.emplace(event.key.keysym.sym);
		break;

	case SDL_KEYUP:
		_keyUps.emplace(event.key.keysym.sym);
		break;

	case SDL_MOUSEBUTTONUP:
		_mouseButtonUps.emplace(event.button.button);
		break;

	case SDL_MOUSEBUTTONDOWN:
		_mouseButtonDowns.emplace(event.button.button);
		break;

	case SDL_MOUSEMOTION:
		_mousePosition.x = static_cast<int>(event.motion.x);
		_mousePosition.y = static_cast<int>(event.motion.y);

		_mouseDelta.x = static_cast<int>(event.motion.xrel);
		_mouseDelta.y = static_cast<int>(event.motion.yrel);
		break;

	case SDL_MOUSEWHEEL:
		_mouseWheel.x = static_cast<int>(event.wheel.x);
		_mouseWheel.y = static_cast<int>(event.wheel.y);
		break;

	default:
		break;
	}
}

void InputManager::clearEvents()
{
	_keyUps.clear();
	_keyDowns.clear();

	_mouseButtonDowns.clear();
	_mouseButtonUps.clear();

	_mousePosition = { 0.f, 0.f };
	_mouseDelta = { 0.f, 0.f };
	_mouseWheel = { 0.f, 0.f };
}
