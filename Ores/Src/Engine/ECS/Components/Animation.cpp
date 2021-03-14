#include "Animation.h"
#include "../../Engine.h"

void Animation::init()
{
	sprite = &entity->getComponent<Sprite>();
	AnimationInfo animInfo = animations.at(currentAnimation);
	sprite->setTexture(animInfo.textureID, animInfo.rowIndex);
}

void Animation::update()
{
	AnimationInfo animInfo = animations.at(currentAnimation);

	sprite->srcRect.x = sprite->srcRect.w * static_cast<int>((SDL_GetTicks() / animInfo.frameDelay) % animInfo.numFrames);
}