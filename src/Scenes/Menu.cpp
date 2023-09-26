#include "Scenes\Menu.h"

#include "ProyectUtilities\Utilities.h"
#include "Scenes/Game.h"
#include "ProyectUtilities/Colours.h"
#include "Scenes/LevelSelector.h"
#include "Scenes/Credits.h"

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
	static Button Autor_Leaf;
	static Button Credits;
	static Button Exit;
	static Levels Actuallevel;

	static bool MouseColision(float mousex, float mousey, Button rec);
	static void DrawSprite(Button Sprite);

	void InitMenu()
	{
		BackGround.sprite = slLoadTexture("assets/jungle/PNG/menu/BackGround.png");
		BackGround.TexturePosition = { 550 , 550 };
		BackGround.SpriteW = 1250;
		BackGround.SpriteH = 1100;

		Title.sprite = slLoadTexture("assets/jungle/PNG/menu/Title.png");
		Title.TexturePosition = { 800 / 2 + 130 , 800 - 120 };
		Title.SpriteW = 900;
		Title.SpriteH = 600;

		Play.sprite = slLoadTexture("assets/jungle/PNG/menu/play.png");
		Play.TexturePosition = { 400 - 60, 375 };
		Play.SpriteW = 140;
		Play.SpriteH = 140;


		Level_Selector.sprite = slLoadTexture("assets/jungle/PNG/menu/about.png");
		Level_Selector.TexturePosition = { 400 + 160, 375 };
		Level_Selector.SpriteW = 140;
		Level_Selector.SpriteH = 140;


		Credits.sprite = slLoadTexture("assets/jungle/PNG/buttons/Credits.png");
		Credits.TexturePosition = { 400 + 380, 375 };
		Credits.SpriteW = 140;
		Credits.SpriteH = 140;

		Exit.sprite = slLoadTexture("assets/jungle/PNG/buttons/close.png");
		Exit.TexturePosition = { 400 + 160, 175 };
		Exit.SpriteW = 140;
		Exit.SpriteH = 140;

		Autor_Leaf.sprite = slLoadTexture("assets/jungle/PNG/menu/Autor_Leaf.png");
		Autor_Leaf.TexturePosition = { 850 , 100 };
		Autor_Leaf.SpriteW = 500;
		Autor_Leaf.SpriteH = 250;
		
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
		else if (MouseColision(mousePositionX, mousePositionY, Credits))
		{
			Credits.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				credits::InitCredits();
				currentScreen = Screen::Credits;
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
			Credits.color = colors::WHITE;
			Exit.color = colors::WHITE;
		}


	}

	void MenuDrawing()
	{
		DrawSprite(BackGround);
		
		DrawSprite(Title);

		DrawSprite(Play);

		DrawSprite(Level_Selector);

		DrawSprite(Credits);

		DrawSprite(Exit);
		
		DrawSprite(Autor_Leaf);
	}

	void DrawSprite(Button Sprite)
	{
		slSetForeColor(Sprite.color.r, Sprite.color.g, Sprite.color.b, 1);
		slSprite(Sprite.sprite, Sprite.TexturePosition.x, Sprite.TexturePosition.y, Sprite.SpriteW, Sprite.SpriteH);
	}

}