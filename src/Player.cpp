#include "Player.h"

Player::Player()
{
	dir = left;
	move = moveToMound = fall = jump = false;
	maxHealth = MAX_HEALTH;
	health = maxHealth;
	jumpCounter = 0;
	jumpVelocity = 30;
}

void Player::SetNewDirection(direction d)
{
	dir = d;

	if (dir == left)
	{
		SetSource(0, 0, 420, 579);
	}
	else if(dir == right)
	{
		SetSource(420, 0, 420, 579);
	}
}

void Player::SetHealth(int h)
{
	health = h;
}

void Player::SetMove(bool m)
{
	move = m;
}

void Player::SetMoveToMound(bool m)
{
	moveToMound = m;
}

void Player::SetFall(bool f)
{
	fall = f;
}

void Player::SetJump(bool j)
{
	jump = j;
}

void Player::Update()
{
	if (move)
	{
		if (dir == left)
		{
			if (GetDest().x > 0 + PLAYER_SPEED)
			{
				Move(-PLAYER_SPEED, 0, GetDest());
			}
		}
		else if (dir == right)
		{
			if (GetDest().x < WIDTH - PLAYER_SPEED - GetDest().w)
			{
				Move(PLAYER_SPEED, 0, GetDest());
			}
		}
	}

	if (jump)
	{
		jumpCounter++;
		Move(0, -jumpVelocity, GetDest());
		jumpVelocity -= 2;
		if (jumpCounter > 15)
		{
			jumpCounter = 0;
			jumpVelocity = 30;
			jump = false;
		}
	}
	else if (fall)
	{
		Move(0, GRAVITY, GetDest());
	}
}
