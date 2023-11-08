#pragma once
#include <vector>
#include "AssetManager.h"
#include "Tileset.h"
#include "Player.h"
#include "Widgets.h"
#include "Entity.h"
#include "EntitySpawner.h"

class Game
{
public:
	Game();
	~Game();
	void Init();
	void Loop();
	void Input();
	void Update(float dt);

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
	std::vector<Entity*> entity;
	EntitySpawner* spawner;

	int spawnTimer = 0;

	bool quitt = false;
	bool gameOver = false;
};