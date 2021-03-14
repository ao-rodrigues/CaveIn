#pragma once

#include <SDL.h>
#include "../ECS.h"
#include "Sprite.h"

class Animation : public Component
{
public:
	struct AnimationInfo
	{
		AnimationInfo(std::string name, std::string textureID, int numFrames, int frameDelay, int rowIndex)
			: name(name)
			, textureID(textureID)
			, numFrames(numFrames)
			, frameDelay(frameDelay)
			, rowIndex(rowIndex)
		{ }

		std::string name;
		std::string textureID;
		int numFrames = 1;
		int frameDelay = 0;
		int rowIndex = 0;
	};

	Animation(std::string textureID, int numFrames, int frameDelay, int rowIndex = 0)
	{
		AnimationInfo animation(currentAnimation, textureID, numFrames, frameDelay, rowIndex);
		animations.emplace(currentAnimation, animation);
	}

	Animation(std::vector<AnimationInfo> animations)
	{
		for (auto& anim : animations)
		{
			this->animations.emplace(anim.name, anim);
		}

		currentAnimation = animations[0].name;
	}

	void init() override;
	void update() override;

	void setAnimation(std::string animation)
	{
		if (animations.count(animation))
		{
			currentAnimation = animation;
			AnimationInfo animInfo = animations.at(currentAnimation);
			sprite->setTexture(animInfo.textureID, animInfo.rowIndex);
			
		}
	}

	std::unordered_map<std::string, AnimationInfo> animations;
	std::string currentAnimation = "Default";
	Sprite* sprite = nullptr;
};

