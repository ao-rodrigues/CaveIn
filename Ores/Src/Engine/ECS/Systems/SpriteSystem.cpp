#include "SpriteSystem.h"

#include "../Components/Sprite.h"

void SpriteSystem::update()
{
	auto spriteEntities = _entityManager->getEntitiesWithComponentAll<Sprite>();
	for (auto& spriteEntity : spriteEntities)
	{
		Sprite& sprite = spriteEntity->getComponent<Sprite>();

		sprite.srcRect()->w = sprite.srcWidth;
		sprite.srcRect()->h = sprite.srcHeight;

		sprite.dstRect()->x = static_cast<int>(sprite.transform->position.x + sprite.getRelativePosition().x * sprite.transform->scale.x);
		sprite.dstRect()->y = static_cast<int>(sprite.transform->position.y + sprite.getRelativePosition().y * sprite.transform->scale.y);
		sprite.dstRect()->w = static_cast<int>(sprite.dstWidth * sprite.transform->scale.x);
		sprite.dstRect()->h = static_cast<int>(sprite.dstHeight * sprite.transform->scale.y);

		sprite.makeDstRelativeToCamera();
	}
}