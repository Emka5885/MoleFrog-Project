#pragma once

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

struct SDL_Window* GetWindow();
struct SDL_Renderer* GetRenderer();

void Render();

void DrawRect(struct SDL_Rect& size, struct SDL_Color&& color);
void DrawMole();
void DrawFrog();
