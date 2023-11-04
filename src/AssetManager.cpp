#include "AssetManager.h"
#include "Render.h"

AssetManager::AssetManager()
{
	InitTextures();
}

void AssetManager::InitTextures()
{
	LoadTexture("moleL", "res/moleL.png");
	LoadTexture("tilesets", "res/moleFrogTilesets.png");
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
