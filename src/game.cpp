#include "game.hpp"
#include <iostream>

// added player via constructor - shrine
// note - speed of player must be some multiple of enemy i.e 5*2 = 10 pixel reasons.
Game::Game()
	: player(Vector2{static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() - 100)}, 10, "../assets/spaceships/player/tiny_ship13.png"),
	  enemy(Vector2{static_cast<float>(GetScreenWidth() / 2), 20}, 5, "../assets/spaceships/enemy/enemyship2.png")
{
	// Other initialization if needed
}

Game::~Game()
{
}

void Game::draw()
{
	player.draw();
	enemy.draw();

	for (auto &laser : player.lasers)
	{
		laser.draw();
	}

	// Enemy laser drawing - shrine
	for (auto &laser : enemy.lasers)
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
		deleteInactiveLasers();
		std::cout << "Vector Size: " << player.lasers.size() << std::endl;
	}

	// Enemy movement and firing - shrine
	enemy.move(player.getPosition());
	enemy.fireLaser();
	for (auto &laser : enemy.lasers)
	{
		laser.move();
	}
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
}