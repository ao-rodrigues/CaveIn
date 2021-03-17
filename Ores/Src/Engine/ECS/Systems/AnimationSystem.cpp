#include "AnimationSystem.h"

#include "../Components/Animation.h"

void AnimationSystem::update()
{
	for (auto& animEntity : _entityManager->getEntitiesWithComponent<Animation>())
	{
		Animation& animation = animEntity->getComponent<Animation>();
		Animation::AnimationInfo animInfo = animation.animations.at(animation.currentAnimation);

		animation.sprite->srcRect()->x = animation.sprite->srcRect()->w * static_cast<int>((SDL_GetTicks() / animInfo.frameDelay) % animInfo.numFrames);
	}
}