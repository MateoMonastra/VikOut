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

	static bool MouseColision(float mousex, float mousey, Button rec);
	void DrawSprite(Button Sprite);

	Button Level1_Button;
	Button Level2_Button;
	Button Level3_Button;
	Button Level4_Button;
	Button Level5_Button;
	Button BackGround;
	Button WoodBackGround;
	Button PaperBackGround;
	Button LevelSelector_Leaf;
	Button Close_Button;
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

		Close_Button.sprite = slLoadTexture("assets/jungle/PNG/pause/close.png");
		Close_Button.TexturePosition.x = 200;
		Close_Button.TexturePosition.y = 700;
		Close_Button.SpriteW = 140;
		Close_Button.SpriteH = 140;

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


		if (MouseColision(mousePositionX, mousePositionY, Level1_Button))
		{

			Level1_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level1;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseColision(mousePositionX, mousePositionY, Level2_Button))
		{
			Level2_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level2;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseColision(mousePositionX, mousePositionY, Level3_Button))
		{
			Level3_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level3;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseColision(mousePositionX, mousePositionY, Level4_Button))
		{

			Level4_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level4;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseColision(mousePositionX, mousePositionY, Level5_Button))
		{

			Level5_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level5;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseColision(mousePositionX, mousePositionY, Close_Button))
		{

			Close_Button.color = colors::GRAY;

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
			Close_Button.color = colors::WHITE;
		}

	}
	
	void LevelSelectorDraw()
	{
		
		DrawSprite(BackGround);

		DrawSprite(WoodBackGround);

		DrawSprite(PaperBackGround);

		DrawSprite(LevelSelector_Leaf);

		DrawSprite(Level1_Button);

		DrawSprite(Level2_Button);

		DrawSprite(Level3_Button);
		
		DrawSprite(Level4_Button);
		
		DrawSprite(Level5_Button);

		DrawSprite(Close_Button);

	}
	
	bool MouseColision(float mousex, float mousey, Button rec)
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

	void DrawSprite(Button Sprite)
	{
		slSetForeColor(Sprite.color.r, Sprite.color.g, Sprite.color.b, 1);
		slSprite(Sprite.sprite, Sprite.TexturePosition.x, Sprite.TexturePosition.y, Sprite.SpriteW, Sprite.SpriteH);
	}
}