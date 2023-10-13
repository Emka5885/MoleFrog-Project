#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	float dt = (float)(SDL_GetTicks() / 1000.f);
	float lastTime = 0.f;
	const float DESIRED_DT = 1 / 60.f; // 60 FPS

	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");

	window = SDL_CreateWindow("MoleFrog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	assert(window != nullptr && "Window could not be created!");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer != nullptr && "Renderer could not be created!");

	bool quit = false;
	SDL_Event event;
	
	while (!quit)
	{
		dt = (SDL_GetTicks() - lastTime) / 1000;

		if (dt >= DESIRED_DT)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
					quit = true;
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);


			SDL_Rect frogHead = { SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 50, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 100, 255, 50, 255);
			SDL_RenderFillRect(renderer, &frogHead);
			SDL_Rect frog = { SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2, 200, 100 };
			SDL_RenderFillRect(renderer, &frog);

			SDL_Rect moleHead = { SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 50, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			SDL_RenderFillRect(renderer, &moleHead);
			SDL_Rect mole = { SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2, 200, 100 };
			SDL_RenderFillRect(renderer, &mole);


			SDL_RenderPresent(renderer);
			lastTime = (float)SDL_GetTicks();
		}
	}

	
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}