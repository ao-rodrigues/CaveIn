#pragma once

#include <SDL.h>
#include <set>
#include <vector>
#include "ECS/Components/Sprite.h"

class Renderer
{
public:
	void init(SDL_Window* window, int flags);
	void destroy();

	void addRenderable(Sprite* renderable);
	void render();

	SDL_Renderer* SDLRenderer() { return _renderer; }

private:
	struct RenderableComparator
	{
		bool operator()(const Sprite* r1, const Sprite* r2) const
		{
			return r1->depth < r2->depth;
		}
	};

	std::vector<std::multiset<Sprite*, RenderableComparator>> _renderables;
	SDL_Renderer* _renderer;
};