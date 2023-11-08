#pragma once
#include "Entity.h"

class Candy : public Entity
{
public:
	Candy(SDL_Texture* tex);
	void Collision() override;
};