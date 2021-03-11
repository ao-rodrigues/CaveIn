#pragma once

#include <SDL.h>
#include "Transform.h"
#include "../../AssetManager.h"
//#include "../../Renderer.h"

class Sprite : public Component
{
public:
	Sprite(SDL_Renderer* renderTarget, int depth, std::string textureID, int width, int height)
		: _renderTarget(renderTarget)
		//, renderLayer(renderLayer)
		, depth(depth)
		, textureID(textureID)
		, width(width)
		, height(height)
	{
	}

	Sprite(SDL_Renderer* renderTarget, int depth, std::string textureID, int width, int height, int numFrames, int frameDelay, int rowIndex)
		: _renderTarget(renderTarget)
		//, renderLayer(renderLayer)
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

	void init() override
	{
		transform = &entity->getComponent<Transform>();
		texture = AssetManager::instance().getTexture(textureID);

		srcRect.x = 0;
		srcRect.y = rowIndex * height;;
		srcRect.w = width;
		srcRect.h = height;

		dstRect.x = static_cast<int>(transform->position.x);
		dstRect.y = static_cast<int>(transform->position.y);
		dstRect.w = static_cast<int>(width * transform->scale.x);
		dstRect.h = static_cast<int>(height * transform->scale.y);

		//_renderer->addRenderable(this, renderLayer, depth);
	}

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

	
	void render()
	{
		SDL_RenderCopyEx(_renderTarget, texture, &srcRect, &dstRect, transform->rotation, nullptr, flip);
	}
	


private:
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
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	Transform* transform = nullptr;

	//Renderer* _renderer;
	SDL_Renderer* _renderTarget;
};