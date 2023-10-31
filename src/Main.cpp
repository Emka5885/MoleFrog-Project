#include <SDL.h>
#include <assert.h>

#include "Render.h"


int main(int argc, char* args[])
{
	float dt = (float)(SDL_GetTicks() / 1000.f);
	float lastTime = 0.f;
	const float DESIRED_DT = 1 / 60.f; // 60 FPS 

	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");

	RenderInit();

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

			DrawFrog();
			DrawMole();

			Render();

			lastTime = (float)SDL_GetTicks();

		}
	}

	RenderTerminate();
	SDL_Quit();
	return 0;
}