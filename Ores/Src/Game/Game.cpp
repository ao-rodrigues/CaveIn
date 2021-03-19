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

	_oreClickSystem = &engine.createSystem<OreClickSystem>();
	_hoverCursorSystem = &engine.createSystem<HoverCursorSystem>();
	_oreGridSystem = &engine.createSystem<OreGridSystem>();
	_oreMovementSystem = &engine.createSystem<OreMovementSystem>();
	_scoreSystem = &engine.createSystem<ScoreSystem>();
	_pointsPopupSystem = &engine.createSystem<PointsPopupSystem>();
	_pushTimerSystem = &engine.createSystem<PushTimerSystem>();

	loadMusic();
	loadCursor();
	loadBackground();
	loadCharacters();
}

void Game::update()
{
	_oreClickSystem->update();
	_hoverCursorSystem->update();
	_oreGridSystem->update();
	_oreMovementSystem->update();
	_scoreSystem->update();
	_pointsPopupSystem->update();
	_pushTimerSystem->update();
}

void Game::loadMusic()
{
	AssetManager::instance().loadMusic("Soundtrack", "Assets/Audio/soundtrack.mp3");
	Engine& engine = Engine::instance();

	Audio& soundtrack = engine.createEntity().addComponent<Audio>(Audio::AudioType::Music, "Soundtrack");
	soundtrack.loop = true;
	soundtrack.play();
}

void Game::loadCursor()
{
	AssetManager::instance().loadTexture("Hover", "Assets/Textures/cursor.png");
	Engine& engine = Engine::instance();

	Entity& hoverCursor = engine.createEntity();
	hoverCursor.addComponent<Sprite>(RenderLayer::Foreground, 1, "Hover", 0, 0, 32, 32);
	hoverCursor.addComponent<HoverCursor>();
}

void Game::loadBackground()
{
	AssetManager::instance().loadTexture("Environment", "Assets/Textures/environment.png");

	Engine& engine = Engine::instance();

	Sprite& bg1 = engine.createEntity().addComponent<Sprite>(RenderLayer::Background, 0, "Environment", 0, 0, 320, 184);
	bg1.dstWidth = engine.getWorldDimensions().x;
	bg1.dstHeight = engine.getWorldDimensions().y;

	Sprite& bg2 = engine.createEntity().addComponent<Sprite>(RenderLayer::Background, -1, "Environment", 0, 186, 320, 184);
	bg2.dstWidth = engine.getWorldDimensions().x;
	bg2.dstHeight = engine.getWorldDimensions().y;

	Sprite& bg3 = engine.createEntity().addComponent<Sprite>(RenderLayer::Background, -2, "Environment", 0, 372, 320, 184);
	bg3.dstWidth = engine.getWorldDimensions().x;
	bg3.dstHeight = engine.getWorldDimensions().y;
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
	king.getComponent<Transform>().position.y = 300.f;

	Entity& heroKnight = engine.createEntity();
	heroKnight.addComponent<Sprite>(RenderLayer::Midground, -1, "HeroKnight", 0, 0, 140, 140);
	heroKnight.addComponent<Animation>("HeroKnight", 11, 80, 0);

	heroKnight.getComponent<Transform>().position.x = 30.f;
	heroKnight.getComponent<Transform>().position.y = 320.f;

	Entity& knight = engine.createEntity();
	knight.addComponent<Sprite>(RenderLayer::Midground, 0, "Knight", 0, 0, 135, 135);
	knight.addComponent<Animation>("Knight", 10, 80, 0);

	knight.getComponent<Transform>().position.x = 45.f;
	knight.getComponent<Transform>().position.y = 320.f;

	Entity& huntress = engine.createEntity();
	huntress.addComponent<Sprite>(RenderLayer::Midground, 0, "Huntress", 0, 0, 150, 150);
	huntress.addComponent<Animation>("Huntress", 8, 80, 0);

	huntress.getComponent<Transform>().position.x = 10.f;
	huntress.getComponent<Transform>().position.y = 310.f;
}
