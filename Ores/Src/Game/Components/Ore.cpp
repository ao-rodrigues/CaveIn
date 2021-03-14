#include "Ore.h"
#include "../../Engine/InputManager.h"
#include "../../Engine/Math/Vector2.h"
#include "../../Engine/ECS/Components/Sprite.h"

void Ore::update()
{
	Vector2 mousePos = InputManager::mousePosition();
	bool hover = false;

	if (mousePos.x > sprite->dstRect.x && mousePos.x < sprite->dstRect.x + sprite->dstRect.w
		&& mousePos.y > sprite->dstRect.y && mousePos.y < sprite->dstRect.y + sprite->dstRect.h)
	{
		//std::cout << "Hovering!" << std::endl;
		hover = true;
		sprite->texture = AssetManager::instance().getTexture(oreData.hoverTextureID);
	}
	else
	{
		sprite->texture = AssetManager::instance().getTexture(oreData.defaultTextureID);
	}

	//bool clicked = false;

	if (InputManager::mouseButtonDown(SDL_BUTTON_LEFT) && hover)
	{
		_clicked = true;
		//std::cout << "Clicked on ore!" << std::endl;
		sprite->texture = AssetManager::instance().getTexture(oreData.clickedTextureID);
	}

	if (InputManager::mouseButtonUp(SDL_BUTTON_LEFT) && _clicked && hover)
	{
		std::cout << "Stopped clicking on ore!" << std::endl;
		sprite->texture = AssetManager::instance().getTexture(oreData.hoverTextureID);
		entity->destroy();
	}

}