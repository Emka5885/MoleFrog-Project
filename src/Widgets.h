#pragma once
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Widgets
{
private:
						// heart, isFull
	std::vector<std::pair<SDL_Rect, bool>> destHearts;
	SDL_Rect srcFullHeart;
	SDL_Rect srcEmptyHeart;
	SDL_Texture* texHeart;
	TTF_Font* font;
	SDL_Color fontColor;
	const char* scoreText;
	int score = 0;
	
public:
	Widgets();
	~Widgets();

	void Init();

	void SetFont(TTF_Font* newfont);
	void SetTexture(SDL_Texture* newTexture);
	void AddPoint();
	void EraseHeart();

	int GetNumberOfFullHearts();
	SDL_Rect& GetFullHeartSrc() { return srcFullHeart; }
	SDL_Rect& GetEmptyHeartSrc() { return srcEmptyHeart; }
	std::vector<std::pair<SDL_Rect, bool>>& GetHeartsDest() { return destHearts; }
	SDL_Texture* GetHeartTexture() { return texHeart; }

	void Draw(SDL_Renderer* render);
};