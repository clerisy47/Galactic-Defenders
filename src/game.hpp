#pragma once
#include "spaceship.hpp"
#include "obstacles.hpp"
#include "aliens.hpp"

class Game
{
private:
	Spaceship player;
	EnemySpaceship enemy;
	std::vector<Obstacle> obstacles;
	std::vector<Obstacle> createObstacles();
	std::vector<Alien> createAliens();
	void deleteInactiveLasers();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShoot();
	void checkForCollisions();
	int level = 0;
	int alienDirection;
	std::vector<Alien> alienVector;
	std::vector<Laser> alienLasers;
	constexpr static float alienShootInterval = 0.35;
	float timeLastAlienFired;

public:
	Game();
	~Game();
	void draw();
	void update();
	void handleInput();
};