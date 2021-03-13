#include "Sprite.h"
#include "../../Renderer.h"

void Sprite::init()
{
	transform = &entity->getComponent<Transform>();
	texture = AssetManager::instance().getTexture(textureID);

	srcRect.x = 0;
	srcRect.y = rowIndex * height;;
	srcRect.w = width;
	srcRect.h = height;

	dstRect.x = static_cast<int>(transform->position.x);
	dstRect.y = static_cast<int>(transform->position.y);
	dstRect.w = static_cast<int>(width * transform->scale.x);
	dstRect.h = static_cast<int>(height * transform->scale.y);

	//_renderTarget->addRenderable(this);
}