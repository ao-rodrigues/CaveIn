#include "OreGridSystem.h"

#include "../../Engine/Engine.h"
#include "../Events/OreSelectedEvent.h"
#include "../Components/Ore.h"
#include "../../Engine/AssetManager.h"

#include "../OreData.h"

void OreGridSystem::init()
{
	srand(time(0));

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

	for (int y = 0; y < GRID_WIDTH; y++)
	{
		for (int x = 0; x < GRID_HEIGHT; x++)
		{
			if (y < _leftmostColIndex)
			{
				_grid[y][x] = nullptr;
			}
			else
			{
				OreData oreData = ores[rand() % 8];

				Entity& ore = engine.createEntity();
				ore.addComponent<Sprite>(Sprite::RenderLayer::Foreground, 0, oreData.textureID, 32, 32);

				Vector2 convertedCoords = coordConvertGridToOre(x, y);
				_grid[y][x] = &ore.addComponent<Ore>(oreData, convertedCoords, 32, 32, 0.8f);

				Vector2 oreDimensions = _grid[y][x]->getOreDimensions();
				Transform& t = ore.getComponent<Transform>();
				t.position.x = convertedCoords.x * oreDimensions.x;
				t.position.y = convertedCoords.y * oreDimensions.y;
			}

		}
	}
}

void OreGridSystem::update()
{
	for (auto& event : _entityManager->getEntitiesWithComponent<OreSelectedEvent>())
	{
		OreSelectedEvent& selected = event->getComponent<OreSelectedEvent>();
		tryDestroy(selected.gridCoords, selected.typeIndex);
		event->destroy();
	}

	updateGrid();
}

void OreGridSystem::updateGrid()
{
	for (int y = _leftmostColIndex; y < GRID_WIDTH; y++)
	{
		int emptyBlocksCounter = 0;

		for (int x = 0; x < GRID_HEIGHT; x++)
		{
			if (_grid[y][x] == nullptr)
			{
				emptyBlocksCounter++;
				continue;
			}

			_grid[y][x]->flagNotVisited();

			if (_grid[y][x]->isSuspended())
			{
				if (x - 1 >= 0)
				{
					if (_grid[y][x - 1] == nullptr)
					{
						_grid[y][x - 1] = _grid[y][x];
						_grid[y][x]->setGridCoords(coordConvertGridToOre(x - 1, y));
						_grid[y][x] = nullptr;
					}
					else
					{
						_grid[y][x]->flagNotSuspended();
					}
				}
			}
		}

		if (emptyBlocksCounter == GRID_HEIGHT && y - 1 >= _leftmostColIndex)
		{
			// Empty column, move all blocks at the left to this column
			for (int x = 0; x < GRID_HEIGHT; x++)
			{
				if (_grid[y - 1][x] != nullptr)
				{
					_grid[y][x] = _grid[y - 1][x];
					_grid[y - 1][x]->setGridCoords(coordConvertGridToOre(x, y));
					_grid[y - 1][x] = nullptr;
				}
			}

			_leftmostColIndex++;
		}
	}
}

Vector2 OreGridSystem::coordConvertGridToOre(int gridX, int gridY)
{
	return Vector2(gridY, (GRID_HEIGHT - 1 - gridX));
}

Vector2 OreGridSystem::coordConvertOreToGrid(int oreX, int oreY)
{
	return Vector2((GRID_HEIGHT - 1 - oreY), oreX);
}

