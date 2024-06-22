#include "spaceship.hpp"

Spaceship::Spaceship(const Vector2& position, int speed, const char* path)
    : position(position), speed(speed), lastFireTime(0.0)
{
    spaceship = LoadTexture(path);
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
	if (position.x <= 10)
		position.x = 10;
	if (position.x >= GetScreenWidth() - spaceship.width - 10)
		position.x = GetScreenWidth() - spaceship.width - 10;
}

void Spaceship::fireLaser()
{
	if (GetTime() - lastFireTime >= 0.2)
	{
		lastFireTime = GetTime();
		lasers.push_back(Laser(Vector2{position.x + spaceship.width / 2 - 5, position.y - 10}, -10));
	}
}