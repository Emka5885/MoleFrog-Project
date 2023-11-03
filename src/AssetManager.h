#pragma once
#include <map>
#include <assert.h>
#include <SDL_image.h>

class AssetManager
{
public:
	AssetManager();
	~AssetManager() {}

	void InitTextures();

	void LoadTexture(const char* name, const char* fileName);
	SDL_Texture* GetTexture(const char* name);

private:
	std::map<const char*, SDL_Texture*> textures;
};