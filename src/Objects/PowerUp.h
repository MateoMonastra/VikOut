#pragma once

#include "Objects/Ball.h"
#include "Objects/Rectangles.h"

namespace powerUp
{
	void PowerUpsUpdate(Ball& PowerUpMultiBall, Ball& PowerDownRemoveLife, Ball& PowerUpExtraLife, bool& multiBall, bool& extraLife, bool& removeLife, int& actualBalls, RecSprites& Player, Ball& ball);
	
}