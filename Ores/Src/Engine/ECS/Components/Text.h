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
	Text(const std::string& fontID, int depth, const std::string& text, SDL_Color color, unsigned int wrapLength, float relativePosX = 0.f, float relativePosY = 0.f)
		: Renderable(RenderLayer::UI, depth, relativePosX, relativePosY)
		, fontID(fontID)
		, text(text)
		, textColor(color)
		, wrapLength(wrapLength)
	{
		setText(this->fontID, this->text);
	}

	void init() override
	{
		transform = &entity->getComponent<Transform>();
		_dstRect.x = transform->position.x + _relativePosX;
		_dstRect.y = transform->position.y + _relativePosY;
		makeDstRelativeToCamera();
	}

	~Text()
	{ 
		if (texture != nullptr)
		{
			SDL_DestroyTexture(texture);
		}
	}

	void setText(std::string fontID, std::string text)
	{
		this->fontID = fontID;
		this->text = text;

		if (texture != nullptr)
		{
			SDL_DestroyTexture(texture);
		}

		SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(AssetManager::instance().getFont(fontID), text.c_str(), textColor, wrapLength);
		texture = SDL_CreateTextureFromSurface(Engine::instance().getRenderer(), surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(texture, nullptr, nullptr, &_dstRect.w, &_dstRect.h);
	}

	void setTextColor(SDL_Color newColor)
	{
		if (texture != nullptr)
		{
			SDL_DestroyTexture(texture);
		}

		SDL_Surface* surf = TTF_RenderText_Blended(AssetManager::instance().getFont(fontID), text.c_str(), newColor);
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
	unsigned int wrapLength;
};