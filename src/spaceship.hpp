#pragma once

#include <raylib.h>
#include "laser.hpp"
#include <vector>
#include <string>

class Spaceship
{
private:
	Vector2 position;
	int speed;
	Texture2D spaceship;
	void limitMovement();
	double lastFireTime;

public:
	Spaceship(const Vector2& position, int speed, const char* path); // Modified constructor to take position , speed  and path to texture
	~Spaceship();
	void draw();
	void moveLeft();
	void moveRight();
	void fireLaser();
	std::vector<Laser> lasers;
};