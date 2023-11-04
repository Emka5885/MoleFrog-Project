#pragma once
#include <map>
#include <assert.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class AssetManager
{
public:
	AssetManager();
	~AssetManager() {}

	void InitTextures();
	void InitFonts();

	void LoadTexture(const char* name, const char* fileName);
	SDL_Texture* GetTexture(const char* name);

	void LoadFont(const char* name, const char* fileName, int fontSize);
	TTF_Font* GetFont(const char* name);

private:
	std::map<const char*, SDL_Texture*> textures;
	std::map<const char*, TTF_Font*> fonts;
};