#include <aliens.hpp>
#include <unordered_map>
#include <string>

Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this->position = position;
    std::unordered_map<int, std::string> alienImage = {{1, "assets/aliens/alien_1.png"}, {2, "assets/aliens/alien_2.png"}, {3, "assets/aliens/alien_3.png"}};
    alienImages[type - 1] = LoadTexture(alienImage[type].c_str());
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
    for (int i = 0; i <= 3; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::getRectangle()
{
    return {position.x, position.y, static_cast<float>(alienImages[type - 1].width), static_cast<float>(alienImages[type - 1].height)};
}

void Alien::Update(int direction)
{
    position.x += direction;
}
