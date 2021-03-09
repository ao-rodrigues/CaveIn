#include "Engine.h"
#include <iostream>

Engine* Engine::s_instance = nullptr;

Engine::Engine()
{
	_isRunning = false;
	_window = nullptr;
	_renderer = nullptr;
}

Engine::~Engine()
{
}

void Engine::init(char* title, int width, int height, bool fullscreen, bool vsync)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << SDL_GetError() << std::endl;
	}

	auto windowFlags = fullscreen ? SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);

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

// TODO
void Engine::update()
{
	// Update entities
}

// TODO
void Engine::render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

	// Render entities

	SDL_RenderPresent(_renderer);
}
