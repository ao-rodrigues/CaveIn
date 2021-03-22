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
	_highScoreSystem = &engine.createSystem<HighScoreSystem>();
	_soundSystem = &engine.createSystem<SoundSystem>();
	_fallingOresSystem = &engine.createSystem<FallingOresSystem>();
	_pointsPopupSystem = &engine.createSystem<PointsPopupSystem>();
	_pushTimerSystem = &engine.createSystem<PushTimerSystem>();
	_pushColumnSystem = &engine.createSystem<PushColumnSystem>();
	_clearEventsSystem = &engine.createSystem<ClearEventsSystem>();

	loadCursor();
	loadEnvironment();
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
	_highScoreSystem->update();
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
	bg1.setDstWidth(static_cast<int>(engine.getWorldDimensions().x));
	bg1.setDstHeight(static_cast<int>(engine.getWorldDimensions().y));

	Sprite& bg2 = engine.createEntity().addComponent<Sprite>(RenderLayer::Background, -1, "Background2", 0, 0, 320, 184);
	bg2.setDstWidth(static_cast<int>(engine.getWorldDimensions().x));
	bg2.setDstHeight(static_cast<int>(engine.getWorldDimensions().y));

	Sprite& bg3 = engine.createEntity().addComponent<Sprite>(RenderLayer::Background, -2, "Background3", 0, 0, 320, 184);
	bg3.setDstWidth(static_cast<int>(engine.getWorldDimensions().x));
	bg3.setDstHeight(static_cast<int>(engine.getWorldDimensions().y));

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
		floorTop.getTransform().position.x = static_cast<float>(i * 32);
		floorTop.getTransform().position.y = 416.f;
		floorTop.getTransform().scale = Vector2(2.f, 2.f);

		for (int j = 0; j < numFloorTilesY; j++)
		{
			Sprite& terrainFill = engine.createEntity().addComponent<Sprite>(RenderLayer::Foreground, 0, terrainFillTiles[rand() % 6], 0, 0, 16, 16);
			terrainFill.getTransform().position.x = static_cast<float>(i * 32);
			terrainFill.getTransform().position.y = 448.f + j * 32;
			terrainFill.getTransform().scale = Vector2(2.f, 2.f);
		}
	}
}

void Game::loadFPSCounter()
{
	AssetManager::instance().loadFont("FPSFont", "Assets/Fonts/Alagard.ttf", 12);

	Engine& engine = Engine::instance();

	std::string fpsDisplay = "FPS: " + std::to_string(engine.FPS());
	SDL_Color fontColor = { 255, 255, 255, 255 };
	_fpsCounter = &engine.createEntity().addComponent<Text>("FPSFont", 0, fpsDisplay, fontColor, 100);
	_fpsCounter->getTransform().position = Vector2(engine.getWorldDimensions().x - 70.f, 10.f);
}

void Game::updateFPSCounter()
{
	_fpsCounter->setText("FPSFont", "FPS: " + std::to_string(Engine::instance().FPS()));
}
