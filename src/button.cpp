#include "button.hpp"

Button::Button(const char *imagePath, Vector2 position)
{
    texture = LoadTexture(imagePath);
    this->position = position;
}

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::Draw()
{
    DrawTexture(texture, position.x, position.y, WHITE);
}

bool Button::IsClicked()
{
    if (CheckCollisionPointRec(GetMousePosition(), {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)}))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return true;
        }
    }
    return false;
}