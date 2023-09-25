#include "LevelSelector.h"

#include "ProyectUtilities/Colours.h"
#include "ProyectUtilities/Utilities.h"
#include "Scenes/Game.h"

using namespace game;

namespace levelSelector
{
	struct Vector2
	{
		double x;
		double y;
	};
	struct Button
	{
		Vector2 TexturePosition;
		int SpriteW;
		int SpriteH;
		int sprite;
		colors::Color color = colors::WHITE;
	};

	static bool MouseMenuColision(float mousex, float mousey, Button rec);

	Button Level1_Button;
	Button Level2_Button;
	Button Level3_Button;
	Button Level4_Button;
	Button Level5_Button;
	Button BackGround;
	Button WoodBackGround;
	Button PaperBackGround;
	Button LevelSelector_Leaf;
	Button Menu_Button;
	Levels Actuallevel;

	void LevelSelectorInit()
	{
		Level1_Button.sprite = slLoadTexture("assets/jungle/PNG/level_select/Level1_Button.png");
		Level1_Button.TexturePosition.x = 350;
		Level1_Button.TexturePosition.y = 550;
		Level1_Button.SpriteW = 140;
		Level1_Button.SpriteH = 140;
		

		Level2_Button.sprite = slLoadTexture("assets/jungle/PNG/level_select/Level2_Button.png");
		Level2_Button.TexturePosition.x = 550;
		Level2_Button.TexturePosition.y = 550;
		Level2_Button.SpriteW = 140;
		Level2_Button.SpriteH = 140;
		

		Level3_Button.sprite = slLoadTexture("assets/jungle/PNG/level_select/Level3_Button.png");
		Level3_Button.TexturePosition.x = 750;
		Level3_Button.TexturePosition.y = 550;
		Level3_Button.SpriteW = 140;
		Level3_Button.SpriteH = 140;
		

		Level4_Button.sprite = slLoadTexture("assets/jungle/PNG/level_select/Level4_Button.png");
		Level4_Button.TexturePosition.x = 450;
		Level4_Button.TexturePosition.y = 350;
		Level4_Button.SpriteW = 140;
		Level4_Button.SpriteH = 140;
		
		Level5_Button.sprite = slLoadTexture("assets/jungle/PNG/level_select/Level5_Button.png");
		Level5_Button.TexturePosition.x = 650;
		Level5_Button.TexturePosition.y = 350;
		Level5_Button.SpriteW = 140;
		Level5_Button.SpriteH = 140;
		

		WoodBackGround.sprite = slLoadTexture("assets/jungle/PNG/you_win/WoodBackGround.png");
		WoodBackGround.TexturePosition.x = 550;
		WoodBackGround.TexturePosition.y = 420;
		WoodBackGround.SpriteW = 760;
		WoodBackGround.SpriteH = 700;

		PaperBackGround.sprite = slLoadTexture("assets/jungle/PNG/you_win/PaperBackGround.png");
		PaperBackGround.TexturePosition.x = 550;
		PaperBackGround.TexturePosition.y = 420;
		PaperBackGround.SpriteW = 660;
		PaperBackGround.SpriteH = 600;

		BackGround.sprite = slLoadTexture("assets/jungle/PNG/pause/BackGround.png");
		BackGround.TexturePosition.x = 550;
		BackGround.TexturePosition.y = 375;
		BackGround.SpriteW = 1100;
		BackGround.SpriteH = 1150;

		Menu_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/menu.png");
		Menu_Button.TexturePosition.x = 550;
		Menu_Button.TexturePosition.y = 150;
		Menu_Button.SpriteW = 140;
		Menu_Button.SpriteH = 140;

		LevelSelector_Leaf.sprite = slLoadTexture("assets/jungle/PNG/level_select/leaf.png");
		LevelSelector_Leaf.TexturePosition.x = 550;
		LevelSelector_Leaf.TexturePosition.y = 730;
		LevelSelector_Leaf.SpriteW = 600;
		LevelSelector_Leaf.SpriteH = 220;

	}

