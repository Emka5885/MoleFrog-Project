#include "Game.h"
#include "Definitions.h"
#include <iostream>

Game::Game()
{
	assets = new AssetManager();
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
	}
}

void Game::Update()
{
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
				tmp->SetSource(32, 32, (currentTile - 1) * 32, 0);
				tmp->SetDest((j * TILE_SIZE) + x, (i * TILE_SIZE) + y, TILE_SIZE, TILE_SIZE);
				tmp->SetID(currentTile);
				if (currentTile == 4)
				{
					tmp->SetSolid(0);
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

	SDL_RenderPresent(GetRender());
}
