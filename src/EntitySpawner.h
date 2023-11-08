#pragma once
#include "Entity.h"
#include "AssetManager.h"

class EntitySpawner
{
public:
	EntitySpawner() {}
	class Entity* Spawn(AssetManager* assets);
};