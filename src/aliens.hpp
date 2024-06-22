#pragma once

#include <raylib.h>

class Alien
{
private:
public:
    Alien(int type, Vector2 position);
    void Update();
    void Draw();
    int getType();
    Texture2D image;
    int type;
    Vector2 position;
};
