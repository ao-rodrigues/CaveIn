#include "Game.h"

#include <stdlib.h>
#include <ctime>

#include "Engine.h"

#include "Components/HoverCursor.h"
#include "../Engine/ECS/Components/Text.h"

void Game::init()
{
	AssetManager::instance().loadTexture("Hover", "Assets/Textures/cursor.png");

	Engine& engine = Engine::instance();

	Entity& hoverCursor = engine.createEntity();
	hoverCursor.addComponent<Sprite>(RenderLayer::Foreground, 1, "Hover", 32, 32);
	hoverCursor.addComponent<HoverCursor>();

	_oreClickSystem = &engine.createSystem<OreClickSystem>();
	_hoverCursorSystem = &engine.createSystem<HoverCursorSystem>();
	_oreGridSystem = &engine.createSystem<OreGridSystem>();
	_oreMovementSystem = &engine.createSystem<OreMovementSystem>();
	_scoreSystem = &engine.createSystem<ScoreSystem>();
	_pointsPopupSystem = &engine.createSystem<PointsPopupSystem>();
}

void Game::update()
{
	_oreClickSystem->update();
	_hoverCursorSystem->update();
	_oreGridSystem->update();
	_oreMovementSystem->update();
	_scoreSystem->update();
	_pointsPopupSystem->update();
}
