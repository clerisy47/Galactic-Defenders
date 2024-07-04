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
	void limitMovement();
	double lastFireTime;
	Sound laserSound; // added laser sound - shrine

public:
	Spaceship(const Vector2 &position, int speed, const char *path, const char *soundpath); // Modified constructor to take position , speed  and path to texture
	~Spaceship();
	void draw();
	void moveLeft();
	void moveRight();
	void fireLaser();
	Rectangle getRectangle();
	Vector2 getPosition();
	std::vector<Laser> lasers;
};

class EnemySpaceship : public Spaceship
{

public:
	EnemySpaceship(const Vector2 &position, int speed, const char *path, const char *soundpath);
	~EnemySpaceship();
	void move(const Vector2 &playerPosition);
	void fireLaser();
};