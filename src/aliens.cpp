#include <iostream>
#include "aliens.hpp"
#include <vector>
#include <string>

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this->position = position;
    std::vector<std::string> alienImage = {"../assets/aliens/alien_1.png", "../assets/aliens/alien_2.png", "../assets/aliens/alien_3.png"};

    if (type <= 0 || type >= alienImage.size() + 1)
    {
        std::cerr << "Invalid alien type: " << type << std::endl;
        return;
    }

    Texture2D texture = LoadTexture(alienImage[type - 1].c_str());

    alienImages[type - 1] = texture;
}

void Alien::Draw()
{
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

int Alien::GetType()
{
    return type;
}

void Alien::UnloadImages()
{
    for (int i = 0; i <= 2; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::GetRectangle()
{
    return {position.x, position.y, static_cast<float>(alienImages[type - 1].width), static_cast<float>(alienImages[type - 1].height)};
}

void Alien::Update(int direction)
{
    position.x += direction;
}
