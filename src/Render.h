#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <cassert>

//struct SDL_Window* GetWindow();
//struct SDL_Renderer* GetRenderer();

void RenderInit(); 
void RenderTerminate();

void RenderBackground();

SDL_Renderer* GetRender();

void Draw();
