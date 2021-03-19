#pragma once

#include <SDL.h>
#include "../ECS.h"
#include "Transform.h"
#include "../../RenderLayer.h"

class Renderable : public Component
{
public:
	Renderable(RenderLayer renderLayer, int depth)
		: renderLayer(renderLayer)
		, depth(depth)
	{}

	~Renderable()
	{

	}

	virtual void init() override 
	{
		transform = &entity->getComponent <Transform>();
	}

	virtual SDL_Rect* srcRect() = 0;
	virtual SDL_Rect* dstRect() = 0;
	
	SDL_Texture* texture = nullptr;
	RenderLayer renderLayer = RenderLayer::Background;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int depth = 0;
	bool visible = true;
	Transform* transform = nullptr;

protected:
	SDL_Rect _srcRect = { 0, 0, 0, 0 };
	SDL_Rect _dstRect = { 0, 0, 0, 0 };

};