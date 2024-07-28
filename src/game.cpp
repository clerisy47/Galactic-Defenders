#include "game.hpp"
#include <iostream>
#include <fstream>

// added player via constructor - shrine
// note - speed of player must be some multiple of enemy i.e 5*2 = 10 pixel reasons.
Game::Game()
	: player(Vector2{static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() - 100)}, 10, "../assets/spaceships/player/tiny_ship13.png", "../assets/sounds/laser.ogg"),
	  enemy(Vector2{static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() * 1 / 5)}, 5, "../assets/spaceships/enemy/enemyship2.png", "../assets/sounds/enemylaser.ogg")
{
	InitLevelOne();
	laserSpaceshipCollisionSound = LoadSound("../assets/sounds/explosion.ogg");
}

Game::~Game()
{
	Alien::UnloadImages();
	UnloadSound(laserSpaceshipCollisionSound);
}

void Game::Draw()
{
	player.Draw();
	// enemy.Draw();
	if (level == 2)
	{
		enemy.Draw();
	}

	for (auto &laser : player.lasers)
	{
		laser.Draw();
	}

	if (level == 2)
	{
		for (auto &laser : enemy.lasers)
		{
			laser.Draw();
		}
	}

	for (auto &obstacle : obstacles)
	{
		obstacle.Draw();
	}
	for (auto &alien : alienVector)
	{
		alien.Draw();
	}
	for (auto &laser : alienLasers)
	{
		laser.Draw();
	}
}

void Game::HandleInput()
{
	if (!run)
	{
		if (IsKeyDown(KEY_ENTER))
		{
			Reset();
			InitLevelOne();
		}

		return;
	}
	if (IsKeyDown(KEY_LEFT))
	{
		player.MoveLeft();
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		player.MoveRight();
	}
	else if (IsKeyDown(KEY_SPACE))
	{
		player.FireLaser();
	}
}

void Game::Update()
{
	if (!run)
	{
		return;
	}
	for (auto &laser : player.lasers)
	{
		laser.Move();
	}
	MoveAliens();
	AlienShoot();
	for (auto &laser : alienLasers)
	{
		laser.Move();
	}
	DeleteInactiveLasers();

	CheckForCollisions();

	if (alienVector.empty() && level == 1)
	{
		TransitionLevelTwo();
	}

	// Enemy movement and firing - shrine
	if (level == 2)
	{
		enemy.Move(player.GetPosition());
		enemy.FireLaser();
		for (auto &laser : enemy.lasers)
		{
			laser.Move();
		}
	}
}

std::vector<Obstacle> Game::CreateObstacles()
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

std::vector<Alien> Game::CreateAliens()
{
	int row = 5, column = 20, cellSize = 55;
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

void Game::DeleteInactiveLasers()
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

	for (auto it = enemy.lasers.begin(); it != enemy.lasers.end();)
	{
		if (!it->active)
		{
			it = enemy.lasers.erase(it);
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
	if (currentTime - timeLastAlienFired >= AlienShootInterval && !alienVector.empty())
	{
		Alien &alien = alienVector[GetRandomValue(0, alienVector.size() - 1)];
		alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2,
									 alien.position.y + alien.alienImages[alien.type - 1].height},
									6, "../assets/projectiles/laser3.png")); // alien laser changed - shrine
		timeLastAlienFired = GetTime();
	}
}

void Game::CheckForCollisions()
{
	// Spaceship Lsers
	for (auto &laser : player.lasers)
	{

		auto it = alienVector.begin();
		while (it != alienVector.end())
		{
			if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
			{
				it = alienVector.erase(it);
				laser.active = false;
				if (it->type == 1)
				{
					score += 100;
				}
				else if (it->type == 2)
				{
					score += 200;
				}
				else if (it->type == 3)
				{
					score += 300;
				}
				checkHighScore();
			}
			else
			{
				++it;
			}
		}
		for (auto &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();

			while (it != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
				{
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else
				{
					++it;
				}
			}
		}
		if (CheckCollisionRecs(laser.GetRectangle(), enemy.GetRectangle()))
		{
			enemyLives--;
			if (enemyLives == 0)
			{
				GameOver();
			}
		}
	}

	// Alien lasers
	for (auto &laser : alienLasers)
	{

		if (CheckCollisionRecs(laser.GetRectangle(), player.GetRectangle()))
		{

			laser.active = false;
			lives--;
			PlaySound(laserSpaceshipCollisionSound);
			if (lives == 0)
			{
				GameOver();
			}
		}

		for (auto &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();

			while (it != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
				{
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else
				{
					++it;
				}
			}
		}
	}
	for (auto &alien : alienVector)
	{
		if (CheckCollisionRecs(alien.GetRectangle(), player.GetRectangle()))
		{
			GameOver();
		}
	}
	for (auto &laser : enemy.lasers)
	{

		if (CheckCollisionRecs(laser.GetRectangle(), player.GetRectangle()))
		{

			laser.active = false;
			lives--;
			PlaySound(laserSpaceshipCollisionSound);
			if (lives == 0)
			{

				GameOver();
			}
		}

		for (auto &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();

			while (it != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
				{
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else
				{
					++it;
				}
			}
		}
	}
}

void Game::GameOver()
{
	run = false;
	enemy.SetPosition(Vector2{-100.0f, -100.0f});
	player.lasers.clear();
	enemy.lasers.clear();
}

void Game::checkHighScore()
{
	if (score > highScore)
	{
		highScore = score;
		saveHighScore(highScore);
	}
}

void Game::saveHighScore(int highScore)
{
	std::ofstream highScoreFile("../data/high_score.txt");
	if (highScoreFile.is_open())
	{
		highScoreFile << highScore;
		highScoreFile.close();
	}
	else
	{
		std::cerr << "Failed to save High Score." << std::endl;
	}
}

int Game::loadHighScore()
{
	int loadedHighscore = 0;
	std::ifstream highScoreFile("../data/high_score.txt");
	if (highScoreFile.is_open())
	{
		highScoreFile >> loadedHighscore;
		highScoreFile.close();
	}
	else
	{
		std::cerr << "Failed to load High Score." << std::endl;
	}
	return loadedHighscore;
}

void Game::Reset()
{
	player.Reset();
	alienVector.clear();
	alienLasers.clear();
	obstacles.clear();
}

void Game::InitLevelOne()
{
	obstacles = CreateObstacles();
	alienVector = CreateAliens();
	alienDirection = 1;
	timeLastAlienFired = 0.0;
	lives = 3;
	enemyLives = INT32_MAX;
	score = 0;
	highScore = loadHighScore();
	run = true;
	level = 1;
}

void Game::TransitionLevelTwo()
{
	level++;
	lives = 3;
	enemyLives = 5;
	player.lasers.clear();
	alienLasers.clear();
}