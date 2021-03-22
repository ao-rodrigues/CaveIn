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
		, _textureID(textureID)
		, _srcX(srcX)
		, _srcY(srcY)
		, _srcWidth(width)
		, _srcHeight(height)
		, _dstWidth(width)
		, _dstHeight(height)
	{
	}

	Sprite(RenderLayer renderLayer, int depth, const std::string& textureID, int srcX, int srcY, int srcWidth, int srcHeight, int dstWidth, int dstHeight, float relativePosX, float relativePosY)
		: Renderable(renderLayer, depth, relativePosX, relativePosY)
		, _textureID(textureID)
		, _srcX(srcX)
		, _srcY(srcY)
		, _srcWidth(srcWidth)
		, _srcHeight(srcHeight)
		, _dstWidth(dstWidth)
		, _dstHeight(dstHeight)
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
		_textureID = newTextureID;
		texture = AssetManager::instance().getTexture(_textureID);
	}

	inline void setTexture(const std::string& newTextureID, int rowIndex)
	{
		setTexture(newTextureID);
		_srcRect.y = rowIndex * _dstHeight;
	}

	inline const std::string& getTextureID() const { return _textureID; }

	inline void setVisible(bool visible)
	{
		this->visible = visible;
	}

	inline int getSrcX() const { return _srcX; }
	inline void setSrcX(int newSrcX) { _srcX = newSrcX; }

	inline int getSrcY() const { return _srcY; }
	inline void setSrcY(int newSrcY) { _srcY = newSrcY; }

	inline int getSrcWidth() const { return _srcWidth; }
	inline void setSrcWidth(int newSrcWidth) { _srcWidth = newSrcWidth; }

	inline int getSrcHeight() const { return _srcHeight; }
	inline void setSrcHeight(int newSrcHeight) { _srcHeight = newSrcHeight; }

	inline int getDstWidth() const { return _dstWidth; }
	inline void setDstWidth(int newDstWidth) { _dstWidth = newDstWidth; }

	inline int getDstHeight() const { return _dstHeight; }
	inline void setDstHeight(int newDstHeight) { _dstHeight = newDstHeight; }

private:
	int _srcX = 0;
	int _srcY = 0;

	int _srcWidth = 0;
	int _srcHeight = 0;

	int _dstWidth = 0;
	int _dstHeight = 0;

	std::string _textureID = "";
};