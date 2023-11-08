#pragma once
#include <string>
#include "SDL_ttf.h"

class Text
{
public:
	void Draw(SDL_Renderer* render, TTF_Font* font, TTF_Font* outlineFont, TTF_Font* shadowFont, SDL_Color fontColor, SDL_Color fontOutlineColor, std::string& text, int x, int y);
};