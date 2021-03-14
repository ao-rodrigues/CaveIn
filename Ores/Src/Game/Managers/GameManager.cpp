#include "GameManager.h"

#include <stdlib.h>
#include <ctime>

#include "Engine.h"

#include "../../Engine/AssetManager.h"
#include "../../Engine/InputManager.h"
#include "../Components/Ore.h"
#include "../Components/HoverCursor.h"
#include "../../Engine/ECS/Components/Animation.h"


void GameManager::init()
{
	srand(time(0));

	AssetManager::instance().loadTexture("Hover", "Assets/Textures/cursor.png");

	AssetManager::instance().loadTexture("Brick", "Assets/Textures/brick_brown0.png");
	AssetManager::instance().loadTexture("Cobble", "Assets/Textures/cobble_blood4.png");
	AssetManager::instance().loadTexture("Crystal", "Assets/Textures/crystal_wall04.png");
	AssetManager::instance().loadTexture("Marble", "Assets/Textures/marble_wall1.png");
	AssetManager::instance().loadTexture("Pebble", "Assets/Textures/pebble_brown2.png");
	AssetManager::instance().loadTexture("Red", "Assets/Textures/rough_red0.png");
	AssetManager::instance().loadTexture("Sandstone", "Assets/Textures/sandstone_wall1.png");
	AssetManager::instance().loadTexture("Slime", "Assets/Textures/slime0.png");

	Engine& engine = Engine::instance();

	OreData ores[8] = {
		OreData(0, 200, "Brick"),
		OreData(1, 200, "Cobble"),
		OreData(2, 200, "Crystal"),
		OreData(3, 200, "Marble"),
		OreData(4, 200, "Pebble"),
		OreData(5, 200, "Red"),
		OreData(6, 200, "Sandstone"),
		OreData(7, 200, "Slime")
	};

	Entity& hoverCursor = engine.createEntity();
	hoverCursor.addComponent<Sprite>(Sprite::RenderLayer::Foreground, 1, "Hover", 32, 32);
	hoverCursor.addComponent<HoverCursor>();
	
	for (std::size_t y = 0; y < 10; y++)
	{
		for (std::size_t x = 0; x < 10; x++)
		{
			OreData oreData = ores[rand() % 8];

			Entity& ore = engine.createEntity();
			ore.addComponent<Sprite>(Sprite::RenderLayer::Foreground, 0, oreData.textureID, 32, 32);
			ore.addComponent<Ore>(oreData, hoverCursor.getComponent<HoverCursor>());

			Transform& t = ore.getComponent<Transform>();
			t.position.x = x * 32;
			t.position.y = y * 32;
		}
	}
	
}

void GameManager::update()
{

}
