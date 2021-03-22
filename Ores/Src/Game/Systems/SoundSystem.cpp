#include "SoundSystem.h"

#include <SDL_mixer.h>

#include "../../Engine/Engine.h"
#include "../../Engine/AssetManager.h"

#include "../Events/OreDestroyedEvent.h"
#include "../Events/LevelUpEvent.h"
#include "../Events/StartGameEvent.h"
#include "../Events/GameOverEvent.h"

void SoundSystem::init()
{
	AssetManager::instance().loadMusic("Soundtrack", "Assets/Audio/soundtrack.mp3");
	AssetManager::instance().loadMusic("GameOverSoundtrack", "Assets/Audio/game_over.mp3");
	AssetManager::instance().loadSoundEffect("OreDestroyedSFX", "Assets/Audio/ore_destroy.wav");
	AssetManager::instance().loadSoundEffect("LevelUpSFX", "Assets/Audio/level_up.mp3");
	AssetManager::instance().loadSoundEffect("CharactersDeath", "Assets/Audio/characters_death.wav");

	Engine& engine = Engine::instance();

	_soundtrack = &engine.createEntity().addComponent<Audio>(Audio::AudioType::Music, "Soundtrack");
	_soundtrack->setLoop(true);
	_soundtrack->play();
	_playingMainSoundtrack = true;

	_oreDestroyedSound = &engine.createEntity().addComponent<Audio>(Audio::AudioType::SoundEffect, "OreDestroyedSFX");
	_levelUpSound = &engine.createEntity().addComponent<Audio>(Audio::AudioType::SoundEffect, "LevelUpSFX");
	_charactersDeathSound = &engine.createEntity().addComponent<Audio>(Audio::AudioType::SoundEffect, "CharactersDeath");

	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
}

void SoundSystem::update()
{
	auto startGameEvents = _entityManager->getEntitiesWithComponentAll<StartGameEvent>();
	if (!_playingMainSoundtrack && startGameEvents.size() > 0)
	{
		_oreDestroyedSound->play();
		_soundtrack->stop();
		_soundtrack->setAudio(Audio::AudioType::Music, "Soundtrack");
		_soundtrack->setLoop(true);
		_soundtrack->play();
	}

	auto gameOverEvents = _entityManager->getEntitiesWithComponentAll<GameOverEvent>();
	if (gameOverEvents.size() > 0)
	{
		_charactersDeathSound->play();

		_soundtrack->stop();
		_soundtrack->setAudio(Audio::AudioType::Music, "GameOverSoundtrack");
		_soundtrack->setLoop(false);
		_soundtrack->play();
		_playingMainSoundtrack = false;
	}

	auto oreDestroyedEvents = _entityManager->getEntitiesWithComponentAll<OreDestroyedEvent>();
	if (oreDestroyedEvents.size() > 0)
	{
		_oreDestroyedSound->play();
	}

	
	auto levelUpEvents = _entityManager->getEntitiesWithComponentAll<LevelUpEvent>();
	if (levelUpEvents.size() > 0)
	{
		_levelUpSound->play();
	}
	
}