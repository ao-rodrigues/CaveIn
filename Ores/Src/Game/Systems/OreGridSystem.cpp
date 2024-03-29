#include "OreGridSystem.h"

#include "../../Engine/Engine.h"
#include "../../Engine/AssetManager.h"
#include "../Components/Ore.h"
#include "../Events/OreSelectedEvent.h"
#include "../Events/OreDestroyedEvent.h"
#include "../Events/OreDestroyedInLevelUpEvent.h"
#include "../Events/PushEvent.h"
#include "../Events/LevelUpEvent.h"
#include "../Events/StartGameEvent.h"
#include "../Events/GameOverEvent.h"
#include "../Events/PauseGameEvent.h"
#include "../Events/ResumeGameEvent.h"

void OreGridSystem::init()
{
	srand(time(0));

	//AssetManager::instance().loadTexture("Brick", "Assets/Textures/brick_brown0.png");
	AssetManager::instance().loadTexture("Cobble", "Assets/Textures/cobble_blood4.png");
	AssetManager::instance().loadTexture("Crystal", "Assets/Textures/crystal_wall04.png");
	AssetManager::instance().loadTexture("Marble", "Assets/Textures/marble_wall1.png");
	//AssetManager::instance().loadTexture("Pebble", "Assets/Textures/pebble_brown2.png");
	AssetManager::instance().loadTexture("Red", "Assets/Textures/rough_red0.png");
	AssetManager::instance().loadTexture("Sandstone", "Assets/Textures/sandstone_wall1.png");
	AssetManager::instance().loadTexture("Slime", "Assets/Textures/slime0.png");

	
	Engine& engine = Engine::instance();

	_gridRoot = Vector2(Engine::instance().getWorldDimensions().x - (GRID_WIDTH * 32), 100.f);

	for (int y = 0; y < GRID_WIDTH; y++)
	{
		for (int x = 0; x < GRID_HEIGHT; x++)
		{
			_grid[y][x] = nullptr;
		}
	}
}

void OreGridSystem::update()
{
	if (!_gameRunning)
	{
		auto startGameEvents = _entityManager->getEntitiesWithComponentAll<StartGameEvent>();
		if (startGameEvents.size() > 0)
		{
			_gameRunning = true;
			destroyAllOres();
			pushNewGrid();
		}
		else
		{
			// Check if game has been resumed
			auto resumeGameEvents = _entityManager->getEntitiesWithComponentAll<ResumeGameEvent>();
			if (resumeGameEvents.size() > 0)
			{
				_gameRunning = true;
			}
			else
			{
				return;
			}
		}
	}

	// Check if the game has been paused
	auto pauseGameEvents = _entityManager->getEntitiesWithComponentAll<PauseGameEvent>();
	if (pauseGameEvents.size() > 0)
	{
		_gameRunning = false;
		return;
	}

	// Check if the game is over
	auto gameOverEvents = _entityManager->getEntitiesWithComponentAll<GameOverEvent>(true);
	if (gameOverEvents.size() > 0)
	{
		_gameRunning = false;
		return;
	}

	for (auto& event : _entityManager->getEntitiesWithComponentAll<LevelUpEvent>(true))
	{
		destroyAllOres();
		pushNewGrid();
	}

	for (auto& event : _entityManager->getEntitiesWithComponentAll<PushEvent>(true))
	{
		pushColumn();
	}

	for (auto& event : _entityManager->getEntitiesWithComponentAll<OreSelectedEvent>())
	{
		OreSelectedEvent selected = event->getComponent<OreSelectedEvent>();
		tryDestroy(selected.gridCoords, selected.typeIndex);
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
				// Find the first null position starting from the bottom,
				// then we move the ore to that position

				int newX;
				for (newX = 0; newX < GRID_HEIGHT; newX++)
				{
					if (_grid[y][newX] == nullptr) break;
				}

				_grid[y][newX] = _grid[y][x];
				_grid[y][x]->setGridCoords(coordConvertGridToOre(newX, y), false);
				_grid[y][x]->flagNotSuspended();
				_grid[y][x] = nullptr;
			}
		}

		if (emptyBlocksCounter == GRID_HEIGHT && y - 1 >= _leftmostColIndex)
		{
			// Empty column, move all the columns at the left 1 step to the right to fill the gap
			for (int i = 1, j = 0; y - i >= _leftmostColIndex && y - j >= _leftmostColIndex + 1; i++, j++)
			{
				for (int x = 0; x < GRID_HEIGHT; x++)
				{
					if (_grid[y - i][x] != nullptr)
					{
						_grid[y - j][x] = _grid[y - i][x];
						_grid[y - i][x]->setGridCoords(coordConvertGridToOre(x, y - j), false);
						_grid[y - i][x] = nullptr;
					}
				}
			}

			_leftmostColIndex++;
		}
	}
}

