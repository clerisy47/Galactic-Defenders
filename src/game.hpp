#pragma once
#include"spaceship.hpp"
#include "obstacles.hpp"

class Game {
	private:
		Spaceship player;
		EnemySpaceship enemy;
		std::vector<Obstacle> obstacles;
		std::vector<Obstacle> createObstacles();
		void deleteInactiveLasers();
		int level = 0;
public:
	Game();
	~Game();
	void draw();
	void update();
	void handleInput();


};