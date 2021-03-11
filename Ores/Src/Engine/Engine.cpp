#include <iostream>
#include "Engine.h"
#include "InputManager.h"
#include "ECS/Components/Transform.h"

Engine::Engine()
{
	_isRunning = false;
	_window = nullptr;
	_renderer = nullptr;
	_entityManager = nullptr;
}

Engine::~Engine()
{
	delete _renderer;
	delete _entityManager;
}

void Engine::init(const char* title, int width, int height, bool fullscreen, bool vsync)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << SDL_GetError() << std::endl;
	}

	auto windowFlags = fullscreen ? SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);

	if (!_window)
	{
		std::cerr << SDL_GetError() << std::endl;
	}

	
	auto rendererFlags = vsync ? (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED) : SDL_RENDERER_ACCELERATED;
	_renderer = SDL_CreateRenderer(_window, -1, rendererFlags);

	if (!_renderer)
	{
		std::cerr << SDL_GetError() << std::endl;
	}
	

	//_renderer = new Renderer();

	//_renderer->init(_window, rendererFlags);

	_entityManager = new EntityManager();

	_isRunning = true;
}

void Engine::quit()
{
	_isRunning = false;
}

void Engine::clear()
{
	SDL_DestroyRenderer(_renderer);
	//_renderer->destroy();
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Engine::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quit();
			return;
		}

		InputManager::handleEvent(event);
	}
}

void Engine::update()
{
	_entityManager->refresh();
	_entityManager->update();

	InputManager::clearEvents();
}

void Engine::render()
{
	deltaTime = (SDL_GetTicks() - _lastFrameTime) / 1000.f;

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

	_entityManager->render();

	SDL_RenderPresent(_renderer);
	//_renderer->render();

	_lastFrameTime = SDL_GetTicks();
}

Entity& Engine::createEntity()
{
	Entity& newEntity = _entityManager->createEntity();
	newEntity.addComponent<Transform>();

	return newEntity;
}
