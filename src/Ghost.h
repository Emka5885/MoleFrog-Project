#pragma once
#include "Entity.h"

class Ghost : public Entity
{
public:
	Ghost(SDL_Texture* tex);
	void Collision() override;
};