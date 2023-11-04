#pragma once
#include <assert.h>
#include <vector>
#include <fstream>
#include <SDL.h>
#include "Render.h"
#include "AssetManager.h"
#include "Tileset.h"

class Game
{
public:
	Game();
	~Game();
	void Init();
	void Loop();
	void Input();
	void Update();

	void LoadMap(const char* fileName);

	void Draw();

private:
	AssetManager* assets;

	std::vector<Tileset*> map;

	bool quitt = false;
};