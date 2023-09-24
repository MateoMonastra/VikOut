#pragma once

struct Ball
{
    double x;
    double y;
    double width;
    double height;
    float radius;
    float speed = 200;
    const float MAX_SPEED = 400;
    const float BASE_SPEED = 250;
    const float SPEED_INCREMENT = 60;
    int directionX = 1;
    int directionY = 1;
    int sprite;
};

void BallMovement(Ball& ball);
void AddBallSpeed(Ball& ball);