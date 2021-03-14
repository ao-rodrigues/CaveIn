#pragma once

#include <SDL.h>
#include "ECS/ECS.h"
#include "Singleton.h"
#include "Renderer.h"
#include "Math/Vector2.h"

class Engine : public Singleton<Engine>
{
public:

	Engine();
	~Engine();

	void init(const char* title, int width, int height, bool fullscreen, bool vsync, int worldWidth, int worldHeight);
	void quit();
	void clear();

	void handleEvents();
	void update();
	void render();

	Entity& createEntity();

	inline bool isRunning() { return _isRunning; }
	inline Renderer* getRenderer() { return _renderer; }
	inline SDL_Rect getCamera() { return _camera; }
	inline Vector2 getWorldDimensions() { return _worldDimensions; }

	float deltaTime = 1.f;

private:
	bool _isRunning = false;

	int _lastFrameTime = 0;
	int _frameCount = 0;

	SDL_Window* _window = nullptr;
	SDL_Rect _camera;
	Vector2 _worldDimensions;
	Renderer* _renderer = nullptr;
	EntityManager* _entityManager = nullptr;
};