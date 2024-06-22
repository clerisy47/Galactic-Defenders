#include"laser.h"
#include<iostream>

Laser::Laser(Vector2 position, int speed)
{
	image = LoadTexture("Graphics/Projectiles/laser1.png");
	this->speed = speed;
	this->position = position;
	active = true;
}


void Laser::draw()
{
	if (active)
	{
		DrawTextureV(image, position, WHITE);
	}
}

void Laser::move()
{
	position.y += speed;	
	if(position.y < 0 || position.y >= GetScreenHeight())
	{
		active = false;
		std::cout << "Laser is inactive" << std::endl;

	}
}
