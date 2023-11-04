#include "Game.h"
#include "Definitions.h"
#include <iostream>

Game::Game()
{
	assets = new AssetManager();
	player = new Player();
	Init();
}

Game::~Game()
{
	RenderTerminate();
	IMG_Quit();
	SDL_Quit();
}

void Game::Init()
{
	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");
	int imgFlags = IMG_INIT_PNG;
	int imgInitResult = IMG_Init(imgFlags);
	assert((imgInitResult & imgFlags) == imgFlags && "SDL_Image could not initialize!");
	RenderInit();
	assets->InitTextures();
	LoadMap("res/MoleFrog.tilesets");
	player->SetDest(WIDTH / 2, HEIGHT - TILE_SIZE - 102, 63, 87);
	player->SetNewDirection(left);
	player->SetTexture(assets->GetTexture(MOLE_IMAGE));

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
			Update();
			
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
				if(!player->GetJump() && !player->GetFall())
					player->SetJump(true);
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

void Game::Update()
{
	PlayerFall();
	player->Update();
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
				tmp->SetTexture(assets->GetTexture("tilesets"));
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

	SDL_RenderCopyEx(GetRender(), player->GetTexture(), &player->GetSource(), &player->GetDest(), 0, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(GetRender());
}

void Game::PlayerFall()
{
	player->SetFall(true);
	for (int i = 0; i < map.size(); i++)
	{
		if (CollisionWithGround(player->GetDest(), map[i]->GetDest()))
		{
			if (map[i]->GetSolid())
			{
				player->SetFall(false);
			}
		}
	}
	for (int i = 0; i < mounds.size(); i++)
	{
		if (Collision(player->GetDest(), mounds[i]->GetDest()))
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

bool Game::Collision(SDL_Rect& a, SDL_Rect& b)
{
	if ((a.x < (b.x + b.w)) && ((a.x + a.w) > b.x) && (a.y < (b.y + b.h)) && ((a.y + a.h) > b.y))
	{
		return true;
	}
	return false;
}

bool Game::CollisionWithGround(SDL_Rect& p, SDL_Rect& g)
{
	if ((p.x + p.w/4 < (g.x + g.w)) && ((p.x + p.w - p.w/4) > g.x) && p.y + p.h > g.y && p.y + p.h < g.y + 12)
	{
		return true;
	}
	return false;
}
