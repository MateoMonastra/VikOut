#include "Scenes\Menu.h"

#include "ProyectUtilities\Utilities.h"
#include "Scenes/Game.h"
#include "ProyectUtilities/Colours.h"
#include "Scenes/LevelSelector.h"

using namespace levelSelector;
using namespace game;


namespace menu
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

	static Button BackGround;
	static Button Title;
	static Button Play;
	static Button Level_Selector;
	static Button Settings;
	static Button Exit;
	static Levels Actuallevel;

	static bool MouseColision(float mousex, float mousey, Button rec);

	void InitMenu()
	{
		BackGround.sprite = slLoadTexture("assets/jungle/PNG/menu/BackGround.png");
		BackGround.TexturePosition = { 550 , 475 };
		BackGround.SpriteW = 1100;
		BackGround.SpriteH = 950;


		Title.sprite = slLoadTexture("assets/jungle/PNG/menu/Title.png");
		Title.TexturePosition = { 800 / 2 + 130 , 800 - 120 };
		Title.SpriteW = 900;
		Title.SpriteH = 600;
		Title.color = colors::WHITE;

		Play.sprite = slLoadTexture("assets/jungle/PNG/menu/play.png");
		Play.TexturePosition = { 400 - 60, 375 };
		Play.SpriteW = 140;
		Play.SpriteH = 140;


		Level_Selector.sprite = slLoadTexture("assets/jungle/PNG/menu/about.png");
		Level_Selector.TexturePosition = { 400 + 160, 375 };
		Level_Selector.SpriteW = 140;
		Level_Selector.SpriteH = 140;


		Settings.sprite = slLoadTexture("assets/jungle/PNG/menu/Setting.png");
		Settings.TexturePosition = { 400 + 380, 375 };
		Settings.SpriteW = 140;
		Settings.SpriteH = 140;


		Exit.sprite = slLoadTexture("assets/jungle/PNG/buttons/close.png");
		Exit.TexturePosition = { 400 + 160, 175 };
		Exit.SpriteW = 140;
		Exit.SpriteH = 140;


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

	void MenuUpdate(Screen& currentScreen)
	{
		int mousePositionX = slGetMouseX();
		int mousePositionY = slGetMouseY();


		if (MouseColision(mousePositionX, mousePositionY, Play))
		{

			Play.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				Actuallevel = Levels::Level1;
				InitGame(Actuallevel);
				currentScreen = Screen::Game;
			}
		}
		else if (MouseColision(mousePositionX, mousePositionY, Level_Selector))
		{
			Level_Selector.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				LevelSelectorInit();
				currentScreen = Screen::LevelSelector;
			}
		}
		else if (MouseColision(mousePositionX, mousePositionY, Settings))
		{
			Settings.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Settings;
			}
		}
		else if (MouseColision(mousePositionX, mousePositionY, Exit))
		{

			Exit.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Exit;
			}
		}
		else
		{
			BackGround.color = colors::WHITE;
			Title.color = colors::WHITE;
			Play.color = colors::WHITE;
			Level_Selector.color = colors::WHITE;
			Settings.color = colors::WHITE;
			Exit.color = colors::WHITE;
		}


	}

	void MenuDrawing()
	{
		slSetForeColor(BackGround.color.r, BackGround.color.g, BackGround.color.b, 1);
		slSprite(BackGround.sprite, BackGround.TexturePosition.x, BackGround.TexturePosition.y, BackGround.SpriteW, BackGround.SpriteH);

		slSetForeColor(Title.color.r, Title.color.g, Title.color.b, 1);
		slSprite(Title.sprite, Title.TexturePosition.x, Title.TexturePosition.y, Title.SpriteW, Title.SpriteH);

		slSetForeColor(Play.color.r, Play.color.g, Play.color.b, 1);
		slSprite(Play.sprite, Play.TexturePosition.x, Play.TexturePosition.y, Play.SpriteW, Play.SpriteH);

		slSetForeColor(Level_Selector.color.r, Level_Selector.color.g, Level_Selector.color.b, 1);
		slSprite(Level_Selector.sprite, Level_Selector.TexturePosition.x, Level_Selector.TexturePosition.y, Level_Selector.SpriteW, Level_Selector.SpriteH);

		slSetForeColor(Settings.color.r, Settings.color.g, Settings.color.b, 1);
		slSprite(Settings.sprite, Settings.TexturePosition.x, Settings.TexturePosition.y, Settings.SpriteW, Settings.SpriteH);

		slSetForeColor(Exit.color.r, Exit.color.g, Exit.color.b, 1);
		slSprite(Exit.sprite, Exit.TexturePosition.x, Exit.TexturePosition.y, Exit.SpriteW, Exit.SpriteH);

	}

}