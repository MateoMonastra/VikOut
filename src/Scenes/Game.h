#pragma once

#pragma once
#include "ScreenManagements/Screen.h"

namespace game
{
	void InitGame(Screen currentScreen);
	void GameUpdate(Screen& currentScreen);
	void DrawGame(Screen currentScreen);
};
