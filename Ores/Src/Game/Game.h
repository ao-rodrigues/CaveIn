#pragma once

#include "Systems/OreClickSystem.h"
#include "Systems/HoverCursorSystem.h"
#include "Systems/OreGridSystem.h"

class Game
{
public:
	Game() {}
	void init();
	void update();

private:
	OreClickSystem* _oreClickSystem = nullptr;
	HoverCursorSystem* _hoverCursorSystem = nullptr;
	OreGridSystem* _oreGridSystem = nullptr;
};