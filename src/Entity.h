#pragma once
#include <random>
#include "Object.h"
#include "Interface.h"

class Entity : public Object, public Interface
{
protected:
	int initialX = 1;

public:
	Entity();

	void Init();
	void Update();

	int GetInitialX() const { return initialX; }
	bool WhetherToDestroy();

	virtual void Collision() = 0;
};