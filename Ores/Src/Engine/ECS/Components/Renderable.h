#pragma once

#include <SDL.h>
#include "../ECS.h"
#include "Transform.h"
#include "../../RenderLayer.h"

class Renderable : public Component
{
public:
	Renderable(RenderLayer renderLayer, int depth, float relativePosX = 0.f, float relativePosY = 0.f)
		: renderLayer(renderLayer)
		, depth(depth)
		, _relativePosX(relativePosX)
		, _relativePosY(relativePosY)
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

	/// <summary>
	/// Get the position offset relative to the Transform.
	/// </summary>
	/// <returns>Position offset relative to Transform</returns>
	inline Vector2 getRelativePosition() { return Vector2(_relativePosX, _relativePosY); }

	/// <summary>
	/// Set the position offset relative to the Transform.
	/// </summary>
	/// <param name="relativePosition">New position offset</param>
	inline void setRelativePosition(Vector2 relativePosition)
	{
		_relativePosX = relativePosition.x;
		_relativePosY = relativePosition.y;
	}

	void makeDstRelativeToCamera();
	
	inline SDL_Texture* getTexture() { return texture; }
	inline RenderLayer getRenderLayer() const { return renderLayer; }
	inline SDL_RendererFlip getFlip() { return flip; }
	inline int getDepth() const { return depth; }
	inline bool isVisible() const { return visible; }
	inline Transform& getTransform() { return *transform; }

protected:
	SDL_Rect _srcRect = { 0, 0, 0, 0 };
	SDL_Rect _dstRect = { 0, 0, 0, 0 };

	float _relativePosX = 0.f;
	float _relativePosY = 0.f;

	SDL_Texture* texture = nullptr;
	RenderLayer renderLayer = RenderLayer::Background;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int depth = 0;
	bool visible = true;
	Transform* transform = nullptr;
};