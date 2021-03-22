#include <stdio.h>
#include "Engine.h"
#include "../Engine/InputManager.h"
#include "../Engine/ECS/Components/Transform.h"
#include "Game.h"

constexpr float MIN_DELTA_TIME = 1000.f / 240.f; // 240 FPS

int main(int argc, char *args[])
{
	Engine& engine = Engine::instance();
	engine.init("Cave-In", 800, 600, false, false, 800, 600);

	Game* game = new Game();
	game->init();

	float lastFrameTime = 0.f;

	while (engine.isRunning())
	{
		float time = SDL_GetTicks();
		float delta = time - lastFrameTime;

		if (delta > MIN_DELTA_TIME)
		{
			engine.handleEvents();

			game->update();

			engine.update();
			engine.render();

			lastFrameTime = time;
		}
	}

	engine.clear();
	delete game;

	return 0;
}