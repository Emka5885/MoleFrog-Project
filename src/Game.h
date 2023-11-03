#pragma once
#include <SDL.h>
#include <assert.h>
#include "Render.h"
#include "AssetManager.h"

class Game
{
public:
	Game();
	~Game();
	void Init();
	void Loop();
	void Input();
	void Update();

private:
	AssetManager* assets;

	SDL_Rect test, test1;

	bool quitt = false;
};