#include "Renderer.h"

void Renderer::init(SDL_Window* window, int flags)
{
	_renderer = SDL_CreateRenderer(window, -1, flags);

	if (!_renderer)
	{
		std::cerr << SDL_GetError() << std::endl;
	}

	//_renderables.reserve(Sprite::RenderLayer::Count);
	for (std::size_t i = 0; i < Sprite::RenderLayer::Count; i++)
	{
		_renderables.emplace_back(std::multiset<Sprite*, RenderableComparator>());
	}
}

void Renderer::destroy()
{
	_renderables.clear();
	SDL_DestroyRenderer(_renderer);
}

void Renderer::addRenderable(Sprite* renderable)
{
	_renderables[renderable->renderLayer].emplace(renderable);
}

void Renderer::render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

	for (auto& layer : _renderables)
	{
		for (auto& renderable : layer)
		{
			SDL_RenderCopyEx(_renderer, renderable->texture, &renderable->srcRect, &renderable->dstRect, renderable->transform->rotation, nullptr, renderable->flip);
		}
	}

	SDL_RenderPresent(_renderer);
}
