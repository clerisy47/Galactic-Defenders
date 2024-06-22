#pragma once

#include<raylib.h>

class  Laser {
private:
	Vector2 position;
	int speed;
	Texture2D image;
	bool active;
public:
	Laser(Vector2 position, int speed);
	void draw();
	void move();

};
