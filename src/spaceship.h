#pragma once

#include <raylib.h>
#include "laser.h"
#include <vector>

class Spaceship
{
private:
	Vector2 position;
	int speed;
	Texture2D spaceship;
	void limitMovement();
	double lastFireTime;

public:
	Spaceship();
	~Spaceship();
	void draw();
	void moveLeft();
	void moveRight();
	void fireLaser();
	std::vector<Laser> lasers;
};