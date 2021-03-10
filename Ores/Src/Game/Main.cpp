#include <stdio.h>
#include "Engine.h"
#include "InputManager.h"
#include "../Engine/ECS/Transform.h"

int main(int argc, char *args[])
{
	Engine& engine = Engine::getInstance();
	engine.init("Ores", 800, 600, false, false);

	while (engine.isRunning())
	{
		engine.handleEvents();
		engine.update();
		engine.render();
	}

	engine.clear();

	return 0;
}