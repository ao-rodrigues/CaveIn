#include "GameManager.h"

#include "Engine.h"

#include "../../Engine/AssetManager.h"
#include "../../Engine/InputManager.h"
#include "../Components/Ore.h"
#include "../../Engine/ECS/Components/Animation.h"


void GameManager::init()
{
	AssetManager::instance().loadTexture("Ore", "Assets/Textures/cobble_blood4.png");
	AssetManager::instance().loadTexture("OreHover", "Assets/Textures/dirt_full.png");
	AssetManager::instance().loadTexture("OreClick", "Assets/Textures/dirt_nw.png");
	AssetManager::instance().loadTexture("Character", "Assets/Textures/characters.png");

	Engine& engine = Engine::instance();

	OreData oreData;
	oreData.typeIndex = 0;
	oreData.destructionPoints = 200;
	oreData.defaultTextureID = "Ore";
	oreData.hoverTextureID = "OreHover";
	oreData.clickedTextureID = "OreClick";

	/*
	for (std::size_t y = 0; y < 32; y++)
	{
		for (std::size_t x = 0; x < 32; x++)
		{
			Entity& ore = engine.createEntity();
			ore.addComponent<Sprite>(Sprite::RenderLayer::Background, 0, "Ore", 32, 32);
			ore.addComponent<Ore>(oreData);

			Transform& t = ore.getComponent<Transform>();
			t.position.x = x * 32;
			t.position.y = y * 32;
		}
	}
	*/

	Entity& ore = engine.createEntity();
	ore.addComponent<Sprite>(Sprite::RenderLayer::Background, 0, "Ore", 32, 32);
	ore.addComponent<Ore>(oreData);

	Transform& t = ore.getComponent<Transform>();
	t.position.x = 32;

	/*
	Entity& player = engine.createEntity();
	player.addComponent<Sprite>(Sprite::RenderLayer::Foreground, 0, "Character", 32, 32);
	player.addComponent<Animation>("Character", 4, 100, 1);
	*/
}

void GameManager::update()
{

}