Vector2 OreGridSystem::coordConvertGridToOre(int gridX, int gridY)
{
	return Vector2(static_cast<float>(gridY), static_cast<float>((GRID_HEIGHT - 1 - gridX)));
}

Vector2 OreGridSystem::coordConvertOreToGrid(int oreX, int oreY)
{
	return Vector2(static_cast<float>((GRID_HEIGHT - 1 - oreY)), static_cast<float>(oreX));
}

void OreGridSystem::destroyAllOres()
{
	for (int y = _leftmostColIndex; y < GRID_WIDTH; y++)
	{
		for (int x = 0; x < GRID_HEIGHT; x++)
		{
			if (_grid[y][x] != nullptr)
			{
				_entityManager->createEntity().addComponent<OreDestroyedInLevelUpEvent>(_grid[y][x]->getOreData(), _grid[y][x]->getTransform().position);
				_grid[y][x]->destroy();
				_grid[y][x] = nullptr;
			}
		}
	}

	_leftmostColIndex = GRID_WIDTH / 2;
}

void OreGridSystem::pushNewGrid()
{
	Engine& engine = Engine::instance();

	for (int y = _leftmostColIndex; y < GRID_WIDTH; y++)
	{
		for (int x = 0; x < GRID_HEIGHT; x++)
		{
			OreData oreData = _oreData[getRandomOreIndex()];

			Entity& ore = engine.createEntity();
			ore.addComponent<Sprite>(RenderLayer::Midground, 0, oreData.textureID, 0, 0, 32, 32);

			Vector2 startingCoords = coordConvertGridToOre(x, y + GRID_WIDTH);
			_grid[y][x] = &ore.addComponent<Ore>(oreData, _gridRoot, startingCoords, 32, 32, 0.8f);

			Vector2 convertedCoords = coordConvertGridToOre(x, y);
			_grid[y][x]->setGridCoords(convertedCoords, false);
		}
	}
}

void OreGridSystem::pushColumn()
{
	if (_leftmostColIndex - 1 < 0)
	{
		// Send game over event
		_entityManager->createEntity().addComponent<GameOverEvent>().entity->setDestroyNextFrame(true);

		// Move all ores a bit more to the left to CRUSH THE HEROES
		crushHeroes();
		return;
	}

	// Move everything one column to the left
	for (int y = _leftmostColIndex; y < GRID_WIDTH; y++)
	{
		for (int x = 0; x < GRID_HEIGHT; x++)
		{
			if (_grid[y][x] != nullptr)
			{
				_grid[y - 1][x] = _grid[y][x];
				_grid[y - 1][x]->setGridCoords(coordConvertGridToOre(x, y - 1), false);
				_grid[y][x] = nullptr;
			}
		}
	}

	_leftmostColIndex--;


	Engine& engine = Engine::instance();

	// Add new column at the end
	for (int x = 0; x < GRID_HEIGHT; x++)
	{
		OreData oreData = _oreData[getRandomOreIndex()];

		Entity& ore = engine.createEntity();
		ore.addComponent<Sprite>(RenderLayer::Midground, 0, oreData.textureID, 0, 0, 32, 32);

		Vector2 startingCoords = coordConvertGridToOre(x, GRID_WIDTH);
		_grid[GRID_WIDTH - 1][x] = &ore.addComponent<Ore>(oreData, _gridRoot, startingCoords, 32, 32, 0.8f);

		Vector2 convertedCoords = coordConvertGridToOre(x, GRID_WIDTH - 1);
		_grid[GRID_WIDTH - 1][x]->setGridCoords(convertedCoords, false);
	}
}

void OreGridSystem::crushHeroes()
{
	for (int y = _leftmostColIndex; y < GRID_WIDTH; y++)
	{
		for (int x = 0; x < GRID_HEIGHT; x++)
		{
			if (_grid[y][x] != nullptr)
			{
				_grid[y][x]->setGridCoords(coordConvertGridToOre(x, y - 3), false);
			}
		}
	}
}

