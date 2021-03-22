#include "TextSystem.h"
#include <stdlib.h>

#include "../Components/Text.h"

void TextSystem::update()
{
	for (auto& textEntity : _entityManager->getEntitiesWithComponentAll<Text>())
	{
		Text& text = textEntity->getComponent<Text>();
		text.dstRect()->x = static_cast<int>(std::round(text.transform->position.x + text.getRelativePosition().x * text.transform->scale.x));
		text.dstRect()->y = static_cast<int>(std::round(text.transform->position.y + text.getRelativePosition().y * text.transform->scale.y));
		text.makeDstRelativeToCamera();
	}
}