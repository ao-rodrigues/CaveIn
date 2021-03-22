#include <stdio.h>
#include "Engine.h"
#include "../Engine/InputManager.h"
#include "../Engine/ECS/Components/Transform.h"
#include "Game.h"


int main(int argc, char *args[])
{
	Engine& engine = Engine::instance();
	engine.init("Cave-In", 800, 600, false, false, 800, 600);

	Game* game = new Game();
	game->init();

	while (engine.isRunning())
	{
		engine.handleEvents();

		game->update();

		engine.update();
		engine.render();
	}

	engine.clear();
	delete game;

	return 0;
}