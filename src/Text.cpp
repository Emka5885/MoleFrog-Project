#include "Text.h"
#include <iostream>

void Text::Draw(SDL_Renderer* render, TTF_Font* font, TTF_Font* outlineFont, TTF_Font* shadowFont, SDL_Color fontColor, SDL_Color fontOutlineColor, std::string& text, int x, int y)
{
	char character;
	int textWidth = 0;
	for (int i = text.size() - 1; i >= 0; i--)
	{
		SDL_Surface* surf;
		SDL_Texture* tex;
		SDL_Rect rect;

		character = text[i];
		std::string mark;
		mark += character;
		const char* st = mark.c_str();

		// shadow
		surf = TTF_RenderText_Solid(shadowFont, st, fontOutlineColor);
		tex = SDL_CreateTextureFromSurface(render, surf);
		rect.x = x - surf->w - textWidth + 3;
		rect.y = y;
		rect.w = surf->w;
		rect.h = surf->h;
		SDL_RenderCopy(render, tex, NULL, &rect);

		// outline
		surf = TTF_RenderText_Solid(outlineFont, st, fontOutlineColor);
		tex = SDL_CreateTextureFromSurface(render, surf);
		rect.x = x - surf->w - textWidth;
		rect.y = y - 1.4;
		rect.w = surf->w;
		rect.h = surf->h;
		SDL_RenderCopy(render, tex, NULL, &rect);

		// basic text
		surf = TTF_RenderText_Solid(font, st, fontColor);
		tex = SDL_CreateTextureFromSurface(render, surf);
		rect.x = x - surf->w - textWidth;
		rect.y = y;
		rect.w = surf->w;
		rect.h = surf->h;
		SDL_RenderCopy(render, tex, NULL, &rect);
		textWidth += surf->w + 2;

		SDL_FreeSurface(surf);
		SDL_DestroyTexture(tex);
	}
}
