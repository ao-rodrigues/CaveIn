#pragma once

#include <SDL.h>
#include "Transform.h"
#include "../AssetManager.h"

class Sprite : public Component
{
public:
	Sprite() = default;
	virtual ~Sprite() = default;

	Sprite(SDL_Renderer* renderTarget, std::string textureID, int width, int height) 
		: _renderTarget(renderTarget)
		, _textureID(textureID)
		, _width(width)
		, _height(height)
	{
	}

	Sprite(SDL_Renderer* renderTarget, std::string textureID, int width, int height, int numFrames, int frameDelay, int rowIndex)
		: _renderTarget(renderTarget)
		, _textureID(textureID)
		, _width(width)
		, _height(height)
		, _animated(true)
		, _numFrames(numFrames)
		, _frameDelay(frameDelay)
		, _rowIndex(rowIndex)
	{
	}

	void init() override
	{
		_transform = &entity->getComponent<Transform>();
		_texture = AssetManager::instance()->getTexture(_textureID);

		_srcRect.x = 0;
		_srcRect.y = _rowIndex * _height;;
		_srcRect.w = _width;
		_srcRect.h = _height;

		_dstRect.x = static_cast<int>(_transform->position.x);
		_dstRect.y = static_cast<int>(_transform->position.y);
		_dstRect.w = static_cast<int>(_width * _transform->scale.x);
		_dstRect.h = static_cast<int>(_height * _transform->scale.y);
	}

	void update() override
	{
		if (_animated)
		{
			_srcRect.x = _srcRect.w * static_cast<int>((SDL_GetTicks() / _frameDelay) % _numFrames);
		}

		_dstRect.x = static_cast<int>(_transform->position.x);
		_dstRect.y = static_cast<int>(_transform->position.y);
		_dstRect.w = static_cast<int>(_width * _transform->scale.x);
		_dstRect.h = static_cast<int>(_height * _transform->scale.y);
	}

	
	void render() override
	{
		SDL_RenderCopyEx(_renderTarget, _texture, &_srcRect, &_dstRect, _transform->rotation, nullptr, _flip);
	}

private:

	int _width = 0;
	int _height = 0;
	SDL_Rect _srcRect = { 0, 0, 0, 0 };
	SDL_Rect _dstRect = { 0, 0, 0, 0 };

	bool _animated = false;
	int _rowIndex = 0;
	int _numFrames = 1;
	int _frameDelay = 100;

	Transform* _transform = nullptr;
	std::string _textureID = "";
	SDL_Texture* _texture = nullptr;
	SDL_Renderer* _renderTarget = nullptr;
	SDL_RendererFlip _flip = SDL_FLIP_NONE;
};