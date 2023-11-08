#include "Ghost.h"
#include "Definitions.h"

Ghost::Ghost(SDL_Texture* tex)
{
	//SetSource(0, 0, 531, 489);
	SetSource(0, 0, 511, 466);
	SetDest(GetDest().x, GetDest().y, GHOST_SIZE, GHOST_SIZE);
	SetTexture(tex);
}

void Ghost::Collision()
{
	numberOfHearts--;
}
