#include "EntitySpawner.h"
#include "Ghost.h"
#include "Candy.h"
#include "Definitions.h"

Entity* EntitySpawner::Spawn(AssetManager* assets)
{
	Entity* entity;

	if (rand() % 2)
	{
		entity = new Candy(assets->GetTexture(CANDY_IMAGE));
	}
	else
	{
		entity = new Ghost(assets->GetTexture(GHOST_IMAGE));
	}

	return entity;
}
