#include "Widgets.h"
#include "Definitions.h"
#include <string>

Widgets::Widgets()
{
	Init();
}

Widgets::~Widgets()
{
	SDL_DestroyTexture(texHeart);
	TTF_CloseFont(font);
}

void Widgets::Init()
{
	srcFullHeart.x = 0;
	srcFullHeart.y = 0;
	srcFullHeart.w = 674;
	srcFullHeart.h = 603;
	srcEmptyHeart.x = 630;
	srcEmptyHeart.y = 0;
	srcEmptyHeart.w = 674;
	srcEmptyHeart.h = 603;

	int x = 0;

	for (int i = 0; i < MAX_HEALTH; i++)
	{
		SDL_Rect tempDest;
		tempDest.x = x + 20;
		tempDest.y = 20;
		tempDest.w = 51;
		tempDest.h = 45;

		x += 55;

		std::pair<SDL_Rect, bool> temp;
		temp.first = tempDest;
		temp.second = true;
		destHearts.emplace_back(temp);
	}

	fontColor.r = 255;
	fontColor.g = 255;
	fontColor.b = 255;
	fontColor.a = 255;
	scoreText = "Score: ";
}

void Widgets::SetFont(TTF_Font* newfont)
{
	font = newfont;
}

void Widgets::SetTexture(SDL_Texture* newTexture)
{
	texHeart = newTexture;
}

void Widgets::AddPoint()
{
	score++;
}

void Widgets::EraseHeart()
{
	for (int i = destHearts.size() - 1; i >= 0; i--)
	{
		if (destHearts[i].second)
		{
			destHearts[i].second = false;
			return;
		}
	}
}

int Widgets::GetNumberOfFullHearts()
{
	int counter = 0;
	for (int i = 0; i < destHearts.size(); i++)
	{
		if (destHearts[i].second)
		{
			counter++;
		}
		else
		{
			break;
		}
	}
	return counter;
}

void Widgets::Draw(SDL_Renderer* render)
{
	for (int i = 0; i < destHearts.size(); i++)
	{
		if (destHearts[i].second)
		{
			SDL_RenderCopy(render, texHeart, &srcFullHeart, &destHearts[i].first);
		}
		else
		{
			SDL_RenderCopy(render, texHeart, &srcEmptyHeart, &destHearts[i].first);
		}
	}

	SDL_Surface* surf;
	SDL_Texture* tex;
	SDL_Rect rect;
	std::string s = std::to_string(score);
	std::string scor = scoreText + s;
	const char* st = scor.c_str();
	surf = TTF_RenderText_Solid(font, st, fontColor);
	tex = SDL_CreateTextureFromSurface(render, surf);
	rect.x = WIDTH - 25 - surf->w;
	rect.y = 22;
	rect.w = surf->w;
	rect.h = surf->h;
	SDL_RenderCopy(render, tex, NULL, &rect);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);
}
