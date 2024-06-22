#include "game.h"
#include<iostream>
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
		deleteInactiveLasers();
		std::cout<<"Vector Size: "<<player.lasers.size() <<std::endl;
	}
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