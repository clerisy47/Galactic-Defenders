#include "menu.hpp"
#include "globals.hpp"

Menu::Menu(Texture2D bg)
{
    background = bg;
}

Menu::~Menu()
{
    UnloadTexture(background);
}

void Menu::Update()
{
    if (CheckScreenPressed())
    {
        // Transition to GAME state
        Window::current = Window::GAME;
    }
}

void Menu::Draw()
{
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawText("CLICK ANYWHERE TO START", 400, Window::height - 100, 50, YELLOW);
}

bool Menu::CheckScreenPressed()
{
    return IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER);
}