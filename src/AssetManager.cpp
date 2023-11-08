#include "AssetManager.h"
#include "Render.h"
#include "Definitions.h"
#include <iostream>

AssetManager::AssetManager()
{
	InitTextures();
	InitFonts();
}

void AssetManager::InitTextures()
{
	LoadTexture(TILESETS_IMAGE, TILESETS_IMAGE_PATH);
	LoadTexture(HEART_IMAGE, HEART_IMAGE_PATH);
	LoadTexture(MOLE_IMAGE, MOLE_IMAGE_PATH);
	LoadTexture(CANDY_IMAGE, CANDY_IMAGE_PATH);
	LoadTexture(GHOST_IMAGE, GHOST_IMAGE_PATH);
}

void AssetManager::InitFonts()
{
	LoadFont(FONT, FONT_PATH, 40);
	LoadFont(OUTLINE_FONT, FONT_PATH, 43);
	LoadFont(SHADOW_FONT, FONT_PATH, 44);
}

void AssetManager::LoadTexture(const char* name, const char* fileName)
{
	SDL_Texture* tex;
	SDL_Surface* surf = IMG_Load(fileName);

	assert(surf != nullptr && "Texture could not be created!");

	tex = SDL_CreateTextureFromSurface(GetRender(), surf);

	if (tex != nullptr)
	{
		textures[name] = tex;
	}
	SDL_FreeSurface(surf);
}

SDL_Texture* AssetManager::GetTexture(const char* name)
{
	return this->textures.at(name);
}

void AssetManager::LoadFont(const char* name, const char* fileName, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(fileName, fontSize);

	assert(font != nullptr && "Font could not be created!");
	
	if (font != nullptr)
	{
		fonts[name] = font;
	}
}

TTF_Font* AssetManager::GetFont(const char* name)
{
	return this->fonts.at(name);
}
