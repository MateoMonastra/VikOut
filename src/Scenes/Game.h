#pragma once

#pragma once
#include "ScreenManagements/Screen.h"

namespace game
{
	void InitGame(Screen currentScreen);
	void initStatesSprites();
	void GameUpdate(Screen& currentScreen);
	void PlayerInput();
	void DrawGame(Screen currentScreen);
};
