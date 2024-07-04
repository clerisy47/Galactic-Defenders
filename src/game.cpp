#include "game.hpp"
#include <iostream>

// added player via constructor - shrine
// note - speed of player must be some multiple of enemy i.e 5*2 = 10 pixel reasons.
Game::Game()
	: player(Vector2{static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() - 100)}, 10, "../assets/spaceships/player/tiny_ship13.png", "../assets/sounds/laser.ogg"),
	  enemy(Vector2{static_cast<float>(GetScreenWidth() / 2), 20}, 5, "../assets/spaceships/enemy/enemyship2.png", "../assets/sounds/enemylaser.ogg")
{
	obstacles = createObstacles();
	alienVector = createAliens();
	alienDirection = 1;
	timeLastAlienFired = 0.0;
}

Game::~Game()
{
	Alien::UnloadImages();
}

void Game::draw()
{
	player.draw();
	// enemy.draw();

	for (auto &laser : player.lasers)
	{
		laser.draw();
	}

	// Enemy laser drawing - shrine
	// for (auto &laser : enemy.lasers)
	// {
	// 	laser.draw();
	// }
	for (auto &obstacle : obstacles)
	{
		obstacle.draw();
	}
	for (auto &alien : alienVector)
	{
		alien.Draw();
	}
	for (auto &laser : alienLasers)
	{
		laser.draw();
	}
}

void Game::handleInput()
{
	if (IsKeyDown(KEY_LEFT))
	{
		player.moveLeft();
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		player.moveRight();
	}
	else if (IsKeyDown(KEY_SPACE))
	{
		player.fireLaser();
	}
}

void Game::update()
{
	for (auto &laser : player.lasers)
	{
		laser.move();
	}
	MoveAliens();
	AlienShoot();
	for (auto &laser : alienLasers)
	{
		laser.move();
	}
	deleteInactiveLasers();

	checkForCollisions();

	// Enemy movement and firing - shrine
	// enemy.move(player.getPosition());
	// enemy.fireLaser();
	// for (auto &laser : enemy.lasers)
	// {
	// 	laser.move();
	// }
}

std::vector<Obstacle> Game::createObstacles()
{
	int obstacleWidth = Obstacle::grid[0].size() * 5;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++)
	{
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 250)}));
	}
	return obstacles;
}

std::vector<Alien> Game::createAliens()
{
	int row = 5, column = 24, cellSize = 55;
	std::vector<Alien> alienVector;
	for (int i = 0; i <= row - 1; i++)
	{
		for (int j = 0; j <= column - 1; j++)
		{
			int alienType;
			if (i == 0)
			{
				alienType = 3;
			}
			else if (i == 1)
			{
				alienType = 2;
			}
			else
			{
				alienType = 1;
			}
			float x = 60 + j * cellSize;
			float y = 120 + i * cellSize;
			alienVector.push_back(Alien(alienType, {x, y}));
		}
	}
	return alienVector;
}

void Game::deleteInactiveLasers()
{

	for (auto it = player.lasers.begin(); it != player.lasers.end();)
	{
		if (!it->active)
		{
			it = player.lasers.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = alienLasers.begin(); it != alienLasers.end();)
	{
		if (!it->active)
		{
			it = alienLasers.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Game::MoveAliens()
{
	for (auto &alien : alienVector)
	{
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
		{
			alienDirection = -1;
			MoveDownAliens(4);
		}
		if (alien.position.x < 25)
		{
			alienDirection = 1;
			MoveDownAliens(4);
		}

		alien.Update(alienDirection);
	}
}

void Game::MoveDownAliens(int distance)
{
	for (auto &alien : alienVector)
	{
		alien.position.y += distance;
	}
}

void Game::AlienShoot()
{
	double currentTime = GetTime();
	if (currentTime - timeLastAlienFired >= alienShootInterval && !alienVector.empty())
	{
		Alien &alien = alienVector[GetRandomValue(0, alienVector.size() - 1)];
		alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2,
									 alien.position.y + alien.alienImages[alien.type - 1].height},
									6, "../assets/projectiles/laser1.png"));
		timeLastAlienFired = GetTime();
	}
}

void Game::checkForCollisions()
{
	//Spaceship Lsers
	for(auto& laser: player.lasers){

		auto it = alienVector.begin();
		while (it != alienVector.end())
		{
			if(CheckCollisionRecs(it-> getRectangle(),laser.getRectangle())){
				it = alienVector.erase(it);
				laser.active = false;
			}
			else{
				++it;
			}
		}
		for(auto& obstacle: obstacles)
		{
			auto it = obstacle.blocks.begin();

		
		while (it != obstacle.blocks.end())
		{
			if(CheckCollisionRecs(it-> getRectangle(),laser.getRectangle())){
				it = obstacle.blocks.erase(it);
				laser.active = false;
			}
			else{
				++it;
			}
		}
		}
		
	}
	//Alien lasers
	for(auto& laser: alienLasers){
	
		if(CheckCollisionRecs(laser.getRectangle(), player.getRectangle())){
			
			laser.active = false;
			
		}


		for(auto& obstacle: obstacles)
		{
			auto it = obstacle.blocks.begin();

		
		while (it != obstacle.blocks.end())
		{
			if(CheckCollisionRecs(it-> getRectangle(),laser.getRectangle())){
				it = obstacle.blocks.erase(it);
				laser.active = false;
			}
			else{
				++it;
			}
		}
		}
		
	}

}
