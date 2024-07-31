#pragma once

#include <raylib.h>
#include "laser.hpp"
#include <vector>
#include <string>

class Spaceship
{
protected:
	Vector2 position;
	int speed;
	Texture2D spaceship;
	void LimitMovement();
	double lastFireTime;
	Sound laserSound; 
public:
	Spaceship(const Vector2 &position, int speed, const char *path, const char *soundpath); 
	~Spaceship();
	void Draw();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	Rectangle GetRectangle();
	Vector2 GetPosition();
	void Reset();
	std::vector<Laser> lasers;
	void SetPosition(Vector2 newPos);

};

class EnemySpaceship : public Spaceship
{

public:
	EnemySpaceship(const Vector2 &position, int speed, const char *path, const char *soundpath);
	~EnemySpaceship();
	void Move(const Vector2 &playerPosition);
	void FireLaser();
	void SetPosition(Vector2 newPos);

};