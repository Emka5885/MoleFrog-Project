#include "Object.h"

Object::~Object()
{
	SDL_DestroyTexture(tex);
}

void Object::SetSource(int x, int y, int w, int h)
{
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
}

void Object::SetDest(int x, int y, int w, int h)
{
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
}

void Object::SetDestPosition(int x, int y)
{
	dest.x = x;
	dest.y = y;
}

void Object::SetTexture(SDL_Texture* tex)
{
	this->tex = tex;
}