	void LevelSelectorUpdate(Screen& currentScreen)
	{
		int mousePositionX = slGetMouseX();
		int mousePositionY = slGetMouseY();


		if (MouseMenuColision(mousePositionX, mousePositionY, Level1_Button))
		{

			Level1_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level1;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Level2_Button))
		{
			Level2_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level2;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Level3_Button))
		{
			Level3_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level3;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Level4_Button))
		{

			Level4_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level4;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Level5_Button))
		{

			Level5_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level5;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Menu_Button))
		{

			Menu_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Menu;
			}
		}
		else
		{
			Level1_Button.color = colors::WHITE;
			Level2_Button.color = colors::WHITE;
			Level3_Button.color = colors::WHITE;
			Level4_Button.color = colors::WHITE;
			Level5_Button.color = colors::WHITE;
			Menu_Button.color = colors::WHITE;
		}

	}
	
	void LevelSelectorDraw()
	{
		slSetForeColor(BackGround.color.r, BackGround.color.g, BackGround.color.b, 1);
		slSprite(BackGround.sprite, BackGround.TexturePosition.x, BackGround.TexturePosition.y, BackGround.SpriteW, BackGround.SpriteH);

		slSetForeColor(WoodBackGround.color.r, WoodBackGround.color.g, WoodBackGround.color.b, 1);
		slSprite(WoodBackGround.sprite, WoodBackGround.TexturePosition.x, WoodBackGround.TexturePosition.y, WoodBackGround.SpriteW, WoodBackGround.SpriteH);

		slSetForeColor(PaperBackGround.color.r, PaperBackGround.color.g, PaperBackGround.color.b, 1);
		slSprite(PaperBackGround.sprite, PaperBackGround.TexturePosition.x, PaperBackGround.TexturePosition.y, PaperBackGround.SpriteW, PaperBackGround.SpriteH);

		slSetForeColor(LevelSelector_Leaf.color.r, LevelSelector_Leaf.color.g, LevelSelector_Leaf.color.b, 1);
		slSprite(LevelSelector_Leaf.sprite, LevelSelector_Leaf.TexturePosition.x, LevelSelector_Leaf.TexturePosition.y, LevelSelector_Leaf.SpriteW, LevelSelector_Leaf.SpriteH);

		slSetForeColor(Level1_Button.color.r, Level1_Button.color.g, Level1_Button.color.b, 1);
		slSprite(Level1_Button.sprite, Level1_Button.TexturePosition.x, Level1_Button.TexturePosition.y, Level1_Button.SpriteW, Level1_Button.SpriteH);

		slSetForeColor(Level2_Button.color.r, Level2_Button.color.g, Level2_Button.color.b, 1);
		slSprite(Level2_Button.sprite, Level2_Button.TexturePosition.x, Level2_Button.TexturePosition.y, Level2_Button.SpriteW, Level2_Button.SpriteH);

		slSetForeColor(Level3_Button.color.r, Level3_Button.color.g, Level3_Button.color.b, 1);
		slSprite(Level3_Button.sprite, Level3_Button.TexturePosition.x, Level3_Button.TexturePosition.y, Level3_Button.SpriteW, Level3_Button.SpriteH);

		slSetForeColor(Level4_Button.color.r, Level4_Button.color.g, Level4_Button.color.b, 1);
		slSprite(Level4_Button.sprite, Level4_Button.TexturePosition.x, Level4_Button.TexturePosition.y, Level4_Button.SpriteW, Level4_Button.SpriteH);

		slSetForeColor(Level5_Button.color.r, Level5_Button.color.g, Level5_Button.color.b, 1);
		slSprite(Level5_Button.sprite, Level5_Button.TexturePosition.x, Level5_Button.TexturePosition.y, Level5_Button.SpriteW, Level5_Button.SpriteH);

		slSetForeColor(Menu_Button.color.r, Menu_Button.color.g, Menu_Button.color.b, 1);
		slSprite(Menu_Button.sprite, Menu_Button.TexturePosition.x, Menu_Button.TexturePosition.y, Menu_Button.SpriteW, Menu_Button.SpriteH);

	}
	
	bool MouseMenuColision(float mousex, float mousey, Button rec)
	{
		int bugCorrectionX = 80;
		int bugCorrectionY = 60;

		if (mousex >= rec.TexturePosition.x - bugCorrectionX &&
			mousex <= rec.TexturePosition.x - bugCorrectionX + rec.SpriteW &&
			mousey >= rec.TexturePosition.y - bugCorrectionY &&
			mousey <= rec.TexturePosition.y - bugCorrectionY + rec.SpriteH)
		{
			return true;
		}
		return false;
	}
}