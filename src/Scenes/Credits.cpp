#include "Credits.h"

#include "ProyectUtilities/Colours.h"
#include "ProyectUtilities/Utilities.h"


namespace credits
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

	void DrawRecSprite(Button Sprite);
	bool MouseColision(float mousex, float mousey, Button rec);

	Button BackGround;
	Button WoodBackGround;
	Button PaperBackGround;
	Button Credits_Leaf;
	Button Close_Button;

	void InitCredits()
	{
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

		Credits_Leaf.sprite = slLoadTexture("assets/jungle/PNG/credits/Credits_Leaf.png");
		Credits_Leaf.TexturePosition.x = 550;
		Credits_Leaf.TexturePosition.y = 730;
		Credits_Leaf.SpriteW = 600;
		Credits_Leaf.SpriteH = 220;


	}


	void CreditsUpdate(Screen& currentScene)
	{
		int mousePositionX = slGetMouseX();
		int mousePositionY = slGetMouseY();

			Close_Button.color = colors::WHITE;
		
			if (MouseColision(mousePositionX, mousePositionY, Close_Button))
			{

			Close_Button.color = colors::GRAY;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				currentScene = Screen::Menu;
			}
			}
		

	}

	void CreditsDrawing()
	{
		DrawRecSprite(BackGround);
		DrawRecSprite(WoodBackGround);
		DrawRecSprite(PaperBackGround);
		DrawRecSprite(Credits_Leaf);
		DrawRecSprite(Close_Button);

	}

	void DrawRecSprite(Button Sprite)
	{
		slSetForeColor(Sprite.color.r, Sprite.color.g, Sprite.color.b, 1);
		slSprite(Sprite.sprite, Sprite.TexturePosition.x, Sprite.TexturePosition.y, Sprite.SpriteW, Sprite.SpriteH);
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
}