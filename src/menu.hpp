#pragma once
#include "raylib.h"
#include "button.hpp"
class Menu
{
private:
    Texture2D background;
    Button startButton;
    Button exitButton;
public:
    Menu(Texture2D bg);
    ~Menu();
    void Update();
    void Draw();
};