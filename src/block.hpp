#pragma once
#include <raylib.h>

class Block{
    private:
        Vector2 position;
    public:
        Block(Vector2 position);
        void draw();
        Rectangle getRectangle();
};