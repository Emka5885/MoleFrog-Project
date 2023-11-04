#include "Ghost.h"

void Ghost::Update()
{
	if (initialX < 0)
	{
		Move(GHOST_SPEED, 0, GetDest());
	}
	else
	{
		Move(-GHOST_SPEED, 0, GetDest());
	}
}
