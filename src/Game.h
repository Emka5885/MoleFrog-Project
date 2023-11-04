#pragma once
#include <assert.h>
#include <vector>
#include <fstream>
#include <SDL.h>
#include "Render.h"
#include "AssetManager.h"
#include "Tileset.h"
#include "Player.h"

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

	bool Collision(SDL_Rect& a, SDL_Rect& b);
	bool CollisionWithGround(SDL_Rect& p, SDL_Rect& g);

private:
	AssetManager* assets;

	Player* player;

	std::vector<Tileset*> map;
	std::vector<Tileset*> mounds;

	bool quitt = false;
};