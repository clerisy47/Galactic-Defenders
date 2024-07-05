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

void Spaceship::Draw()
{
	DrawTextureV(spaceship, position, WHITE);
}

void Spaceship::MoveLeft()
{
	position.x -= speed;
	LimitMovement();
}

void Spaceship::MoveRight()
{
	position.x += speed;
	LimitMovement();
}

void Spaceship::LimitMovement()
{
	if (position.x <= 10)
		position.x = 10;
	if (position.x >= GetScreenWidth() - spaceship.width - 10)
		position.x = GetScreenWidth() - spaceship.width - 10;
}

void Spaceship::FireLaser()
{
	if (GetTime() - lastFireTime >= 0.35)
	{
		lastFireTime = GetTime();
		lasers.push_back(Laser(Vector2{position.x + spaceship.width / 2 - 10, position.y - 10}, -10, "../assets/projectiles/laser1.png")); // laser position adjust ...suyash
		PlaySound(laserSound);																											   // added laser sound - shrine
	}
}

Rectangle Spaceship::GetRectangle()
{
	return {position.x, position.y, float(spaceship.width), float(spaceship.height)};
}

// modifications - shrine

Vector2 Spaceship::GetPosition()
{
	return position;
}

void Spaceship::Reset()
{
	position.x = (GetScreenWidth() - spaceship.width) / 2.0f;
	position.y = GetScreenHeight() - spaceship.height - 100;
	lasers.clear();
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

void EnemySpaceship::Move(const Vector2 &playerPostion)
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

void EnemySpaceship::FireLaser()
{
	if (GetTime() - lastFireTime >= 1)
	{
		lastFireTime = GetTime();
		lasers.push_back(Laser(Vector2{position.x + spaceship.width / 2 - 18, position.y + 20}, 8, "../assets/projectiles/laser2.png")); // laser position adjust ...suyash
		PlaySound(laserSound);																											 // added laser sound - shrine
	}
}
