#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <stdio.h>
#include "Engine.h"
#include "../Engine/InputManager.h"
#include "../Engine/ECS/Components/Transform.h"
#include "Game.h"


int main(int argc, char *args[])
{
	Engine& engine = Engine::instance();
	engine.init("Ores", 800, 600, false, false, 800, 600);

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

	_CrtDumpMemoryLeaks();
	return 0;
}