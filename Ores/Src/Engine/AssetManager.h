#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <unordered_map>
#include <string>

#include "Singleton.h"

class AssetManager : public Singleton<AssetManager>
{
public:
	AssetManager();
	~AssetManager() = default;

	void clear();

	void loadTexture(const std::string& id, const std::string& path);
	SDL_Texture* getTexture(const std::string& id);

	void loadFont(const std::string& id, const std::string& path, int fontSize);
	TTF_Font* getFont(const std::string& id);

	void loadMusic(const std::string& id, const std::string& path);
	Mix_Music* getMusic(const std::string& id);

	void loadSoundEffect(const std::string& id, const std::string& path);
	Mix_Chunk* getSoundEffect(const std::string& id);

private:
	std::unordered_map<std::string, SDL_Texture*> _textures;
	std::unordered_map<std::string, TTF_Font*> _fonts;
	std::unordered_map<std::string, Mix_Music*> _music;
	std::unordered_map<std::string, Mix_Chunk*> _soundEffects;
};