#include "RenderSystem.h"

#include <iostream>
#include "../Components/Sprite.h"
#include "../Components/Text.h"


void RenderSystem::init()
{
	_sortedRenderables.reserve(RenderLayer::Count);
	for (std::size_t i = 0; i < RenderLayer::Count; i++)
	{
		_sortedRenderables.emplace_back(std::multiset<Renderable*, RenderableComparator>());
	}
}

void RenderSystem::init(SDL_Window* window, int flags)
{
	_renderer = SDL_CreateRenderer(window, -1, flags);

	if (!_renderer)
	{
		std::cerr << SDL_GetError() << std::endl;
	}
}

void RenderSystem::update()
{
	auto renderableEntities = _entityManager->getEntitiesWithComponent<Sprite, Text>();
	for (auto& entity : renderableEntities)
	{
		if (entity->hasComponent<Sprite>())
		{
			Sprite& sprite = entity->getComponent<Sprite>();
			_sortedRenderables[sprite.renderLayer].emplace(&sprite);
		}
		else if (entity->hasComponent<Text>())
		{
			Text& text = entity->getComponent<Text>();
			_sortedRenderables[text.renderLayer].emplace(&text);
		}
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

	for (auto& layer : _sortedRenderables)
	{
		for (auto& renderable : layer)
		{
			if (renderable->visible)
			{
				SDL_RenderCopyEx(_renderer, renderable->texture, renderable->srcRect(), renderable->dstRect(), renderable->transform->rotation, nullptr, renderable->flip);
			}
		}

		layer.clear();
	}

	SDL_RenderPresent(_renderer);
}

void RenderSystem::destroy()
{
	_sortedRenderables.clear();
	SDL_DestroyRenderer(_renderer);
}