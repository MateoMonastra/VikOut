#include "Scenes\Menu.h"

#include "ProyectUtilities\Utilities.h"
#include "Scenes/Game.h"
#include "ProyectUtilities/Colours.h"

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
		colors::Color color = colors::WHITE;
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
		
	
		Title.image = slLoadTexture("assets/jungle/PNG/menu/Title.png");
		Title.TexturePosition = { 800 /2 + 130 , 800 -120 };
		Title.SpriteW = 900;
		Title.SpriteH = 600;
		Title.color = colors::WHITE;

		Play.image = slLoadTexture("assets/jungle/PNG/menu/play.png");
		Play.TexturePosition = { 400 - 60, 375 };
		Play.SpriteW = 140;
		Play.SpriteH = 140;
		

		Rules.image = slLoadTexture("assets/jungle/PNG/menu/about.png");
		Rules.TexturePosition = { 400 + 160, 375 };
		Rules.SpriteW = 140;
		Rules.SpriteH = 140;
		

		Settings.image = slLoadTexture("assets/jungle/PNG/menu/Setting.png");
		Settings.TexturePosition = { 400 + 380, 375 };
		Settings.SpriteW = 140;
		Settings.SpriteH = 140;
		

		Exit.image = slLoadTexture("assets/jungle/PNG/buttons/close.png");
		Exit.TexturePosition = { 400 + 160, 175 };
		Exit.SpriteW = 140;
		Exit.SpriteH = 140;
		
		
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
			
		Play.color = colors::GRAY;

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				game::InitGame();
				currentScreen = Screen::Game;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Rules))
		{
			Rules.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::LevelSelector;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Settings))
		{
			Settings.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Settings;
			}
		}
		else if (MouseMenuColision(mousePositionX, mousePositionY, Exit))
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
			Rules.color = colors::WHITE;
			Settings.color = colors::WHITE;
			Exit.color = colors::WHITE;
		}


	}

	void MenuDrawing()
	{
		slSetForeColor(BackGround.color.r, BackGround.color.g, BackGround.color.b, 1);
		slSprite(BackGround.image, BackGround.TexturePosition.x, BackGround.TexturePosition.y, BackGround.SpriteW, BackGround.SpriteH);
		
		slSetForeColor(Title.color.r, Title.color.g, Title.color.b, 1);
		slSprite(Title.image,Title.TexturePosition.x, Title.TexturePosition.y,Title.SpriteW,Title.SpriteH);
		
		slSetForeColor(Play.color.r, Play.color.g, Play.color.b, 1);
		slSprite(Play.image, Play.TexturePosition.x, Play.TexturePosition.y, Play.SpriteW, Play.SpriteH);
		
		slSetForeColor(Rules.color.r, Rules.color.g, Rules.color.b, 1);
		slSprite(Rules.image, Rules.TexturePosition.x, Rules.TexturePosition.y, Rules.SpriteW, Rules.SpriteH);
		
		slSetForeColor(Settings.color.r, Settings.color.g, Settings.color.b, 1);
		slSprite(Settings.image, Settings.TexturePosition.x, Settings.TexturePosition.y, Settings.SpriteW, Settings.SpriteH);
		
		slSetForeColor(Exit.color.r, Exit.color.g, Exit.color.b, 1);
		slSprite(Exit.image, Exit.TexturePosition.x, Exit.TexturePosition.y, Exit.SpriteW, Exit.SpriteH);
	
	}

}