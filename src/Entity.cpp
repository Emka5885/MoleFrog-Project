#include "Entity.h"

Entity::Entity()
{
	Init();
}

void Entity::Init()
{
	int x = rand() % 2;
	int y = rand() % 4;

	if (x == 0)
	{
		initialX = -100;
	}
	else
	{
		initialX = WIDTH;
	}
	switch (y)
	{
	case 0:
		SetDest(initialX, 20, ENTITY_SIZE, ENTITY_SIZE);
		break;
	case 1:
		SetDest(initialX, 200, ENTITY_SIZE, ENTITY_SIZE);
		break;
	case 2:
		SetDest(initialX, 380, ENTITY_SIZE, ENTITY_SIZE);
		break;
	case 3:
		SetDest(initialX, 560, ENTITY_SIZE, ENTITY_SIZE);
		break;
	}
}