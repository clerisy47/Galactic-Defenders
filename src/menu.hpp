#pragma once
#include "raylib.h"
#include "button.hpp"
class Menu
{
private:
    Texture2D background;
    Button startButton;
    Button exitButton;
    Font font = LoadFont("../assets/fonts/gamefont.ttf");

public:
    Menu(Texture2D bg);
    ~Menu();
    void Update();
    void Draw();
};