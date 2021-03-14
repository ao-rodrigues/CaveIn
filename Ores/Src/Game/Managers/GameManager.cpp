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

	for (std::size_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (std::size_t x = 0; x < GRID_WIDTH; x++)
		{
			if (x < GRID_WIDTH / 2)
			{
				_grid[x][y] = nullptr;
			}
			else
			{
				OreData oreData = ores[rand() % 8];

				Entity& ore = engine.createEntity();
				ore.addComponent<Sprite>(Sprite::RenderLayer::Foreground, 0, oreData.textureID, 32, 32);
				_grid[x][y] = &ore.addComponent<Ore>(oreData, hoverCursor.getComponent<HoverCursor>(), Vector2(x, y));

				Transform& t = ore.getComponent<Transform>();
				t.position.x = x * 32;
				t.position.y = y * 32;
			}

		}
	}
}

void GameManager::update()
{

}

void GameManager::onOreDestroyed(const Vector2& oreCoords, int typeIndex)
{
	int x = static_cast<int>(oreCoords.x);
	int y = static_cast<int>(oreCoords.y);

	bool neighborDestroyed = false;

	// Check up
	if (y - 1 >= 0 && _grid[x][y - 1] != nullptr && _grid[x][y - 1]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x, y - 1), _grid[x][y - 1]->getOreData().typeIndex, ComingFrom::Down);
		_grid[x][y - 1]->entity->destroy();
		_grid[x][y - 1] = nullptr;
		neighborDestroyed = true;
	}

	// Check down
	if (y + 1 < GRID_HEIGHT && _grid[x][y + 1] != nullptr && _grid[x][y + 1]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x, y + 1), _grid[x][y + 1]->getOreData().typeIndex, ComingFrom::Up);
		_grid[x][y + 1]->entity->destroy();
		_grid[x][y + 1] = nullptr;
		neighborDestroyed = true;
	}

	// Check left
	if (x - 1 >= 0 && _grid[x - 1][y] != nullptr && _grid[x - 1][y]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x - 1, y), _grid[x - 1][y]->getOreData().typeIndex, ComingFrom::Right);
		_grid[x - 1][y]->entity->destroy();
		_grid[x - 1][y] = nullptr;
		neighborDestroyed = true;
	}

	// Check right
	if (x + 1 < GRID_WIDTH && _grid[x + 1][y] != nullptr && _grid[x + 1][y]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x + 1, y), _grid[x + 1][y]->getOreData().typeIndex, ComingFrom::Left);
		_grid[x + 1][y]->entity->destroy();
		_grid[x + 1][y] = nullptr;
		neighborDestroyed = true;
	}

	// We only destroy a block if at least one of its neighbors was destroyed
	if (neighborDestroyed)
	{
		_grid[x][y]->entity->destroy();
		_grid[x][y] = nullptr;
	}
}

void GameManager::destroyNeighboringOre(const Vector2& oreCoords, int typeIndex, ComingFrom comingFrom)
{
	int x = static_cast<int>(oreCoords.x);
	int y = static_cast<int>(oreCoords.y);

	// Check up
	if (comingFrom != ComingFrom::Up && y - 1 >= 0 && _grid[x][y - 1] != nullptr && _grid[x][y - 1]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x, y - 1), _grid[x][y - 1]->getOreData().typeIndex, ComingFrom::Down);
		_grid[x][y - 1]->entity->destroy();
		_grid[x][y - 1] = nullptr;
	}

	// Check down
	if (comingFrom != ComingFrom::Down && y + 1 < GRID_HEIGHT && _grid[x][y + 1] != nullptr && _grid[x][y + 1]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x, y + 1), _grid[x][y + 1]->getOreData().typeIndex, ComingFrom::Up);
		_grid[x][y + 1]->entity->destroy();
		_grid[x][y + 1] = nullptr;
	}

	// Check left
	if (comingFrom != ComingFrom::Left && x - 1 >= 0 && _grid[x - 1][y] != nullptr && _grid[x - 1][y]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x - 1, y), _grid[x - 1][y]->getOreData().typeIndex, ComingFrom::Right);
		_grid[x - 1][y]->entity->destroy();
		_grid[x - 1][y] = nullptr;
	}

	// Check right
	if (comingFrom != ComingFrom::Right && x + 1 < GRID_WIDTH && _grid[x + 1][y] != nullptr && _grid[x + 1][y]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x + 1, y), _grid[x + 1][y]->getOreData().typeIndex, ComingFrom::Left);
		_grid[x + 1][y]->entity->destroy();
		_grid[x + 1][y] = nullptr;
	}
}
