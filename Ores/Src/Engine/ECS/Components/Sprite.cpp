#include "Sprite.h"
#include "../../Engine.h"

void Sprite::init()
{
	transform = &entity->getComponent<Transform>();
	texture = AssetManager::instance().getTexture(textureID);

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;

	dstRect.x = static_cast<int>(transform->position.x);
	dstRect.y = static_cast<int>(transform->position.y);
	dstRect.w = static_cast<int>(width * transform->scale.x);
	dstRect.h = static_cast<int>(height * transform->scale.y);

	makeDstRelativeToCamera();
}

void Sprite::makeDstRelativeToCamera()
{
	/*
	// Clamp final destination within world borders
	Vector2 worldDimensions = Engine::instance().getWorldDimensions();
	if (dstRect.x + dstRect.w > worldDimensions.x)
	{
		dstRect.x = worldDimensions.x - dstRect.w;
	}

	if (dstRect.y + dstRect.h > worldDimensions.y)
	{
		dstRect.y = worldDimensions.y - dstRect.y;
	}
	*/

	// Make final destination relative to camera
	SDL_Rect camera = Engine::instance().getCamera();
	dstRect.x -= camera.x;
	dstRect.y -= camera.y;
}