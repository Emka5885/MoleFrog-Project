#pragma once
#include <assert.h>
#include <vector>
#include <fstream>
#include <SDL.h>
#include "Render.h"
#include "AssetManager.h"
#include "Tileset.h"
#include "Player.h"
#include "Widgets.h"

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

	void PlayerFall();

	bool Collision(Object& a, Object& b);
	bool CollisionWithGround(Player& p, Tileset& g);

private:
	AssetManager* assets;

	Widgets* widgets;
	Player* player;

	std::vector<Tileset*> map;
	std::vector<Tileset*> mounds;

	bool quitt = false;
	bool gameOver = false;
};