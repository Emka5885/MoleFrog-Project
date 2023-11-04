#pragma once
#include "Entity.h"
#include "Interface.h"

class Ghost : public Entity, public Interface
{
private:

public:

	void Update();
};