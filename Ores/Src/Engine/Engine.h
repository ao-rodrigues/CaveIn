#pragma once

#include <SDL.h>
#include "ECS/ECS.h"

class Engine
{
public:
	Engine();
	~Engine();

	void init(const char* title, int width, int height, bool fullscreen, bool vsync);
	void quit();
	void clear();

	void handleEvents();
	void update();
	void render();

	Entity& createEntity();

	inline static Engine& instance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new Engine();
		}

		return *s_instance;
	}

	inline bool isRunning()
	{
		return _isRunning;
	}

	inline SDL_Renderer* getRenderer()
	{
		return _renderer;
	}

	float deltaTime = 1.f;

private:
	bool _isRunning = false;
	int _lastFrameTime = 0;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	EntityManager* _entityManager = nullptr;
	static Engine* s_instance;
};