#include "Game.h"

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
	RenderInit();
	assets->InitTextures();

	test.x = 100;
	test.y = 100;
	test.w = 84;
	test.h = 116;
	test1.x = 0;
	test1.y = 0;
	test1.w = 420;
	test1.h = 579;

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
			RenderBackground();

			SDL_RenderCopyEx(GetRender(), assets->GetTexture("moleL"), &test1, &test, 0, NULL, SDL_FLIP_NONE);

			SDL_RenderPresent(GetRender());

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
