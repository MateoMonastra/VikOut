#pragma once

struct RecSprites
{
	double x = {0};
	double y = {0};
	double width = {0};
	double height = {0};

	int lives = {0};
	bool havePowerUp = false;
	bool isAlive = true;
	bool isaRock = false;
	int sprite = {0};
	const float SPEED = 360;
};

