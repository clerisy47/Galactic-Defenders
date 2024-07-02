#include <iostream>
#include <raylib.h>
#include "game.hpp"

namespace Window
{
	const int width = 1440;
	const int height = 900;
	enum Screen
	{
		MENU,
		GAME
	};
}

int main()
{
	InitWindow(Window::width, Window::height, "Galactic Defenders");
	InitAudioDevice(); // Initialize audio device
	SetTargetFPS(60);
	Window::Screen current = Window::MENU;

	Texture2D menuBackground = LoadTexture("../assets/background/background1.png");
	Texture2D gameBackground = LoadTexture("../assets/background/background2.png");

	Music music = LoadMusicStream("../assets/sounds/background.ogg");
	PlayMusicStream(music); // Start playing the music

	Game game;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		switch (current)
		{
		case Window::MENU:
			ClearBackground(RAYWHITE);
			DrawTexture(menuBackground, 0, 0, WHITE);
			DrawText("CLICK ANYWHERE TO START", 500, 500, 20, WHITE);
			UpdateMusicStream(music);
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER))
			{
				current = Window::GAME; // Transition to GAME state
			}
			break;

		case Window::GAME:
			game.handleInput();
			game.update();

			ClearBackground(RAYWHITE);
			DrawTexture(gameBackground, 0, 0, WHITE);
			game.draw();

			// Check for return to MENU input
			if (IsKeyPressed(KEY_ESCAPE))
			{
				current = Window::MENU; // Transition back to MENU state
				PlayMusicStream(music); // Restart music when returning to menu
			}
			break;
		}

		EndDrawing();
	}

	// Cleanup
	UnloadMusicStream(music); // Unload music stream
	CloseAudioDevice();		  // Close audio device
	CloseWindow();			  // Close window

	return 0;
}
