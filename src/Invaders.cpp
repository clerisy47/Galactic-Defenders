#include<iostream>
#include <raylib.h>
#include"game.h"

using  namespace std;

namespace Window
{
	const int width = 1440;
	const int height = 900;
}

int main() {

	InitWindow(Window::width, Window::height, "Space Invaders");
	Texture2D background = LoadTexture("../Graphics/Background/background2.png");
	SetTargetFPS(60); // Set the frames per second to 60

	Game game;

	while(WindowShouldClose() == false)
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