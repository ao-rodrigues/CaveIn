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
		AnimationInfo animation(_currentAnimation, textureID, numFrames, frameDelay, loop, rowIndex);
		_animations.emplace(_currentAnimation, animation);
	}

	Animation(const std::vector<AnimationInfo>& animations)
	{
		for (auto& anim : animations)
		{
			_animations.emplace(anim.name, anim);
		}

		_currentAnimation = animations[0].name;
	}

	~Animation()
	{

	}

	void init() override;

	void addAnimation(AnimationInfo animation)
	{
		_animations.emplace(animation.name, animation);
	}

	void setAnimation(const std::string& animation)
	{
		if (_animations.count(animation))
		{
			_currentAnimation = animation;
			AnimationInfo animInfo = _animations.at(_currentAnimation);
			_sprite->setTexture(animInfo.textureID, animInfo.rowIndex);
			reset();
		}
	}

	inline AnimationInfo getCurrentAnimation()
	{
		return _animations.at(_currentAnimation);
	}

	void reset()
	{
		_currentFrame = 0;
	}

	inline const std::unordered_map<std::string, AnimationInfo>& getAnimations() { return _animations; }

	inline unsigned int getCurrentFrame() { return _currentFrame; }
	inline void setCurrentFrame(unsigned int nextFrame) { _currentFrame = nextFrame; }

	inline Sprite& getSprite() { return *_sprite; }

private:
	std::unordered_map<std::string, AnimationInfo> _animations;
	std::string _currentAnimation = "Default";
	unsigned int _currentFrame = 0;
	Sprite* _sprite = nullptr;
};

