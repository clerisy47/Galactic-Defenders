#include "game.hpp"
#include<iostream>
Game::Game()
{
	obstacles = createObstacles();
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

	for (auto& obstacle: obstacles)
	{
		obstacle.draw();
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
		std::cout<<"Vector Size: "<<player.lasers.size() <<std::endl;
	}
}

std::vector<Obstacle> Game::createObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 5;
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 250)}));
    }
    return obstacles;
}

void Game::deleteInactiveLasers()
{
    for(auto it = player.lasers.begin(); it != player.lasers.end();)
	{
        if(!it -> active) {
            it = player.lasers.erase(it);
        } else {
            ++ it;
        }
    }
}