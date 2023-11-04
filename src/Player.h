#pragma once
#include <vector>
#include <map>
#include "Object.h"
#include "Interface.h"
#include "Definitions.h"

class Player : public Object, public Interface
{
private:
	int health, maxHealth;
	bool move, fall, moveToMound, jump;
	int jumpCounter, jumpVelocity, fallVelocity;
	direction dir;

public:
	Player();

	void SetNewDirection(direction d);
	void SetHealth(int h);
	void SetMove(bool m);
	void SetMoveToMound(bool m);
	void SetFall(bool f);
	void SetJump(bool j);
	void Update();

	direction GetDirection() const { return dir; }
	int GetHealth() const { return health; }
	bool GetFall() const { return fall; }
	bool GetMove() const { return move; }
	bool GetMoveToMound() const { return moveToMound; }
	bool GetJump() const { return jump; }
};