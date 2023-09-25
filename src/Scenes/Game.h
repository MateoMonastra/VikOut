#pragma once

#include "ScreenManagements/Screen.h"
#include "Scenes/LevelSelector.h"

using namespace levelSelector;

namespace game
{
	void InitGame(Levels Actuallevel);
	void GameUpdate(Screen& currentScreen);
	void DrawGame(Screen currentScreen);
};
