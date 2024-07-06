#include "menu.hpp"
#include "globals.hpp"

Menu::Menu(Texture2D bg)
    : background(bg),
      startButton("../assets/buttons/start.png", {static_cast<float>(Window::width / 2 - 205), static_cast<float>(Window::height / 2 - 100)}),
      exitButton("../assets/buttons/quit.png", {static_cast<float>(Window::width / 2 - 205), static_cast<float>(Window::height / 2 + 100)})
{
}

Menu::~Menu()
{
    UnloadTexture(background);
}

void Menu::Update()
{
    if (startButton.IsClicked())
    {
        Window::current = Window::GAME;
    }
    else if (exitButton.IsClicked())
    {
        CloseWindow();
    }
}

void Menu::Draw()
{
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTextEx(font, "GALACTIC INVADERS", {static_cast<float>(Window::width / 2 - 400), 150}, 100, 2, WHITE);
    startButton.Draw();
    exitButton.Draw();
}
