#pragma once

#include <SDL.h>
#include "../ECS.h"
#include "Sprite.h"

class Animation : public Component
{
public:
	struct AnimationInfo
	{
		AnimationInfo(const std::string& name, const std::string& textureID, unsigned int numFrames, unsigned int frameDelay, bool loop, unsigned int rowIndex)
			: name(name)
			, textureID(textureID)
			, numFrames(numFrames)
			, frameDelay(frameDelay)
			, loop(loop)
			, rowIndex(rowIndex)
		{ }

		std::string name;
		std::string textureID;
		unsigned int numFrames = 1;
		unsigned int frameDelay = 0;
		bool loop = true;
		unsigned int rowIndex = 0;
	};

	Animation(const std::string& textureID, unsigned int numFrames, unsigned int frameDelay, bool loop = true, unsigned int rowIndex = 0)
	{
		AnimationInfo animation(currentAnimation, textureID, numFrames, frameDelay, loop, rowIndex);
		animations.emplace(currentAnimation, animation);
	}

	Animation(const std::vector<AnimationInfo>& animations)
	{
		for (auto& anim : animations)
		{
			this->animations.emplace(anim.name, anim);
		}

		currentAnimation = animations[0].name;
	}

	~Animation()
	{

	}

	void init() override;

	void addAnimation(AnimationInfo animation)
	{
		animations.emplace(animation.name, animation);
	}

	void setAnimation(const std::string& animation)
	{
		if (animations.count(animation))
		{
			currentAnimation = animation;
			AnimationInfo animInfo = animations.at(currentAnimation);
			sprite->setTexture(animInfo.textureID, animInfo.rowIndex);
			reset();
		}
	}

	inline AnimationInfo getCurrentAnimation()
	{
		return animations.at(currentAnimation);
	}

	void reset()
	{
		currentFrame = 0;
	}

	std::unordered_map<std::string, AnimationInfo> animations;
	std::string currentAnimation = "Default";
	unsigned int currentFrame = 0;
	Sprite* sprite = nullptr;
};

