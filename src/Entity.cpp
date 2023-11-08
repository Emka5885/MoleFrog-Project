#include "Entity.h"
#include "Definitions.h"

Entity::Entity()
{
	Init();
}

void Entity::Init()
{
	int x = rand() % 2;
	int y = rand() % 4;

	initialX = x ? -100 : WIDTH;
	switch (y)
	{
	case 0:
		SetDestPosition(initialX, 20);
		break;
	case 1:
		SetDestPosition(initialX, 200);
		break;
	case 2:
		SetDestPosition(initialX, 380);
		break;
	case 3:
		SetDestPosition(initialX, 560);
		break;
	}
}

void Entity::Update()
{
	if (initialX < 0)
	{
		Move(ENTITY_SPEED, 0, GetDest());
	}
	else
	{
		Move(-ENTITY_SPEED, 0, GetDest());
	}
}

bool Entity::WhetherToDestroy()
{
	if (initialX < 0)
	{
		if (GetDest().x > WIDTH)
		{
			return true;
		}
	}
	else
	{
		if (GetDest().x < 0 - GetDest().w)
		{
			return true;
		}
	}
	return false;
}
