#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Renderable.h"
#include "../../Engine.h"
#include "../../AssetManager.h"


class Text : public Renderable
{
public:
	Text(std::string fontID, int xPos, int yPos, int depth, std::string text, SDL_Color& color)
		: Renderable(RenderLayer::UI, depth)
		, fontID(std::move(fontID))
		, text(std::move(text))
		, textColor(color)
	{
		_dstRect.x = xPos;
		_dstRect.y = yPos;
		setText(this->fontID, this->text);
	}

	~Text()
	{ }

	void setText(const std::string& fontID, const std::string& text)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(AssetManager::instance().getFont(fontID), text.c_str(), textColor);
		texture = SDL_CreateTextureFromSurface(Engine::instance().getRenderer(), surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(texture, nullptr, nullptr, &_dstRect.w, &_dstRect.h);
	}

	virtual SDL_Rect* srcRect() override
	{
		return nullptr;
	}

	virtual SDL_Rect* dstRect() override
	{
		return &_dstRect;
	}

	std::string fontID;
	std::string text;
	SDL_Color textColor;
};