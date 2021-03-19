#pragma once

#include <SDL_mixer.h>
#include "../ECS.h"
#include "../../AssetManager.h"

class Audio : public Component
{
public:
	enum AudioType
	{
		Music,
		SoundEffect,

		Count
	};

	Audio(AudioType type, std::string audioID)
		: type(type)
		, audioID(audioID)
	{ }

	void init() override
	{
		switch (type)
		{
		case Audio::Music:
			music = AssetManager::instance().getMusic(audioID);
			break;
		case Audio::SoundEffect:
			soundEffect = AssetManager::instance().getSoundEffect(audioID);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// Play the sound in this component.
	/// </summary>
	/// <param name="numLoops">The number of loops to play. Will be ignored if loop is set to true.</param>
	/// <param name="channel">The channel where this audio will play. Only applies for audios of type SoundEffect.</param>
	void play(int numLoops = 0, int channel = -1)
	{
		switch (type)
		{
		case Audio::Music:
			Mix_PlayMusic(music, loop ? -1 : numLoops);
			break;
		case Audio::SoundEffect:
			Mix_PlayChannel(channel, soundEffect, numLoops);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// Pause the sound being played.
	/// </summary>
	/// <param name="channel">The channel of the audio to pause. Only applies for audios of type SoundEffect.</param>
	void pause(int channel = -1)
	{
		switch (type)
		{
		case Audio::Music:
			Mix_PauseMusic();
			break;
		case Audio::SoundEffect:
			Mix_Pause(channel);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// Stop the sound being played.
	/// </summary>
	/// <param name="channel">The channel of the audio to stop. Only applies for audios of type SoundEffect.</param>
	void stop(int channel = -1)
	{
		switch (type)
		{
		case Audio::Music:
			Mix_HaltMusic();
			break;
		case Audio::SoundEffect:
			Mix_HaltChannel(channel);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// Resume the sound that was paused.
	/// </summary>
	/// <param name="channel">The channel of the audio to resume. Only applies for audios of type SoundEffect.</param>
	void resume(int channel = -1)
	{
		switch (type)
		{
		case Audio::Music:
			Mix_ResumeMusic();
			break;
		case Audio::SoundEffect:
			Mix_Resume(channel);
			break;
		default:
			break;
		}
	}

	AudioType type;
	std::string audioID;
	bool loop = false;
	Mix_Music* music = nullptr;
	Mix_Chunk* soundEffect = nullptr;
};