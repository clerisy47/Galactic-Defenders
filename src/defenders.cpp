#include <iostream>
#include <raylib.h>
#include "game.hpp" // added global vars to globals - shrine
#include "globals.hpp"
#include "menu.hpp"

int main()
{
	InitWindow(Window::width, Window::height, "Galactic Defenders");
	InitAudioDevice(); // Initialize audio device
	SetTargetFPS(60);

	Menu menu(LoadTexture("../assets/background/background1.png"));
	Texture2D gameBackground = LoadTexture("../assets/background/background2.png");

	Music music = LoadMusicStream("../assets/sounds/background.ogg");
	PlayMusicStream(music); // Start playing the music

	Game game;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		switch (Window::current)
		{
		// menu active on start - shrine
		case Window::MENU:
			menu.Update(); // broken down menu into menu.hpp and menu.cpp - shrine
			menu.Draw();
			break;
			// once game state game will run - shrine
		case Window::GAME:
			game.HandleInput();
			game.Update();

			ClearBackground(RAYWHITE);
			DrawTexture(gameBackground, 0, 0, WHITE);
			game.Draw();

			// Check for return to MENU input
			if (IsKeyPressed(KEY_ESCAPE))
			{
				Window::current = Window::MENU; // Transition back to MENU state
				PlayMusicStream(music);			// Restart music when returning to menu
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
