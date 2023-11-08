#pragma once
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Text.h"

class Widgets
{
private:
						// heart, isFull
	std::vector<std::pair<SDL_Rect, bool>> destHearts;
	SDL_Rect srcFullHeart;
	SDL_Rect srcEmptyHeart;
	SDL_Texture* texHeart;
	TTF_Font* font;
	TTF_Font* shadowFont;
	TTF_Font* outlineFont;
	SDL_Color fontColor;
	SDL_Color fontOutlineColor;
	const char* scoreText;
	Text* text;
	
public:
	Widgets();
	~Widgets();

	void Init();

	void SetFont(TTF_Font* newFont);
	void SetOutlineFont(TTF_Font* newOutlineFont);
	void SetShadowFont(TTF_Font* newShadowFont);
	void SetTexture(SDL_Texture* newTexture);
	void EraseHeart();

	int GetNumberOfFullHearts();
	SDL_Rect& GetFullHeartSrc() { return srcFullHeart; }
	SDL_Rect& GetEmptyHeartSrc() { return srcEmptyHeart; }
	std::vector<std::pair<SDL_Rect, bool>>& GetHeartsDest() { return destHearts; }
	SDL_Texture* GetHeartTexture() { return texHeart; }

	void Draw(SDL_Renderer* render);
};