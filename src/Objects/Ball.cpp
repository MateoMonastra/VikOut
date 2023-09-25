#include "Ball.h"

#include "ProyectUtilities/Utilities.h"

void BallMovement(Ball& ball)
{

	ball.x += ball.speed * ball.directionX * slGetDeltaTime();

	ball.y += ball.speed * ball.directionY * slGetDeltaTime();

}

void AddBallSpeed(Ball& ball)
{
	if (ball.speed <= ball.MAX_SPEED)
	{
		ball.speed += ball.SPEED_INCREMENT;
	}
}