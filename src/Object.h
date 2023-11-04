#pragma once
#include <SDL_image.h>

class Object
{
private:
	SDL_Rect dest;
	SDL_Rect src;
	SDL_Texture* tex;

public:
	~Object();
	void SetSource(int w, int h, int x = 0, int y = 0);
	void SetDest(int x, int y, int w, int h);
	void SetDestPosition(int x, int y);
	void SetTexture(SDL_Texture* tex);

	SDL_Rect& GetSource() { return src; }
	SDL_Rect& GetDest() { return dest; }
	SDL_Texture* GetTexture() { return tex; }
};