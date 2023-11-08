#include "Game.h"
#include <assert.h>
#include <fstream>
#include <SDL.h>
#include "Render.h"
#include "Definitions.h"
#include <iostream>

int score = 0;
int numberOfHearts = MAX_HEALTH;

Game::Game()
{
	assets = nullptr;
	widgets = nullptr;
	player = nullptr;
	Init();
}

Game::~Game()
{
	RenderTerminate();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::Init()
{
	//SDL Init
	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");
	//TTF Init
	result = TTF_Init();
	assert(result == 0 && "Font could not initialize!");
	//SDL_Image Init
	int imgFlags = IMG_INIT_PNG;
	int imgInitResult = IMG_Init(imgFlags);
	assert((imgInitResult & imgFlags) == imgFlags && "SDL_Image could not initialize!");
	//Render Init
	RenderInit();

	SDL_ShowCursor(false);

	assets = new AssetManager();
	widgets = new Widgets();
	player = new Player();
	spawner = new EntitySpawner();

	assets->InitTextures();
	LoadMap("res/MoleFrog.tilesets");

	player->SetDest(WIDTH / 2, HEIGHT - TILE_SIZE - 102, 63, 87);
	player->SetNewDirection(left);
	player->SetTexture(assets->GetTexture(MOLE_IMAGE));
	widgets->SetTexture(assets->GetTexture(HEART_IMAGE));
	widgets->SetFont(assets->GetFont(FONT));
	widgets->SetOutlineFont(assets->GetFont(OUTLINE_FONT));
	widgets->SetShadowFont(assets->GetFont(SHADOW_FONT));

	Loop();
}

void Game::Loop()
{
	float dt = (float)(SDL_GetTicks() / 1000.f);
	float lastTime = 0.f;
	const float DESIRED_DT = 1 / 60.f; // 60 FPS 

	while (!quitt)
	{
		dt = (SDL_GetTicks() - lastTime) / 1000;

		if (dt >= DESIRED_DT)
		{
			Input();
			Update(dt);
			
			Draw();

			lastTime = (float)SDL_GetTicks();
		}
	}
}

void Game::Input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quitt = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quitt = true;
			}
			if (!gameOver)
			{
				if (event.key.keysym.sym == SDLK_a)
				{
					player->SetNewDirection(left);
					player->SetMove(true);
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					player->SetNewDirection(right);
					player->SetMove(true);
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					player->SetMoveToMound(true);
				}
				if (event.key.keysym.sym == SDLK_w)
				{
					if (!player->GetJump() && !player->GetFall())
						player->SetJump(true);
				}
				if (event.key.keysym.sym == SDLK_e)
				{
					widgets->EraseHeart();
				}
			}
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d)
			{
				player->SetMove(false);
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				player->SetMoveToMound(false);
			}
		}
	}
}

void Game::Update(float dt)
{
	if (!gameOver)
	{
		PlayerFall();
		player->Update();

		for (int i = 0; i < entity.size(); i++)
		{
			entity[i]->Update();

			if (entity[i]->WhetherToDestroy())
			{
				entity.erase(entity.begin() + i);
			}

			if (Collision(*player, *entity[i]))
			{
				entity[i]->Collision();
				entity.erase(entity.begin() + i);
			}
		}

		if (spawnTimer <= 0)
		{
			entity.emplace_back(spawner->Spawn(assets));

			spawnTimer = SPAWN_RATE;
		}
		else
		{
			spawnTimer -= dt;
		}

		if (widgets->GetNumberOfFullHearts() != numberOfHearts)
		{
			widgets->EraseHeart();
		}

		if (widgets->GetNumberOfFullHearts() <= 0)
		{
			gameOver = true;
		}
		if (gameOver)
		{
			std::cout << "Game Over!\n";
		}
	}
}

void Game::LoadMap(const char* fileName)
{
	int currentTile, x, y, w, h;
	std::fstream file(fileName);

	if (!file.is_open())
	{
		assert(!file.is_open() && "File with tilesets could not be opened!");
		return;
	}

	file >> w;
	file >> h;
	file >> x;
	file >> y;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (file.eof())
			{
				assert(file.eof() && "Reached end of map file too soon!");
				return;
			}
			file >> currentTile;
			if (currentTile != 0)
			{
				Tileset* tmp = new Tileset;
				tmp->SetTexture(assets->GetTexture(TILESETS_IMAGE));
				tmp->SetSource((currentTile - 1) * 32, 0, 32, 32);
				tmp->SetDest((j * TILE_SIZE) + x, (i * TILE_SIZE) + y, TILE_SIZE, TILE_SIZE);
				tmp->SetID(currentTile);
				if (currentTile == 4)
				{
					tmp->SetSolid(0);
					mounds.emplace_back(tmp);
				}
				else
				{
					tmp->SetSolid(1);
				}
				map.emplace_back(tmp);
			}
		}
	}
	file.close();
}

void Game::Draw()
{
	RenderBackground();

	for (int i = 0; i < map.size(); i++)
	{
		SDL_RenderCopyEx(GetRender(), map[i]->GetTexture(), &map[i]->GetSource(), &map[i]->GetDest(), 0, NULL, SDL_FLIP_NONE);
	}

	for (int i = 0; i < entity.size(); i++)
	{
		if (entity[i]->GetInitialX() < 0)
		{
			SDL_RenderCopyEx(GetRender(), entity[i]->GetTexture(), &entity[i]->GetSource(), &entity[i]->GetDest(), 0, NULL, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopyEx(GetRender(), entity[i]->GetTexture(), &entity[i]->GetSource(), &entity[i]->GetDest(), 0, NULL, SDL_FLIP_HORIZONTAL);
		}
	}

	widgets->Draw(GetRender());

	SDL_RenderCopyEx(GetRender(), player->GetTexture(), &player->GetSource(), &player->GetDest(), 0, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(GetRender());
}

void Game::PlayerFall()
{
	player->SetFall(true);
	for (int i = 0; i < map.size(); i++)
	{
		if (CollisionWithGround(*player, *map[i]))
		{
			if (map[i]->GetSolid())
			{
				player->SetFall(false);
			}
		}
	}
	for (int i = 0; i < mounds.size(); i++)
	{
		if (Collision(*player, *mounds[i]))
		{
			if (player->GetMoveToMound())
			{
				int randomMound;
				do
				{
					randomMound = rand() % mounds.size();
				}
				while (randomMound == i);

				player->SetDestPosition(mounds[randomMound]->GetDest().x, mounds[randomMound]->GetDest().y + mounds[randomMound]->GetDest().h - player->GetDest().h);
				player->SetMoveToMound(false);
				player->SetMove(false);
				player->SetFall(true);
			}
		}
	}
}

bool Game::Collision(Object& a, Object& b)
{
	if ((a.GetDest().x < (b.GetDest().x + b.GetDest().w)) && ((a.GetDest().x + a.GetDest().w) > b.GetDest().x) && (a.GetDest().y < (b.GetDest().y + b.GetDest().h)) && ((a.GetDest().y + a.GetDest().h) > b.GetDest().y))
	{
		return true;
	}
	return false;
}

bool Game::CollisionWithGround(Player& p, Tileset& g)
{
	if ((p.GetDest().x + p.GetDest().w/4 < (g.GetDest().x + g.GetDest().w)) && ((p.GetDest().x + p.GetDest().w - p.GetDest().w/4) > g.GetDest().x) && p.GetDest().y + p.GetDest().h > g.GetDest().y && p.GetDest().y + p.GetDest().h < g.GetDest().y + 18)
	{
		return true;
	}
	return false;
}
