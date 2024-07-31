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
	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> CreateAliens();
	void DeleteInactiveLasers();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShoot();
	void CheckForCollisions();
	int alienDirection;
	std::vector<Alien> alienVector;
	std::vector<Laser> alienLasers;
	constexpr static float AlienShootInterval = 0.35;
	float timeLastAlienFired;
	void GameOver();
	void checkHighScore();
	void saveHighScore(int highScore);
	int loadHighScore();
	Sound laserSpaceshipCollisionSound;

public:
	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();
	bool run;
	void Reset();
	void InitLevelOne();
	void TransitionLevelTwo();
	int lives;
	int enemyLives;
	int score;
	int highScore;
	bool hasWon;
	int level;
};