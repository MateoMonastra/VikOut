#include "Scenes\Menu.h"

#include "ProyectUtilities\Utilities.h"
#include "ScreenManagements/Screen.h"
#include "ProyectUtilities/Colours.h"
#include "Scenes/Game.h"

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
		int image;
		Color Color;
	};

	static Button BackGround;
	static Button Title;
	static Button Play;
	static Button Rules;
	static Button Settings;
	static Button Exit;

	static bool MouseMenuColision(float mousex, float mousey, Button rec);

	void InitMenu()
	{
		BackGround.image = slLoadTexture("assets/jungle/PNG/menu/BackGround.png");
		BackGround.TexturePosition = { 550 , 475 };
		BackGround.SpriteW = 1100;
		BackGround.SpriteH = 950;
		BackGround.Color = colors::WHITE;
		
		
		
		Title.image = slLoadTexture("assets/jungle/PNG/menu/Title.png");
		Title.TexturePosition = { 800 /2 + 130 , 800 -120 };
		Title.SpriteW = 900;
		Title.SpriteH = 600;
		Title.Color = colors::WHITE;

		Play.image = slLoadTexture("assets/jungle/PNG/menu/play.png");
		Play.TexturePosition = { 400 - 60, 375 };
		Play.SpriteW = 140;
		Play.SpriteH = 140;
		Play.Color = colors::WHITE;

		Rules.image = slLoadTexture("assets/jungle/PNG/menu/about.png");
		Rules.TexturePosition = { 400 + 160, 375 };
		Rules.SpriteW = 140;
		Rules.SpriteH = 140;
		Rules.Color = colors::WHITE;

		Settings.image = slLoadTexture("assets/jungle/PNG/menu/Setting.png");
		Settings.TexturePosition = { 400 + 380, 375 };
		Settings.SpriteW = 140;
		Settings.SpriteH = 140;
		Settings.Color = colors::WHITE;

		Exit.image = slLoadTexture("assets/jungle/PNG/buttons/close.png");
		Exit.TexturePosition = { 400 + 160, 175 };
		Exit.SpriteW = 140;
		Exit.SpriteH = 140;
		Exit.Color = colors::WHITE;
		
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

	void MenuUpdate(Screen& currentScreen)
	{
		int mousePositionX = slGetMouseX();
		int mousePositionY = slGetMouseY();


		if (MouseMenuColision(mousePositionX, mousePositionY, Play))
		{
			
		Play.Color = colors::GRAY;

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Game;
				game::InitGame(currentScreen);
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Rules))
		{
			Rules.Color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::LevelSelector;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Settings))
		{
			Settings.Color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Settings;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Exit))
		{

			Exit.Color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Exit;
			}
		}
		else
		{
			BackGround.Color = colors::WHITE;
			Title.Color = colors::WHITE;
			Play.Color = colors::WHITE;
			Rules.Color = colors::WHITE;
			Settings.Color = colors::WHITE;
			Exit.Color = colors::WHITE;
		}


	}

	void MenuDrawing()
	{
	


		slSetForeColor(BackGround.Color.r, BackGround.Color.g, BackGround.Color.g, 1);
		slSprite(BackGround.image, BackGround.TexturePosition.x, BackGround.TexturePosition.y, BackGround.SpriteW, BackGround.SpriteH);
		
		slSetForeColor(Title.Color.r, Title.Color.g, Title.Color.g, 1);
		slSprite(Title.image,Title.TexturePosition.x, Title.TexturePosition.y,Title.SpriteW,Title.SpriteH);
		
		slSetForeColor(Play.Color.r, Play.Color.g, Play.Color.g, 1);
		slSprite(Play.image, Play.TexturePosition.x, Play.TexturePosition.y, Play.SpriteW, Play.SpriteH);
		
		slSetForeColor(Rules.Color.r, Rules.Color.g, Rules.Color.g, 1);
		slSprite(Rules.image, Rules.TexturePosition.x, Rules.TexturePosition.y, Rules.SpriteW, Rules.SpriteH);
		
		slSetForeColor(Settings.Color.r, Settings.Color.g, Settings.Color.g, 1);
		slSprite(Settings.image, Settings.TexturePosition.x, Settings.TexturePosition.y, Settings.SpriteW, Settings.SpriteH);
		
		slSetForeColor(Exit.Color.r, Exit.Color.g, Exit.Color.g, 1);
		slSprite(Exit.image, Exit.TexturePosition.x, Exit.TexturePosition.y, Exit.SpriteW, Exit.SpriteH);


		
	}

}