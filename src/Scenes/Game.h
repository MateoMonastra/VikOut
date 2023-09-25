#pragma once

#include "ScreenManagements/Screen.h"

namespace game
{
	void InitGame();
	void GameUpdate(Screen& currentScreen);
	void DrawGame(Screen currentScreen);
};
