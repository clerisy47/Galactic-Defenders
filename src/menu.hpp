#pragma once
#include "raylib.h"
class Menu
{
private:
    Texture2D background;
    // Texture2D startBtn;
    // Texture2D exitBtn;

public:
    Menu(Texture2D bg);
    ~Menu();
    void Update();
    void Draw();
    bool CheckScreenPressed();
};