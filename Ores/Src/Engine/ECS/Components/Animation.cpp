#include "Animation.h"
#include "../../Engine.h"

void Animation::init()
{
	sprite = &entity->getComponent<Sprite>();
	AnimationInfo animInfo = animations.at(currentAnimation);
	sprite->setTexture(animInfo.textureID, animInfo.rowIndex);
}