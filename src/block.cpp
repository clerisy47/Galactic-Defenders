#include "block.hpp"

Block::Block(Vector2 position)
{
 this->position = position;
}

void Block::Draw(){
  DrawRectangle(position.x,position.y, 5,5 ,{243,216,63,255});
}
Rectangle Block::GetRectangle()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 5;
    rect.height = 5;
    return rect;
}