void OreGridSystem::tryDestroy(Vector2 oreCoords, int typeIndex)
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
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y - 1][x]->getOreData(), _grid[y - 1][x]->getTransform().position);
		_grid[y - 1][x]->destroy();
		_grid[y - 1][x] = nullptr;
		neighborDestroyed = true;
	}

	// Check right
	if (y + 1 < GRID_WIDTH && _grid[y + 1][x] != nullptr && _grid[y + 1][x]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x, y + 1), _grid[y + 1][x]->getOreData().typeIndex);
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y + 1][x]->getOreData(), _grid[y + 1][x]->getTransform().position);
		_grid[y + 1][x]->destroy();
		_grid[y + 1][x] = nullptr;
		neighborDestroyed = true;
	}

	// Check up
	if (x + 1 < GRID_HEIGHT && _grid[y][x + 1] != nullptr && _grid[y][x + 1]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x + 1, y), _grid[y][x + 1]->getOreData().typeIndex);
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y][x + 1]->getOreData(), _grid[y][x + 1]->getTransform().position);
		_grid[y][x + 1]->destroy();
		_grid[y][x + 1] = nullptr;
		neighborDestroyed = true;
	}

	// Check down
	if (x - 1 >= 0 && _grid[y][x - 1] != nullptr && _grid[y][x - 1]->getOreData().typeIndex == typeIndex)
	{
		destroyNeighboringOre(Vector2(x - 1, y), _grid[y][x - 1]->getOreData().typeIndex);
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y][x - 1]->getOreData(), _grid[y][x - 1]->getTransform().position);
		_grid[y][x - 1]->destroy();
		_grid[y][x - 1] = nullptr;
		neighborDestroyed = true;
	}

	// We only destroy a block if at least one of its neighbors was destroyed
	if (neighborDestroyed)
	{
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y][x]->getOreData(), _grid[y][x]->getTransform().position);
		_grid[y][x]->destroy();
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

void OreGridSystem::destroyNeighboringOre(Vector2 gridCoords, int typeIndex)
{
	int x = static_cast<int>(gridCoords.x);
	int y = static_cast<int>(gridCoords.y);

	_grid[y][x]->flagVisited();

	// Check left
	if (y - 1 >= 0 && _grid[y - 1][x] != nullptr && _grid[y - 1][x]->getOreData().typeIndex == typeIndex && !_grid[y - 1][x]->visited())
	{
		destroyNeighboringOre(Vector2(x, y - 1), _grid[y - 1][x]->getOreData().typeIndex);
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y - 1][x]->getOreData(), _grid[y - 1][x]->getTransform().position);
		_grid[y - 1][x]->destroy();
		_grid[y - 1][x] = nullptr;
	}

	// Check right
	if (y + 1 < GRID_WIDTH && _grid[y + 1][x] != nullptr && _grid[y + 1][x]->getOreData().typeIndex == typeIndex && !_grid[y + 1][x]->visited())
	{
		destroyNeighboringOre(Vector2(x, y + 1), _grid[y + 1][x]->getOreData().typeIndex);
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y + 1][x]->getOreData(), _grid[y + 1][x]->getTransform().position);
		_grid[y + 1][x]->destroy();
		_grid[y + 1][x] = nullptr;
	}

	// Check down
	if (x - 1 >= 0 && _grid[y][x - 1] != nullptr && _grid[y][x - 1]->getOreData().typeIndex == typeIndex && !_grid[y][x - 1]->visited())
	{
		destroyNeighboringOre(Vector2(x - 1, y), _grid[y][x - 1]->getOreData().typeIndex);
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y][x - 1]->getOreData(), _grid[y][x - 1]->getTransform().position);
		_grid[y][x - 1]->destroy();
		_grid[y][x - 1] = nullptr;
	}

	// Check up
	if (x + 1 < GRID_HEIGHT && _grid[y][x + 1] != nullptr && _grid[y][x + 1]->getOreData().typeIndex == typeIndex && !_grid[y][x + 1]->visited())
	{
		destroyNeighboringOre(Vector2(x + 1, y), _grid[y][x + 1]->getOreData().typeIndex);
		_entityManager->createEntity().addComponent <OreDestroyedEvent>(_grid[y][x + 1]->getOreData(), _grid[y][x + 1]->getTransform().position);
		_grid[y][x + 1]->destroy();
		_grid[y][x + 1] = nullptr;

	}

	// Flag all ores above as suspended
	for (int i = 1; x + i < GRID_HEIGHT; i++)
	{
		if (_grid[y][x + i] != nullptr && !_grid[y][x + i]->visited())
		{
			_grid[y][x + i]->flagSuspended();
		}
	}
}
