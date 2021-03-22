#pragma once

#include <SDL.h>
#include <vector>
#include "Renderable.h"
#include "../../AssetManager.h"
#include "../../RenderLayer.h"


class Sprite : public Renderable
{
public:
	Sprite(RenderLayer renderLayer, int depth, const std::string& textureID, int srcX, int srcY, int width, int height, float relativePosX = 0.f, float relativePosY = 0.f)
		: Renderable(renderLayer, depth, relativePosX, relativePosY)
		, textureID(textureID)
		, srcX(srcX)
		, srcY(srcY)
		, srcWidth(width)
		, srcHeight(height)
		, dstWidth(width)
		, dstHeight(height)
	{
	}

	Sprite(RenderLayer renderLayer, int depth, const std::string& textureID, int srcX, int srcY, int srcWidth, int srcHeight, int dstWidth, int dstHeight, float relativePosX, float relativePosY)
		: Renderable(renderLayer, depth, relativePosX, relativePosY)
		, textureID(textureID)
		, srcX(srcX)
		, srcY(srcY)
		, srcWidth(srcWidth)
		, srcHeight(srcHeight)
		, dstWidth(dstWidth)
		, dstHeight(dstHeight)
	{ }

	~Sprite()
	{
		
	}

	void init() override;

	virtual SDL_Rect* srcRect() override
	{
		return &_srcRect;
	}

	inline void setSrcDimensions(int w, int h)
	{
		_srcRect.w = w;
		_srcRect.h = h;
	}

	virtual SDL_Rect* dstRect() override
	{
		return &_dstRect;
	}

	inline void setTexture(const std::string& newTextureID)
	{
		textureID = newTextureID;
		texture = AssetManager::instance().getTexture(textureID);
	}

	inline void setTexture(const std::string& newTextureID, int rowIndex)
	{
		setTexture(newTextureID);
		_srcRect.y = rowIndex * dstHeight;
	}

	inline void setVisible(bool visible)
	{
		this->visible = visible;
	}

	int srcX = 0;
	int srcY = 0;

	int srcWidth = 0;
	int srcHeight = 0;

	int dstWidth = 0;
	int dstHeight = 0;

	std::string textureID = "";
};