#pragma once

#include "Singleton.h"

struct Vector2;
class Ore;

constexpr auto GRID_WIDTH = 20;
constexpr auto GRID_HEIGHT = 10;

class GameManager : public Singleton<GameManager>
{
public:
	void init();
	void update();

	void onOreDestroyed(const Vector2& oreCoords, int typeIndex);

private:
	enum ComingFrom
	{
		Up,
		Down,
		Left,
		Right
	};

	void destroyNeighboringOre(const Vector2& oreCoords, int typeIndex, ComingFrom comingFrom);
	Ore* _grid[GRID_WIDTH][GRID_HEIGHT];
};