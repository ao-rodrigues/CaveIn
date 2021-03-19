#include "RenderSystem.h"

#include <iostream>
#include "../Components/Sprite.h"
#include "../Components/Text.h"

#include "../../InputManager.h"


void RenderSystem::init()
{
	/*
	_sortedRenderables.reserve(RenderLayer::Count);
	for (std::size_t i = 0; i < RenderLayer::Count; i++)
	{
		_sortedRenderables.emplace_back(std::multiset<Renderable*, RenderableComparator>());
	}
	*/

	//_sortedRenderables(RenderLayer::Count, std::vector<Renderable*>(100));
	_sortedRenderables.reserve(RenderLayer::Count);
	for (int i = 0; i < RenderLayer::Count; i++)
	{
		_sortedRenderables.emplace_back(std::vector<Renderable*>());
		_sortedRenderables[i].reserve(100);
	}
}

void RenderSystem::init(SDL_Window* window, int flags)
{
	_renderer = SDL_CreateRenderer(window, -1, flags);

	if (!_renderer)
	{
		std::cerr << SDL_GetError() << std::endl;
	}

	AssetManager::instance().loadTexture("Cursor", "Assets/Textures/pointer.png");

	SDL_ShowCursor(0);
	_cursorTexture = AssetManager::instance().getTexture("Cursor");
}

void RenderSystem::update()
{
	auto renderableEntities = _entityManager->getEntitiesWithComponentAny<Sprite, Text>();
	for (auto& entity : renderableEntities)
	{
		if (entity->hasComponent<Sprite>())
		{
			Sprite& sprite = entity->getComponent<Sprite>();
			_sortedRenderables[sprite.renderLayer].emplace_back(&sprite);
		}
		else if (entity->hasComponent<Text>())
		{
			Text& text = entity->getComponent<Text>();
			_sortedRenderables[text.renderLayer].emplace_back(&text);
		}
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

	for (auto& layer : _sortedRenderables)
	{
		std::sort(layer.begin(), layer.end(), 
			[](const Renderable* r1, const Renderable* r2)
			{
				return r1->depth < r2->depth;
			}
		);

		for (auto& renderable : layer)
		{
			if (renderable->visible)
			{
				SDL_RenderCopyEx(_renderer, renderable->texture, renderable->srcRect(), renderable->dstRect(), renderable->transform->rotation, nullptr, renderable->flip);
			}
		}

		layer.clear();
	}

	Vector2 mousePos = InputManager::mousePosition();
	SDL_Rect cursorDstRect = { mousePos.x, mousePos.y, _cursorSrcRect.w, _cursorSrcRect.h };
	SDL_RenderCopy(_renderer, _cursorTexture, &_cursorSrcRect, &cursorDstRect);

	SDL_RenderPresent(_renderer);
}

void RenderSystem::destroy()
{
	_sortedRenderables.clear();
	SDL_DestroyRenderer(_renderer);
}