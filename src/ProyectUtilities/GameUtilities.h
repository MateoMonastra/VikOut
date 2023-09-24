#pragma once
#include "ProyectUtilities/Utilities.h"

enum class GameState
{
	ControlRules,
	PowerUpRules,
	Playing,
	Paused,
	Win,
	Lose
};

enum class Levels
{
	Level1,
	Level2,
	Level3,
	Level4,
	Level5
};
bool RandomizeBool();
void CollisionCheck();
GameState ShouldContinue();
