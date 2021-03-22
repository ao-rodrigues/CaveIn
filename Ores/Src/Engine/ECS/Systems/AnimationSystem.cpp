#include "AnimationSystem.h"

#include "../Components/Animation.h"

void AnimationSystem::update()
{
	for (auto& animEntity : _entityManager->getEntitiesWithComponentAll<Animation>())
	{
		Animation& animation = animEntity->getComponent<Animation>();
		Animation::AnimationInfo animInfo = animation.getCurrentAnimation();

		if (!animInfo.loop && (animation.currentFrame == animInfo.numFrames - 1)) continue;

		int nextFrame = static_cast<int>((SDL_GetTicks() / animInfo.frameDelay) % animInfo.numFrames);
		animation.sprite->srcRect()->x = animation.sprite->srcRect()->w * nextFrame;
		animation.currentFrame = nextFrame;

		if (animInfo.loop && animation.currentFrame == animInfo.numFrames - 1)
		{
			animation.reset();
		}
	}
}