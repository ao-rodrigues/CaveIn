#include "MenuSystem.h"

#include "../../Engine/Engine.h"
#include "../../Engine/AssetManager.h"

void MenuSystem::init()
{
	// Load all GUI assets
	AssetManager::instance().loadTexture("UIPanel", "Assets/Textures/ui_panel.png");
	AssetManager::instance().loadTexture("UIHeader", "Assets/Textures/ui_header.png");

	AssetManager::instance().loadFont("TitleFont", "Assets/Fonts/Alagard.ttf", 46);
	AssetManager::instance().loadFont("UITextFont", "Assets/Fonts/Alagard.ttf", 14);

	// Create entities, set references

	// Put game in initial state
}

void MenuSystem::update()
{
	// Check GUI events

	// Change game state accordingly
}