#include "Game.h"

#include <stdlib.h>
#include <ctime>

#include "Engine.h"

#include "Components/HoverCursor.h"
#include "../Engine/ECS/Components/Text.h"
#include "../Engine/ECS/Components/Animation.h"
#include "../Engine/ECS/Components/Audio.h"

void Game::init()
{
	Engine& engine = Engine::instance();

	_menuSystem = &engine.createSystem<MenuSystem>();
	_characterSystem = &engine.createSystem<CharacterSystem>();
	_oreClickSystem = &engine.createSystem<OreClickSystem>();
	_hoverCursorSystem = &engine.createSystem<HoverCursorSystem>();
	_oreGridSystem = &engine.createSystem<OreGridSystem>();
	_oreMovementSystem = &engine.createSystem<OreMovementSystem>();
	_scoreSystem = &engine.createSystem<ScoreSystem>();
	_soundSystem = &engine.createSystem<SoundSystem>();
	_fallingOresSystem = &engine.createSystem<FallingOresSystem>();
	_pointsPopupSystem = &engine.createSystem<PointsPopupSystem>();
	_pushTimerSystem = &engine.createSystem<PushTimerSystem>();
	_pushColumnSystem = &engine.createSystem<PushColumnSystem>();
	_clearEventsSystem = &engine.createSystem<ClearEventsSystem>();

	loadCursor();
	loadEnvironment();
	//loadCharacters();
	loadFPSCounter();
}

void Game::update()
{
	updateFPSCounter();

	_menuSystem->update();
	_characterSystem->update();
	_oreClickSystem->update();
	_hoverCursorSystem->update();
	_oreGridSystem->update();
	_oreMovementSystem->update();
	_scoreSystem->update();
	_soundSystem->update();
	_fallingOresSystem->update();
	_pointsPopupSystem->update();
	_pushTimerSystem->update();
	_pushColumnSystem->update();
	_clearEventsSystem->update();
}

void Game::loadCursor()
{
	AssetManager::instance().loadTexture("Hover", "Assets/Textures/cursor.png");
	Engine& engine = Engine::instance();

	Entity& hoverCursor = engine.createEntity();
	hoverCursor.addComponent<Sprite>(RenderLayer::Foreground, 1, "Hover", 0, 0, 32, 32);
	hoverCursor.addComponent<HoverCursor>();
}

void Game::loadEnvironment()
{
	srand(time(0));

	AssetManager::instance().loadTexture("Background1", "Assets/Textures/bg1.png");
	AssetManager::instance().loadTexture("Background2", "Assets/Textures/bg2.png");
	AssetManager::instance().loadTexture("Background3", "Assets/Textures/bg3.png");

	AssetManager::instance().loadTexture("TerrainFillBottomCenter", "Assets/Textures/terrain_fill_bottom_center.png");
	AssetManager::instance().loadTexture("TerrainFillBottomLeft", "Assets/Textures/terrain_fill_bottom_left.png");
	AssetManager::instance().loadTexture("TerrainFillBottomRight", "Assets/Textures/terrain_fill_bottom_right.png");
	AssetManager::instance().loadTexture("TerrainFillCenterCenter", "Assets/Textures/terrain_fill_center_center.png");
	AssetManager::instance().loadTexture("TerrainFillTopCenter", "Assets/Textures/terrain_fill_top_center.png");
	AssetManager::instance().loadTexture("TerrainFillTopLeft", "Assets/Textures/terrain_fill_top_left.png");
	AssetManager::instance().loadTexture("TerrainTopCenter", "Assets/Textures/terrain_top_center.png");

	Engine& engine = Engine::instance();

	Sprite& bg1 = engine.createEntity().addComponent<Sprite>(RenderLayer::Background, 0, "Background1", 0, 0, 320, 184);
	bg1.dstWidth = engine.getWorldDimensions().x;
	bg1.dstHeight = engine.getWorldDimensions().y;

	Sprite& bg2 = engine.createEntity().addComponent<Sprite>(RenderLayer::Background, -1, "Background2", 0, 0, 320, 184);
	bg2.dstWidth = engine.getWorldDimensions().x;
	bg2.dstHeight = engine.getWorldDimensions().y;

	Sprite& bg3 = engine.createEntity().addComponent<Sprite>(RenderLayer::Background, -2, "Background3", 0, 0, 320, 184);
	bg3.dstWidth = engine.getWorldDimensions().x;
	bg3.dstHeight = engine.getWorldDimensions().y;

	std::string terrainFillTiles[6] = {
		"TerrainFillBottomCenter",
		"TerrainFillBottomLeft",
		"TerrainFillBottomRight",
		"TerrainFillCenterCenter",
		"TerrainFillTopCenter",
		"TerrainFillTopLeft"
	};

	int numFloorTilesX = std::ceil(engine.getWorldDimensions().x / 32);
	int numFloorTilesY = std::ceil((engine.getWorldDimensions().y - 436) / 32);

	for (int i = 0; i < numFloorTilesX; i++)
	{
		Sprite& floorTop = engine.createEntity().addComponent<Sprite>(RenderLayer::Foreground, 0, "TerrainTopCenter", 0, 0, 16, 16);
		floorTop.transform->position.x = i * 32;
		floorTop.transform->position.y = 416.f;
		floorTop.transform->scale = Vector2(2.f, 2.f);

		for (int j = 0; j < numFloorTilesY; j++)
		{
			Sprite& terrainFill = engine.createEntity().addComponent<Sprite>(RenderLayer::Foreground, 0, terrainFillTiles[rand() % 6], 0, 0, 16, 16);
			terrainFill.transform->position.x = i * 32;
			terrainFill.transform->position.y = 448.f + j * 32;
			terrainFill.transform->scale = Vector2(2.f, 2.f);
		}
	}
}

