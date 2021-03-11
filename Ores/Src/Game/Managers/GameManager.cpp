#include "GameManager.h"
#include "../../Engine/AssetManager.h"
#include "../../Engine/InputManager.h"

void GameManager::init()
{
	AssetManager::instance().loadTexture("Grass", "Assets/Textures/grass.png");
	AssetManager::instance().loadTexture("Characters", "Assets/Textures/characters.png");

	Engine& engine = Engine::instance();

	for (std::size_t y = 0; y < 32; y++)
	{
		for (std::size_t x = 0; x < 32; x++)
		{
			Entity& grassBlock = engine.createEntity();
			grassBlock.addComponent<Sprite>(engine.getRenderer(), Sprite::RenderLayer::Background, 0, "Grass", 32, 32);

			Transform& blockTransform = grassBlock.getComponent<Transform>();
			blockTransform.position.x = x * 32;
			blockTransform.position.y = y * 32;
		}
	}

	player = &engine.createEntity();
	player->addComponent<Sprite>(engine.getRenderer(), Sprite::RenderLayer::Foreground, 0, "Characters", 32, 32, 4, 100, 1);
}

void GameManager::update()
{
	if (InputManager::keyDown(SDLK_d))
	{
		player->getComponent<Transform>().position.x += 100.f * Engine::instance().deltaTime;
	}

	if (InputManager::keyDown(SDLK_a))
	{
		player->getComponent<Transform>().position.x -= 100.f * Engine::instance().deltaTime;
	}

	if (InputManager::keyDown(SDLK_w))
	{
		player->getComponent<Transform>().position.y -= 100.f * Engine::instance().deltaTime;
	}

	if (InputManager::keyDown(SDLK_s))
	{
		player->getComponent<Transform>().position.y += 100.f * Engine::instance().deltaTime;
	}
}
