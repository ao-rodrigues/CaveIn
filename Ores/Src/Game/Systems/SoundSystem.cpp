#include "SoundSystem.h"

#include <SDL_mixer.h>

#include "../../Engine/Engine.h"
#include "../../Engine/AssetManager.h"

#include "../Events/OreDestroyedEvent.h"
#include "../Events/LevelUpEvent.h"

void SoundSystem::init()
{
	AssetManager::instance().loadMusic("Soundtrack", "Assets/Audio/soundtrack.mp3");
	AssetManager::instance().loadSoundEffect("OreDestroyedSFX", "Assets/Audio/ore_destroy.wav");
	AssetManager::instance().loadSoundEffect("LevelUpSFX", "Assets/Audio/level_up.mp3");

	Engine& engine = Engine::instance();

	Audio& soundtrack = engine.createEntity().addComponent<Audio>(Audio::AudioType::Music, "Soundtrack");
	soundtrack.loop = true;
	soundtrack.play();

	_oreDestroyedSound = &engine.createEntity().addComponent<Audio>(Audio::AudioType::SoundEffect, "OreDestroyedSFX");
	_levelUpSound = &engine.createEntity().addComponent<Audio>(Audio::AudioType::SoundEffect, "LevelUpSFX");

	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
}

void SoundSystem::update()
{
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