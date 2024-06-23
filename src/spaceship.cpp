#include "spaceship.hpp"

Spaceship::Spaceship()
{
	speed = 10;
	spaceship = LoadTexture("../assets/spaceships/tiny_ship13.png");
	position.x = (GetScreenWidth() - spaceship.width) / 2;
	position.y = GetScreenHeight() - spaceship.height - 30;
	lastFireTime = 0.0;
}

Spaceship::~Spaceship()
{
	UnloadTexture(spaceship);
}

void Spaceship::draw()
{
	DrawTextureV(spaceship, position, WHITE);
}

void Spaceship::moveLeft()
{
	position.x -= speed;
	limitMovement();
}

void Spaceship::moveRight()
{
	position.x += speed;
	limitMovement();
}

void Spaceship::limitMovement()
{
	if (position.x <= 20)
		position.x = 20;
	if (position.x >= GetScreenWidth() - spaceship.width - 20)
		position.x = GetScreenWidth() - spaceship.width - 20;
}

void Spaceship::fireLaser()
{
	if (GetTime() - lastFireTime >= 0.2)
	{
		lastFireTime = GetTime();
		lasers.push_back(Laser(Vector2{position.x + spaceship.width / 2 - 10, position.y - 10}, -10));
	}
}