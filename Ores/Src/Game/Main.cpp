#include <stdio.h>
#include "Engine.h"
#include "../Engine/InputManager.h"
#include "../Engine/ECS/Components/Transform.h"
#include "Managers/GameManager.h"

int main(int argc, char *args[])
{
	Engine& engine = Engine::instance();
	engine.init("Ores", 800, 600, false, false);

	GameManager& gameManager = GameManager::instance();
	gameManager.init();

	while (engine.isRunning())
	{
		engine.handleEvents();

		gameManager.update();

		engine.update();
		engine.render();
	}

	engine.clear();

	return 0;
}