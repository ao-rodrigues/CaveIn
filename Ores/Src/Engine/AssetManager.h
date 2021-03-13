#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include "Singleton.h"

class AssetManager : public Singleton<AssetManager>
{
public:
	AssetManager();
	~AssetManager() = default;

	void clear();

	SDL_Texture* getTexture(std::string id);
	void loadTexture(std::string id, std::string path);

	/*
	inline static AssetManager* instance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new AssetManager();
		}

		return s_instance;
	}
	*/

private:
	//static AssetManager* s_instance;
	std::unordered_map<std::string, SDL_Texture*> _textures;
};