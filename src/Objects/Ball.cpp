#include "Ball.h"

#include "ProyectUtilities/Utilities.h"

void BallMovement(Ball& ball)
{
	if (!ball.isStraight)
	{
		if (ball.toUp)
		{
			ball.y -= ball.speed * slGetDeltaTime();
		}
		else
		{
			ball.y += ball.speed * slGetDeltaTime();
		}
	}

	if (ball.toRight)
	{
		ball.x += ball.speed * slGetDeltaTime();
	}
	else
	{
		ball.x -= ball.speed * slGetDeltaTime();
	}
}

void AddBallSpeed(Ball& ball)
{
	if (ball.speed <= ball.MAX_SPEED)
	{
		ball.speed += ball.SPEED_INCREMENT * slGetDeltaTime();
	}
}