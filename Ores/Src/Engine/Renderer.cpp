#include "Renderer.h"

void Renderer::init(SDL_Window* window, int flags)
{
	_renderer = SDL_CreateRenderer(window, -1, flags);

	if (!_renderer)
	{
		std::cerr << SDL_GetError() << std::endl;
	}

	
	_sortedRenderables.reserve(Sprite::RenderLayer::Count);
	for (std::size_t i = 0; i < Sprite::RenderLayer::Count; i++)
	{
		_sortedRenderables.emplace_back(std::multiset<Sprite*, RenderableComparator>());
	}
}

void Renderer::destroy()
{
	_sortedRenderables.clear();
	SDL_DestroyRenderer(_renderer);
}

void Renderer::render(std::vector<Entity*> renderables)
{
	for (auto& entity : renderables)
	{
		Sprite& renderable = entity->getComponent<Sprite>();
		_sortedRenderables[renderable.renderLayer].emplace(&renderable);
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);
	
	for (auto& layer : _sortedRenderables)
	{
		for (auto& renderable : layer)
		{
			SDL_RenderCopyEx(_renderer, renderable->texture, &renderable->srcRect, &renderable->dstRect, renderable->transform->rotation, nullptr, renderable->flip);
		}

		layer.clear();
	}

	SDL_RenderPresent(_renderer);
}
