#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::draw()
{
	player.draw();

	for (auto &laser : player.lasers)
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
}