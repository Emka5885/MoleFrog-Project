#include "Interface.h"

void Interface::Move(int x, int y, SDL_Rect& dest)
{
	dest.x = dest.x + x;
	dest.y = dest.y + y;
}