#pragma once

#include <SDL.h>
#include <set>
#include <vector>

#include "../ECS.h"
#include "../Components/Renderable.h"

class RenderSystem : public System
{
public:
	using System::System;

	void init() override;
	void init(SDL_Window* window, int flags);

	virtual void update() override;

	inline SDL_Renderer* SDLRenderer() { return _renderer; }

	void destroy();

private:
	struct RenderableComparator
	{
		bool operator()(const Renderable* r1, const Renderable* r2) const
		{
			return r1->depth < r2->depth;
		}
	};

	std::vector<std::multiset<Renderable*, RenderableComparator>> _sortedRenderables;
	SDL_Renderer* _renderer;
};