void Game::loadCharacters()
{
	AssetManager::instance().loadTexture("King", "Assets/Textures/king.png");
	AssetManager::instance().loadTexture("HeroKnight", "Assets/Textures/hero_knight.png");
	AssetManager::instance().loadTexture("Knight", "Assets/Textures/knight.png");
	AssetManager::instance().loadTexture("Huntress", "Assets/Textures/huntress.png");

	Engine& engine = Engine::instance();

	Entity& king = engine.createEntity();
	king.addComponent<Sprite>(RenderLayer::Midground, 0, "King", 0, 0, 160, 111);
	king.addComponent<Animation>("King", 8, 100, 0);

	king.getComponent<Transform>().position.x = 50.f;
	king.getComponent<Transform>().position.y = 315.f;

	Entity& heroKnight = engine.createEntity();
	heroKnight.addComponent<Sprite>(RenderLayer::Midground, -1, "HeroKnight", 0, 0, 140, 140);
	heroKnight.addComponent<Animation>("HeroKnight", 11, 80, 0);

	heroKnight.getComponent<Transform>().position.x = 30.f;
	heroKnight.getComponent<Transform>().position.y = 340.f;

	Entity& knight = engine.createEntity();
	knight.addComponent<Sprite>(RenderLayer::Midground, 0, "Knight", 0, 0, 135, 135);
	knight.addComponent<Animation>("Knight", 10, 80, 0);

	knight.getComponent<Transform>().position.x = 45.f;
	knight.getComponent<Transform>().position.y = 330.f;

	Entity& huntress = engine.createEntity();
	huntress.addComponent<Sprite>(RenderLayer::Midground, 0, "Huntress", 0, 0, 150, 150);
	huntress.addComponent<Animation>("Huntress", 8, 80, 0);

	huntress.getComponent<Transform>().position.x = 10.f;
	huntress.getComponent<Transform>().position.y = 320.f;
}

void Game::loadFPSCounter()
{
	AssetManager::instance().loadFont("FPSFont", "Assets/Fonts/Alagard.ttf", 12);

	Engine& engine = Engine::instance();

	std::string fpsDisplay = "FPS: " + std::to_string(engine.FPS());
	SDL_Color fontColor = { 255, 255, 255, 255 };
	_fpsCounter = &engine.createEntity().addComponent<Text>("FPSFont", 0, fpsDisplay, fontColor, 100);
	_fpsCounter->transform->position = Vector2(engine.getWorldDimensions().x - 55.f, 10.f);
}

void Game::updateFPSCounter()
{
	_fpsCounter->setText("FPSFont", "FPS: " + std::to_string(Engine::instance().FPS()));
}
