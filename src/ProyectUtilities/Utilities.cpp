#include "ProyectUtilities/Utilities.h"

float Clampf(float min, float max, float value)
{
	if (value <= min)
	{
		return min;
	}
	else if(value >= max)
	{
		return max;
	}
	else
	{
		return value;
	}
}

static const double PI = 4.0 * atan(1.0);

float deg2rad(double deg)
{
	return deg * PI / 180.0;
}