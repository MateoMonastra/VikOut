#pragma once
#include "ScreenManagements/Screen.h"

namespace levelSelector
{
	enum class Levels
	{
		Level1,
		Level2,
		Level3,
		Level4,
		Level5
	};

	void LevelSelectorInit();
	void LevelSelectorUpdate(Screen& currentScreen);
	void LevelSelectorDraw();
}