#include "Game.h"

#include <stdlib.h>
#include <ctime>

#include "Engine.h"

#include "Components/HoverCursor.h"
#include "../Engine/ECS/Components/Text.h"

void Game::init()
{
	AssetManager::instance().loadTexture("Hover", "Assets/Textures/cursor.png");
	AssetManager::instance().loadFont("Alagard", "Assets/Fonts/Alagard.ttf", 24);

	Engine& engine = Engine::instance();

	Entity& hoverCursor = engine.createEntity();
	hoverCursor.addComponent<Sprite>(RenderLayer::Foreground, 1, "Hover", 32, 32);
	hoverCursor.addComponent<HoverCursor>();

	Entity& text = engine.createEntity();
	SDL_Color textColor = { 255, 255, 255, 255 };
	text.addComponent<Text>("Alagard", 10, 10, 0, "TEST STRING", textColor);

	_oreClickSystem = &engine.createSystem<OreClickSystem>();
	_hoverCursorSystem = &engine.createSystem<HoverCursorSystem>();
	_oreGridSystem = &engine.createSystem<OreGridSystem>();
	_oreMovementSystem = &engine.createSystem<OreMovementSystem>();
}

void Game::update()
{
	_oreClickSystem->update();
	_hoverCursorSystem->update();
	_oreGridSystem->update();
	_oreMovementSystem->update();
}
