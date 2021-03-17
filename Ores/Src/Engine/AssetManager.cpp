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

	if (TTF_Init() == -1)
	{
		std::cerr << TTF_GetError() << std::endl;
	}
}

void AssetManager::loadTexture(const std::string& id, const std::string& path)
{
	if (!_textures.count(id))
	{
		SDL_Texture* texture = IMG_LoadTexture(Engine::instance().getRenderer(), path.c_str());
		if (texture)
		{
			_textures.emplace(id, texture);
			std::cout << "Texture: [" << path << "] loaded!" << std::endl;
		}
		else
		{
			std::cerr << SDL_GetError() << std::endl;
		}
	}
}

SDL_Texture* AssetManager::getTexture(const std::string& id)
{
	return _textures.count(id) ? _textures[id] : nullptr;
}

void AssetManager::loadFont(const std::string& id, const std::string& path, int fontSize)
{
	if (!_fonts.count(id))
	{
		TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);

		if (font)
		{
			_fonts.emplace(id, font);
			std::cout << "Font: [" << path << "] loaded!" << std::endl;
		}
		else
		{
			std::cerr << SDL_GetError() << std::endl;
		}
	}
}

TTF_Font* AssetManager::getFont(const std::string& id)
{
	return _fonts.count(id) ? _fonts[id] : nullptr;
}

