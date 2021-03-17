#pragma once

#include <SDL.h>
#include <vector>
#include "Renderable.h"
#include "../../AssetManager.h"
#include "../../RenderLayer.h"


class Sprite : public Renderable
{
public:
	Sprite(RenderLayer renderLayer, int depth, const std::string& textureID, int width, int height)
		: Renderable(renderLayer, depth)
		, textureID(textureID)
		, width(width)
		, height(height)
	{
	}

	void init() override;

	virtual SDL_Rect* srcRect() override
	{
		return &_srcRect;
	}

	virtual SDL_Rect* dstRect() override
	{
		return &_dstRect;
	}

	inline void setTexture(const std::string& newTextureID, int rowIndex)
	{
		textureID = newTextureID;
		texture = AssetManager::instance().getTexture(textureID);
		_srcRect.y = rowIndex * height;
	}

	inline void setVisible(bool visible)
	{
		this->visible = visible;
	}

	void makeDstRelativeToCamera();

	int width = 0;
	int height = 0;

	std::string textureID = "";
};