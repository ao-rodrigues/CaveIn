#include "Ore.h"
#include "../../Engine/InputManager.h"
#include "../../Engine/Math/Vector2.h"
#include "../../Engine/ECS/Components/Sprite.h"
#include "../../Engine/ECS/Components/Animation.h"
#include "HoverCursor.h"

void Ore::update()
{
	Vector2 mousePos = InputManager::mousePosition();

	if (mousePos.x > _sprite->dstRect.x && mousePos.x < _sprite->dstRect.x + _sprite->dstRect.w
		&& mousePos.y > _sprite->dstRect.y && mousePos.y < _sprite->dstRect.y + _sprite->dstRect.h)
	{
		_hover = true;

		_hoverCursor.setPosition(_transform->position);
		_hoverCursor.setVisible(true);
		_hoverCursor.use();
	}
	else if (_hover)
	{
		_hoverCursor.release();
		_hoverCursor.setVisible(false);
		_hover = false;
	}

	if (_hover && InputManager::mouseButtonPressed(SDL_BUTTON_LEFT))
	{
		_clicked = true;
	}


	if (InputManager::mouseButtonUp(SDL_BUTTON_LEFT) && _clicked)
	{
		std::cout << "Clicked it" << std::endl;
		_hoverCursor.release();
		_hoverCursor.setVisible(false);
		entity->destroy();
	}
}