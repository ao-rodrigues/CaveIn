#include "CharacterSystem.h"

#include "../../Engine/Engine.h"
#include "../../Engine/AssetManager.h"
#include "../../Engine/ECS/Components/Sprite.h"
#include "../../Engine/ECS/Components/Animation.h"
#include "../Events/StartGameEvent.h"
#include "../Events/GameOverEvent.h"

void CharacterSystem::init()
{
	AssetManager::instance().loadTexture("KingIdle", "Assets/Textures/king.png");
	AssetManager::instance().loadTexture("KingDeath", "Assets/Textures/king_death.png");

	AssetManager::instance().loadTexture("HeroKnightIdle", "Assets/Textures/hero_knight.png");
	AssetManager::instance().loadTexture("HeroKnightDeath", "Assets/Textures/hero_knight_death.png");

	AssetManager::instance().loadTexture("KnightIdle", "Assets/Textures/knight.png");
	AssetManager::instance().loadTexture("KnightDeath", "Assets/Textures/knight_death.png");

	AssetManager::instance().loadTexture("HuntressIdle", "Assets/Textures/huntress.png");
	AssetManager::instance().loadTexture("HuntressDeath", "Assets/Textures/huntress_death.png");

	Engine& engine = Engine::instance();

	_king = &engine.createEntity();
	_king->addComponent<Sprite>(RenderLayer::Foreground, 0, "KingIdle", 0, 0, 160, 111);

	std::vector<Animation::AnimationInfo> kingAnims = 
	{
		Animation::AnimationInfo("Idle", "KingIdle", 8, 100, true, 0),
		Animation::AnimationInfo("Death", "KingDeath", 6, 100, false, 0)
	};
	_king->addComponent<Animation>(kingAnims);

	_king->getComponent<Transform>().position.x = 50.f;
	_king->getComponent<Transform>().position.y = 315.f;

	_heroKnight = &engine.createEntity();
	_heroKnight->addComponent<Sprite>(RenderLayer::Foreground, -1, "HeroKnightIdle", 0, 0, 140, 140);

	std::vector<Animation::AnimationInfo> heroKnightAnims =
	{
		Animation::AnimationInfo("Idle", "HeroKnightIdle", 11, 100, true, 0),
		Animation::AnimationInfo("Death", "HeroKnightDeath", 9, 100, false, 0)
	};
	_heroKnight->addComponent<Animation>(heroKnightAnims);

	_heroKnight->getComponent<Transform>().position.x = 30.f;
	_heroKnight->getComponent<Transform>().position.y = 340.f;

	_knight = &engine.createEntity();
	_knight->addComponent<Sprite>(RenderLayer::Foreground, 0, "KnightIdle", 0, 0, 135, 135);

	std::vector<Animation::AnimationInfo> knightAnims =
	{
		Animation::AnimationInfo("Idle", "KnightIdle", 10, 100, true, 0),
		Animation::AnimationInfo("Death", "KnightDeath", 9, 100, false, 0)
	};
	_knight->addComponent<Animation>(knightAnims);

	_knight->getComponent<Transform>().position.x = 45.f;
	_knight->getComponent<Transform>().position.y = 330.f;

	_huntress = &engine.createEntity();
	_huntress->addComponent<Sprite>(RenderLayer::Foreground, 0, "HuntressIdle", 0, 0, 150, 150);

	std::vector<Animation::AnimationInfo> huntressAnims =
	{
		Animation::AnimationInfo("Idle", "HuntressIdle", 8, 100, true, 0),
		Animation::AnimationInfo("Death", "HuntressDeath", 8, 100, false, 0)
	};
	_huntress->addComponent<Animation>(huntressAnims);

	_huntress->getComponent<Transform>().position.x = 10.f;
	_huntress->getComponent<Transform>().position.y = 320.f;
}

void CharacterSystem::update()
{
	auto startGameEvents = _entityManager->getEntitiesWithComponentAll<StartGameEvent>(true);
	if (startGameEvents.size() > 0)
	{
		_king->getComponent<Animation>().setAnimation("Idle");
		_heroKnight->getComponent<Animation>().setAnimation("Idle");
		_knight->getComponent<Animation>().setAnimation("Idle");
		_huntress->getComponent<Animation>().setAnimation("Idle");
	}

	auto gameOverEvents = _entityManager->getEntitiesWithComponentAll<GameOverEvent>(true);
	if (gameOverEvents.size() > 0)
	{
		_king->getComponent<Animation>().setAnimation("Death");
		_heroKnight->getComponent<Animation>().setAnimation("Death");
		_knight->getComponent<Animation>().setAnimation("Death");
		_huntress->getComponent<Animation>().setAnimation("Death");
	}
}
