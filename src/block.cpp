#include "block.hpp"

Block::Block(Vector2 position)
{
 this->position = position;
}

void Block::draw(){
  DrawRectangle(position.x,position.y, 5,5 ,{243,216,63,255});
};