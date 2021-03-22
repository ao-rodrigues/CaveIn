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
	void updateGrid();

	Vector2 coordConvertGridToOre(int gridX, int gridY);
	Vector2 coordConvertOreToGrid(int oreX, int oreY);

	void destroyAllOres();
	void pushNewGrid();

	void pushColumn();
	void crushHeroes();

	void tryDestroy(const Vector2& oreCoords, int typeIndex);
	void destroyNeighboringOre(const Vector2& gridCoords, int typeIndex);

	Ore* _grid[GRID_WIDTH][GRID_HEIGHT]; // We work with a transposed grid because we'll be working column-major and this way it's more cache-friendly
	int _leftmostColIndex = GRID_WIDTH / 2; // The value that controls how close the grid is from the limit line (0)

	Vector2 _gridRoot;

	OreData _oreData[8] = {
		OreData(0, 100, "Brick"),
		OreData(1, 110, "Cobble"),
		OreData(2, 280, "Crystal"),
		OreData(3, 240, "Marble"),
		OreData(4, 150, "Pebble"),
		OreData(5, 100, "Red"),
		OreData(6, 90, "Sandstone"),
		OreData(7, 200, "Slime")
	};

	bool _gameRunning = false;
};