#include "AssetManager.h"
#include "Engine.h"
#include <iostream>

AssetManager::AssetManager()
{
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
	{
		std::cerr << IMG_GetError() << std::endl;
	}
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
	return _textures.count(id) > 0 ? _textures[id] : nullptr;
}

void AssetManager::loadTexture(std::string id, std::string path)
{
	if (_textures.count(id) <= 0)
	{
		SDL_Texture* texture = IMG_LoadTexture(Engine::instance().getRenderer(), path.c_str());
		if (texture)
		{
			_textures[id] = texture;
			std::cout << "Texture: [" << path << "] loaded!" << std::endl;
		}
		else
		{
			std::cerr << SDL_GetError() << std::endl;
		}
	}
}
