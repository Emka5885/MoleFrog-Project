#include "Candy.h"
#include "Definitions.h"

Candy::Candy(SDL_Texture* tex)
{
	SetSource(0, 0, 382, 381);
	SetDest(GetDest().x, GetDest().y + 15, CANDY_SIZE, CANDY_SIZE);
	SetTexture(tex);
}

void Candy::Collision()
{
	score++;
}
