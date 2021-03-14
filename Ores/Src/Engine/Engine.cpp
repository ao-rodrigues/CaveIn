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

void Engine::init(const char* title, int width, int height, bool fullscreen, bool vsync, int worldWidth, int worldHeight)
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

	_camera.x = 0;
	_camera.y = 0;
	_camera.w = width;
	_camera.h = height;

	_worldDimensions.x = worldWidth;
	_worldDimensions.y = worldHeight;

	_renderer = new Renderer();
	auto rendererFlags = vsync ? (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED) : SDL_RENDERER_ACCELERATED;
	_renderer->init(_window, rendererFlags);

	_entityManager = new EntityManager();

	_isRunning = true;
}

void Engine::quit()
{
	_isRunning = false;
}

void Engine::clear()
{
	_renderer->destroy();
	InputManager::clearEvents();
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
	_entityManager->update();
	_entityManager->refresh();
	InputManager::clearFrameEvents();
}

void Engine::render()
{
	deltaTime = (SDL_GetTicks() - _lastFrameTime) / 1000.f;
	_lastFrameTime = SDL_GetTicks();
	int fps = _frameCount / (_lastFrameTime / 1000.f);
	std::cout << "FPS: " << fps << std::endl;


	std::vector<Entity*> renderables = _entityManager->getEntitiesWithComponent<Sprite>();

	_renderer->render(renderables);
	_frameCount++;
}

Entity& Engine::createEntity()
{
	Entity& newEntity = _entityManager->createEntity();
	newEntity.addComponent<Transform>();

	return newEntity;
}
