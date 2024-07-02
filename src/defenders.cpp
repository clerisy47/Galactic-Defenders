#include <iostream>
#include <raylib.h>
#include "game.hpp"

namespace Window
{
	const int width = 1440;
	const int height = 900;
}

int main()
{

	InitWindow(Window::width, Window::height, "Galactic Defenders");
	InitAudioDevice(); // audio - by shrine
	Texture2D background = LoadTexture("../assets/background/background2.png");
	SetTargetFPS(60);

	Game game;

	while (!WindowShouldClose())
	{
		game.handleInput();

		game.update();

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(background, 0, 0, WHITE);
		game.draw();

		EndDrawing();
	}

	CloseAudioDevice(); // audio closed
	CloseWindow();		// window closed

	return 0;
}