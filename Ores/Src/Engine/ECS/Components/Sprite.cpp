#include "Sprite.h"
#include "../../Engine.h"

void Sprite::init()
{
	transform = &entity->getComponent<Transform>();
	texture = AssetManager::instance().getTexture(textureID);

	_srcRect.x = 0;
	_srcRect.y = 0;
	_srcRect.w = width;
	_srcRect.h = height;

	_dstRect.x = static_cast<int>(transform->position.x);
	_dstRect.y = static_cast<int>(transform->position.y);
	_dstRect.w = static_cast<int>(width * transform->scale.x);
	_dstRect.h = static_cast<int>(height * transform->scale.y);

	makeDstRelativeToCamera();
}

void Sprite::makeDstRelativeToCamera()
{
	// Make final destination relative to camera
	SDL_Rect camera = Engine::instance().getCamera();
	_dstRect.x -= camera.x;
	_dstRect.y -= camera.y;
}