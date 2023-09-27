#include "PowerUp.h"

#include <stdlib.h>
#include "ProyectUtilities/Utilities.h"

namespace powerUp
{
	bool CircleRect(Ball& ball, RecSprites& rec);

	void PowerUpsUpdate(Ball& PowerUpMultiBall, Ball& PowerDownRemoveLife, Ball& PowerUpExtraLife, bool& multiBall, bool& extraLife, bool& removeLife, int& actualBalls, RecSprites& Player, Ball& ball)
	{
		if (multiBall)
		{
			PowerUpMultiBall.y += PowerUpMultiBall.speed * PowerUpMultiBall.directionY * slGetDeltaTime();

			if (CircleRect(PowerUpMultiBall,Player))
			{
			actualBalls += 2;
			multiBall = false;
			}
		}

		if (extraLife)
		{
			PowerUpExtraLife.y += PowerUpExtraLife.speed * PowerUpExtraLife.directionY * slGetDeltaTime();
			if (CircleRect(PowerUpExtraLife, Player))
			{
				if (Player.lifes!=3)
				{
				Player.lifes++;
				}
				extraLife = false;
			}
		}
		if (removeLife)
		{
			PowerDownRemoveLife.y += PowerDownRemoveLife.speed * PowerDownRemoveLife.directionY * slGetDeltaTime();
			if (CircleRect(PowerDownRemoveLife, Player))
			{
				Player.lifes--;
				removeLife = false;
			}
		}
	}
	
	bool CircleRect(Ball& ball, RecSprites& rec)
	{

		float testX = ball.x;
		float testY = ball.y;

		float leftRec = rec.x - rec.width / 2;
		float rightRec = rec.x + rec.width / 2;
		float upRec = rec.y + rec.height / 2;
		float downRec = rec.y - rec.height / 2;

		if (ball.x < leftRec)
		{
			testX = leftRec;
		}
		else if (ball.x > rightRec)
		{
			testX = rightRec;
		}
		if (ball.y < downRec)
		{
			testY = downRec;
		}
		else if (ball.y > upRec)
		{
			testY = upRec;
		}

		float distX = ball.x - testX;
		float distY = ball.y - testY;
		float distance = sqrt((distX * distX) + (distY * distY));


		if (distance <= ball.radius)
		{
			return true;
		}
		return false;

	}
}