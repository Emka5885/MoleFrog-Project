#pragma once
#include <random>
#include "Object.h"
#include "Definitions.h"

class Entity : public Object
{
protected:
	int initialX = 1;

public:
	Entity();

	void Init();
};