#include <iostream>
#include "Engine.h"
#include "AssetManager.h"
#include "ECS/Sprite.h"

Engine* Engine::s_instance = nullptr;

Engine::Engine()
{
	_isRunning = false;
	_window = nullptr;
	_renderer = nullptr;
	_entityManager = nullptr;
}

Engine::~Engine()
{
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

	_entityManager = new EntityManager();

	AssetManager::getInstance()->loadTexture("Characters", "Assets/Textures/characters.png");
	
	Entity& entity = _entityManager->createEntity();
	Transform& transform = entity.addComponent<Transform>();
	entity.addComponent<Sprite>(_renderer, "Characters", 32, 32, 4, 100, 1);

	transform.scale.x = 2.f;
	transform.scale.y = 2.f;

	_isRunning = true;
}

void Engine::quit()
{
	_isRunning = false;
}

void Engine::clear()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Engine::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit();
			break;
		default:
			break;
		}
	}
}

void Engine::update()
{
	_entityManager->update();
}

void Engine::render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

	_entityManager->render();

	SDL_RenderPresent(_renderer);
}
