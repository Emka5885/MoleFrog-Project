#pragma once
#include "Object.h"

class Tileset : public Object
{
private:
	int id;
	bool solid;

public:
	Tileset() { id = 0; solid = 1; }

	void SetID(int id);
	void SetSolid(bool solid);

	int GetID() const { return id; }
	bool GetSolid() const { return solid; }
};