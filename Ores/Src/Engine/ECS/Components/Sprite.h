#pragma once

#include <SDL.h>
#include "Transform.h"
#include "../../AssetManager.h"
//#include "../../Renderer.h"
class Renderer;

class Sprite : public Component
{
public:
	enum RenderLayer
	{
		Background,
		Foreground,
		UI,

		Count
	};

	Sprite(Renderer* renderTarget, RenderLayer renderLayer, int depth, std::string textureID, int width, int height)
		: _renderTarget(renderTarget)
		, renderLayer(renderLayer)
		, depth(depth)
		, textureID(textureID)
		, width(width)
		, height(height)
	{
	}

	Sprite(Renderer* renderTarget, RenderLayer renderLayer, int depth, std::string textureID, int width, int height, int numFrames, int frameDelay, int rowIndex)
		: _renderTarget(renderTarget)
		, renderLayer(renderLayer)
		, depth(depth)
		, textureID(textureID)
		, width(width)
		, height(height)
		, animated(true)
		, numFrames(numFrames)
		, frameDelay(frameDelay)
		, rowIndex(rowIndex)
	{
	}

	void init() override;

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / frameDelay) % numFrames);
		}

		dstRect.x = static_cast<int>(transform->position.x);
		dstRect.y = static_cast<int>(transform->position.y);
		dstRect.w = static_cast<int>(width * transform->scale.x);
		dstRect.h = static_cast<int>(height * transform->scale.y);
	}

	/*
	void render()
	{
		SDL_RenderCopyEx(_renderTarget, texture, &srcRect, &dstRect, transform->rotation, nullptr, flip);
	}
	*/
	


	int width = 0;
	int height = 0;
	SDL_Rect srcRect = { 0, 0, 0, 0 };
	SDL_Rect dstRect = { 0, 0, 0, 0 };

	int depth = 0;

	bool animated = false;
	int rowIndex = 0;
	int numFrames = 1;
	int frameDelay = 100;

	std::string textureID = "";
	SDL_Texture* texture = nullptr;

	//Renderer::RenderLayer renderLayer = Renderer::RenderLayer::Background;

	RenderLayer renderLayer = RenderLayer::Background;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	Transform* transform = nullptr;

private:
	//Renderer* _renderer;
	Renderer* _renderTarget;
};