#pragma once

#include <SDL.h>
#include <vector>
#include "Renderable.h"
#include "../../AssetManager.h"
#include "../../RenderLayer.h"


class Sprite : public Renderable
{
public:
	Sprite(RenderLayer renderLayer, int depth, const std::string& textureID, int srcX, int srcY, int width, int height)
		: Renderable(renderLayer, depth)
		, textureID(textureID)
		, srcX(srcX)
		, srcY(srcY)
		, srcWidth(width)
		, srcHeight(height)
		, dstWidth(width)
		, dstHeight(height)
	{
	}

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

	void makeDstRelativeToCamera();

	int srcX = 0;
	int srcY = 0;

	int srcWidth = 0;
	int srcHeight = 0;

	int dstWidth = 0;
	int dstHeight = 0;

	std::string textureID = "";
};