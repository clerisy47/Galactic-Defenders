#include "spaceship.hpp"

Spaceship::Spaceship(const Vector2 &position, int speed, const char *path, const char *soundpath)
	: position(position), speed(speed), lastFireTime(0.0)
{
	spaceship = LoadTexture(path);
	laserSound = LoadSound(soundpath);
}

Spaceship::~Spaceship()
{
	UnloadTexture(spaceship);
	UnloadSound(laserSound);
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
	if (GetTime() - lastFireTime >= 0.35)
	{
		lastFireTime = GetTime();
		lasers.push_back(Laser(Vector2{position.x + spaceship.width / 2 - 10, position.y - 10}, -10, "../assets/projectiles/laser1.png")); // laser position adjust ...suyash
		PlaySound(laserSound);																											   // added laser sound - shrine
	}
}

Rectangle Spaceship::getRectangle()
{
    return {position.x,position.y, float(spaceship.width),float(spaceship.height)};
}

// modifications - shrine

Vector2 Spaceship::getPosition()
{
	return position;
}

// enemy spaceship

EnemySpaceship::EnemySpaceship(const Vector2 &position, int speed, const char *path, const char *soundpath)
	: Spaceship(position, speed, path, soundpath)
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
	if (GetTime() - lastFireTime >= 1)
	{
		lastFireTime = GetTime();
		lasers.push_back(Laser(Vector2{position.x + spaceship.width / 2 - 18, position.y + 20}, 8, "../assets/projectiles/laser2.png")); // laser position adjust ...suyash
		PlaySound(laserSound);																											 // added laser sound - shrine
	}
}
