#include <iostream>
#include <raylib.h>
#include "game.hpp"
#include "globals.hpp"
#include "menu.hpp"
#include <iostream>

std::string FormatWithLeadingZeros(int number, int width)
{
	std::string numberText = std::to_string(number);
	int leadingZeroes = width - numberText.size();
	return numberText = std::string(leadingZeroes, '0') + numberText;
}

int main()
{
	InitWindow(Window::width, Window::height, "Galactic Defenders");
	InitAudioDevice(); // Initialize audio device
	SetTargetFPS(60);
	SetExitKey(0); // so esc key doesn't close the window but returns to menu
	Color yellow = {243, 216, 63, 255};
	Font font = LoadFont("../assets/fonts/gamefont.ttf");

	Menu menu(LoadTexture("../assets/background/background1.png"));
	Texture2D gameBackground = LoadTexture("../assets/background/background2.png");

	Music musicMenu = LoadMusicStream("../assets/sounds/backgroundmenu.ogg");
	Music musicGame = LoadMusicStream("../assets/sounds/backgroundgame.ogg");
	Sound gameOverSound = LoadSound("../assets/sounds/youlose.ogg");

	PlayMusicStream(musicMenu); // Start playing the music

	Texture2D level1Image = LoadTexture("../assets/buttons/level1.png");
	Texture2D level2Image = LoadTexture("../assets/buttons/level2.png");
	Texture2D level3Image = LoadTexture("../assets/buttons/level3.png");
	Texture2D gameOverImage = LoadTexture("../assets/buttons/you_lose.png");
	Texture2D livesImage = LoadTexture("../assets/buttons/hp.png");

	Game *game = nullptr; // Declare a pointer to the Game object - shrine
	bool gameOverSoundPlayed = false;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		switch (Window::current)
		{
		// menu active on start
		case Window::MENU:
			menu.Update();
			menu.Draw();
			UpdateMusicStream(musicMenu);

			// If we are switching from GAME to MENU, delete the game object
			if (game != nullptr)
			{
				delete game;
				game = nullptr;
				gameOverSoundPlayed = false;
				std::cout << "Game object deleted" << std::endl;
			}
			break;

		case Window::GAME:
			// If we are switching to GAME from MENU, create the game object

			if (game == nullptr)
			{
				game = new Game();
				gameOverSound = LoadSound("../assets/sounds/youlose.ogg");

				// Transition from menu to game music
				StopMusicStream(musicMenu);
				SetMusicVolume(musicGame, 0.2f);
				PlayMusicStream(musicGame);
			}

			UpdateMusicStream(musicGame);
			game->HandleInput();
			game->Update();

			ClearBackground(RAYWHITE);
			DrawTexture(gameBackground, 0, 0, WHITE);
			if (game->run && game->level == 1)
			{
				DrawTexture(level1Image, 50, 30, WHITE);
			}
			else if (game->run && game->level == 2)
			{
				DrawTexture(level2Image, 50, 30, WHITE);
			}
			else if (game->hasWon)
			{
				game->Reset();
				DrawTextEx(font, "YOU WON", {static_cast<float>(Window::width / 2) - 400, 150}, 200, 5, WHITE);
				DrawTextEx(font, "Press ESC to return to MENU.", {static_cast<float>(Window::width / 2) - 350, 400}, 50, 2, yellow);
			}
			else
			{
				game->Reset();
				DrawTextEx(font, "GAME OVER", {static_cast<float>(Window::width / 2) - 400, 150}, 200, 5, WHITE);
				DrawTextEx(font, "Press ESC to return to MENU.", {static_cast<float>(Window::width / 2) - 350, 400}, 50, 2, yellow);

				if (!gameOverSoundPlayed)
				{

					PlaySound(gameOverSound);
					gameOverSoundPlayed = true;
				}
			}

			for (int i = 0; i <= game->lives - 1; i++)
			{
				DrawTexture(livesImage, (i + 1) * 70 + Window::width - 300, 30, WHITE);
			}
			DrawTextEx(font, "SCORE: ", {330, 30}, 34, 2, yellow);
			std::string scoreText = FormatWithLeadingZeros(game->score, 5);
			DrawTextEx(font, scoreText.c_str(), {450, 30}, 34, 2, yellow);

			DrawTextEx(font, "HIGH SCORE: ", {770, 30}, 34, 2, yellow);
			std::string highScoreText = FormatWithLeadingZeros(game->highScore, 5);
			DrawTextEx(font, highScoreText.c_str(), {970, 30}, 34, 2, yellow);

			game->Draw();

			// Check for return to MENU input
			if (IsKeyPressed(KEY_ESCAPE))
			{
				Window::current = Window::MENU; // Transition back to MENU state
				if (IsSoundPlaying(gameOverSound))
				{
					UnloadSound(gameOverSound);
				}
				// Transition from game to menu music
				StopMusicStream(musicGame);
				PlayMusicStream(musicMenu);
			}
			break;
		}

		EndDrawing();
	}

	// Cleanup
	UnloadMusicStream(musicMenu); // Unload music stream
	UnloadMusicStream(musicGame); // Unload game music stream
	UnloadSound(gameOverSound);
	CloseAudioDevice(); // Close audio device
	CloseWindow();		// Close window

	// If the game object still exists, delete it
	if (game != nullptr)
	{
		delete game;
	}

	return 0;
}
