#include "spaceship.hpp"

Spaceship::Spaceship(const Vector2 &position, int speed, const char *path)
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
		lasers.push_back(Laser(Vector2{position.x + spaceship.width / 2 - 10, position.y - 10}, -10, "../assets/projectiles/laser1.png")); // laser position adjust ...suyash
	}
}

//modifications - shrine

Vector2 Spaceship::getPosition()
{
	return position;
}

//enemy spaceship

EnemySpaceship::EnemySpaceship(const Vector2 &position, int speed, const char *path)
	: Spaceship(position, speed, path)
{
}

EnemySpaceship::~EnemySpaceship()
{
	UnloadTexture(spaceship);
}

void EnemySpaceship::move(const Vector2 &playerPostion)
{
	if (position.x > playerPostion.x)
	{
		position.x -= speed;
	}
	else if (position.x < playerPostion.x)
	{
		position.x += speed;
	}
}

void EnemySpaceship::fireLaser()
{
	if (GetTime() - lastFireTime >= 0.5)
	{
		lastFireTime = GetTime();
		lasers.push_back(Laser(Vector2{position.x + spaceship.width / 2 - 18, position.y + 20}, 8, "../assets/projectiles/laser2.png")); // laser position adjust ...suyash
	}
}
