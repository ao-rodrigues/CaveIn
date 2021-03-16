#include "SpriteSystem.h"

#include "../Components/Sprite.h"

void SpriteSystem::update()
{
	for (auto& spriteEntity : _entityManager->getEntitiesWithComponent<Sprite>())
	{
		Sprite& sprite = spriteEntity->getComponent<Sprite>();

		sprite.dstRect.x = static_cast<int>(sprite.transform->position.x);
		sprite.dstRect.y = static_cast<int>(sprite.transform->position.y);
		sprite.dstRect.w = static_cast<int>(sprite.width * sprite.transform->scale.x);
		sprite.dstRect.h = static_cast<int>(sprite.height * sprite.transform->scale.y);

		sprite.makeDstRelativeToCamera();
	}
}