void OreGridSystem::tryDestroy(const Vector2& oreCoords, int typeIndex)
{
	// Convert the coords because the Ore component doesn't know that the grid is transposed
	Vector2 convertedCoords = coordConvertOreToGrid(static_cast<int>(oreCoords.x), static_cast<int>(oreCoords.y));
	int x = static_cast<int>(convertedCoords.x);
	int y = static_cast<int>(convertedCoords.y);

	_grid[y][x]->flagVisited();

	bool neighborDestroyed = false;

	// Check left
	if (y - 1 >= 0 && _grid[y - 1][x] != nullptr && _grid[y - 1][x]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x, y - 1), _grid[y - 1][x]->getOreData().typeIndex);
		_grid[y - 1][x]->entity->destroy();
		_grid[y - 1][x] = nullptr;
		neighborDestroyed = true;
	}

	// Check right
	if (y + 1 < GRID_WIDTH && _grid[y + 1][x] != nullptr && _grid[y + 1][x]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x, y + 1), _grid[y + 1][x]->getOreData().typeIndex);
		_grid[y + 1][x]->entity->destroy();
		_grid[y + 1][x] = nullptr;
		neighborDestroyed = true;
	}

	// Check up
	if (x + 1 < GRID_HEIGHT && _grid[y][x + 1] != nullptr && _grid[y][x + 1]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x + 1, y), _grid[y][x + 1]->getOreData().typeIndex);
		_grid[y][x + 1]->entity->destroy();
		_grid[y][x + 1] = nullptr;
		neighborDestroyed = true;
	}

	// Check down
	if (x - 1 >= 0 && _grid[y][x - 1] != nullptr && _grid[y][x - 1]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x - 1, y), _grid[y][x - 1]->getOreData().typeIndex);
		_grid[y][x - 1]->entity->destroy();
		_grid[y][x - 1] = nullptr;
		neighborDestroyed = true;
	}

	// We only destroy a block if at least one of its neighbors was destroyed
	if (neighborDestroyed)
	{
		_grid[y][x]->entity->destroy();
		_grid[y][x] = nullptr;

		// Flag all ores above as suspended
		for (int i = 1; x + i < GRID_HEIGHT; i++)
		{
			if (_grid[y][x + i] != nullptr && !_grid[y][x + i]->visited() && !_grid[y][x + i]->isSuspended())
			{
				_grid[y][x + i]->flagSuspended();
			}
		}
	}
}

void OreGridSystem::destroyNeighboringOre(const Vector2& gridCoords, int typeIndex)
{
	int x = static_cast<int>(gridCoords.x);
	int y = static_cast<int>(gridCoords.y);

	_grid[y][x]->flagVisited();

	// Check left
	if (y - 1 >= 0 && _grid[y - 1][x] != nullptr && _grid[y - 1][x]->getOreData().typeIndex == typeIndex && !_grid[y - 1][x]->visited())
	{
		destroyNeighboringOre(Vector2(x, y - 1), _grid[y - 1][x]->getOreData().typeIndex);
		_grid[y - 1][x]->entity->destroy();
		_grid[y - 1][x] = nullptr;
	}

	// Check right
	if (y + 1 < GRID_WIDTH && _grid[y + 1][x] != nullptr && _grid[y + 1][x]->getOreData().typeIndex == typeIndex && !_grid[y + 1][x]->visited())
	{
		destroyNeighboringOre(Vector2(x, y + 1), _grid[y + 1][x]->getOreData().typeIndex);
		_grid[y + 1][x]->entity->destroy();
		_grid[y + 1][x] = nullptr;
	}

	// Check down
	if (x - 1 >= 0 && _grid[y][x - 1] != nullptr && _grid[y][x - 1]->getOreData().typeIndex == typeIndex && !_grid[y][x - 1]->visited())
	{
		destroyNeighboringOre(Vector2(x - 1, y), _grid[y][x - 1]->getOreData().typeIndex);
		_grid[y][x - 1]->entity->destroy();
		_grid[y][x - 1] = nullptr;
	}

	// Check up
	if (x + 1 < GRID_HEIGHT && _grid[y][x + 1] != nullptr && _grid[y][x + 1]->getOreData().typeIndex == typeIndex && !_grid[y][x + 1]->visited())
	{
		destroyNeighboringOre(Vector2(x + 1, y), _grid[y][x + 1]->getOreData().typeIndex);
		_grid[y][x + 1]->entity->destroy();
		_grid[y][x + 1] = nullptr;

	}

	/*
	// Flag all ores above as suspended
	if (x + 1 < GRID_HEIGHT && _grid[y][x + 1] != nullptr && _grid[y][x + 1]->getOreData().typeIndex != typeIndex)
	{
		for (int i = 1; x + i < GRID_HEIGHT; i++)
		{
			if (_grid[y][x + i] != nullptr)
			{
				_grid[y][x + i]->flagSuspended();
			}
		}
	}
	*/

	// Flag all ores above as suspended
	for (int i = 1; x + i < GRID_HEIGHT; i++)
	{
		if (_grid[y][x + i] != nullptr && !_grid[y][x + i]->visited())
		{
			_grid[y][x + i]->flagSuspended();
		}
	}
}
