#include <iostream>
#include <raylib.h>
#include "game.h"

namespace Window
{
	const int width = 1440;
	const int height = 900;
}

int main()
{

	InitWindow(Window::width, Window::height, "Galactic Defenders");
	Texture2D background = LoadTexture("../assets/background/background2.png");
	SetTargetFPS(60);

	Game game;

	while (WindowShouldClose() == false)
	{
		game.handleInput();

		game.update();

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(background, 0, 0, WHITE);
		game.draw();

		EndDrawing();
	}

	return 0;
}