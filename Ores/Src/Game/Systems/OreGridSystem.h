#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Math/Vector2.h"

#include "../OreData.h"

class Ore;

constexpr auto GRID_WIDTH = 20;
constexpr auto GRID_HEIGHT = 10;

class OreGridSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;

private:
	inline int getRandomOreIndex()
	{
		return rand() % 6;
	}
	void updateGrid();

	Vector2 coordConvertGridToOre(int gridX, int gridY);
	Vector2 coordConvertOreToGrid(int oreX, int oreY);

	void destroyAllOres();
	void pushNewGrid();

	void pushColumn();
	void crushHeroes();

	void tryDestroy(Vector2 oreCoords, int typeIndex);
	void destroyNeighboringOre(Vector2 gridCoords, int typeIndex);

	Ore* _grid[GRID_WIDTH][GRID_HEIGHT]; // We work with a transposed grid because we'll be working column-major and this way it's more cache-friendly
	int _leftmostColIndex = GRID_WIDTH / 2; // The value that controls how close the grid is from the limit line (0)

	Vector2 _gridRoot;

	OreData _oreData[6] = {
		//OreData(0, 113, "Brick"),
		OreData(0, 132, "Cobble"),
		OreData(1, 282, "Crystal"),
		OreData(2, 150, "Marble"),
		//OreData(2, 150, "Pebble"),
		OreData(3, 111, "Red"),
		OreData(4, 98, "Sandstone"),
		OreData(5, 202, "Slime")
	};

	bool _gameRunning = false;
};