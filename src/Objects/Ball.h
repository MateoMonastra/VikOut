#pragma once
#include "ProyectUtilities/Colours.h"

struct Ball
{
    double x;
    double y;
    double width;
    double height;
    float radius;
    float speed = 150;
    const float MAX_SPEED = 400;
    const float BASE_SPEED = 150;
    const float SPEED_INCREMENT = 60;
    float directionX = 1;
    float directionY = 1;
    int sprite;
    colors::Color color = colors::WHITE;
    bool isAlive = true;
};

void BallMovement(Ball& ball);
void AddBallSpeed(Ball& ball);