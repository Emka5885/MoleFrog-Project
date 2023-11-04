#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Interface
{
public:
	void Move(int x, int y, SDL_Rect& dest);
};