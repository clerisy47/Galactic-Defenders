#pragma once
#include"spaceship.hpp"

class Game {
	private:
		Spaceship player;
public:
	Game();
	~Game();
	void draw();
	void update();
	void handleInput();
	void deleteInactiveLasers();
};