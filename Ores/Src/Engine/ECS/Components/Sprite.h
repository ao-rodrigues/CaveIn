#pragma once

#include <SDL.h>
#include <vector>
#include "Transform.h"
#include "../../AssetManager.h"


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

	Sprite(RenderLayer renderLayer, int depth, const std::string& textureID, int width, int height)
		: renderLayer(renderLayer)
		, depth(depth)
		, textureID(textureID)
		, width(width)
		, height(height)
	{
	}

	void init() override;

	/*
	void update() override
	{
		dstRect.x = static_cast<int>(transform->position.x);
		dstRect.y = static_cast<int>(transform->position.y);
		dstRect.w = static_cast<int>(width * transform->scale.x);
		dstRect.h = static_cast<int>(height * transform->scale.y);

		makeDstRelativeToCamera();
	}
	*/

	inline void setTexture(const std::string& newTextureID, int rowIndex)
	{
		textureID = newTextureID;
		texture = AssetManager::instance().getTexture(textureID);
		srcRect.y = rowIndex * height;
	}

	inline void setVisible(bool visible)
	{
		this->visible = visible;
	}

	void makeDstRelativeToCamera();

	int width = 0;
	int height = 0;
	SDL_Rect srcRect = { 0, 0, 0, 0 };
	SDL_Rect dstRect = { 0, 0, 0, 0 };

	int depth = 0;
	bool visible = true;

	std::string textureID = "";
	SDL_Texture* texture = nullptr;

	RenderLayer renderLayer = RenderLayer::Background;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	Transform* transform = nullptr;

private:
};