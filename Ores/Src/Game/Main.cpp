#include <stdio.h>
#include "Engine.h"
#include "../Engine/InputManager.h"
#include "../Engine/ECS/Transform.h"

int main(int argc, char *args[])
{
	Engine& engine = Engine::instance();
	engine.init("Ores", 800, 600, false, false);

	while (engine.isRunning())
	{
		engine.handleEvents();

		// Game code
		if (InputManager::keyDown(SDLK_w))
		{
			std::cout << "Pressed W!" << std::endl;
		}

		engine.update();
		engine.render();
	}

	engine.clear();

	return 0;
}