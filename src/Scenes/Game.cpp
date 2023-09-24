#include "Game.h"

#include "ProyectUtilities/Utilities.h"
#include "Objects/Rectangles.h"
#include "Objects/Ball.h"




namespace game
{

enum class GameState
{
	ControlRules,
	PowerUpRules,
	Playing,
	Paused,
	Win,
	Lose
};

enum class Levels
{
	Level1,
	Level2,
	Level3,
	Level4,
	Level5
};



static GameState ShouldContinue();
static void LevelGenerator();
static bool CircleRect(float circleX, float circleY, float radius, float rectangleX, float rectangleY, float rectangleW, float rectangleH);

static const int REC_AMOUNT = 42;
static RecSprites Player;
static RecSprites PlayerLive;
static Ball ball;
static RecSprites BackGround;
static RecSprites Rects[REC_AMOUNT];
static Levels level;
static GameState state;


void InitGame(Screen currentScreen)
{

	state = GameState::ControlRules;
	level = Levels::Level1;

	LevelGenerator();


}

void LevelGenerator()
	{
		Player.sprite = slLoadTexture("assets/jungle/PNG/game_sprites/Pad.png");
		Player.x = 600;
		Player.y = 90;
		Player.width = 260;
		Player.height = 50;
		Player.lives = 3;

		PlayerLive.sprite = slLoadTexture("assets/jungle/PNG/game_sprites/heart.png");
		PlayerLive.x = 160;
		PlayerLive.y = 920;
		PlayerLive.width = 45;
		PlayerLive.height = 45;

		BackGround.sprite = slLoadTexture("assets/jungle/PNG/game_sprites/BackGround2.png");
		BackGround.x = 550;
		BackGround.y = 475;
		BackGround.width = 1100;
		BackGround.height = 950;

		ball.x = 600;
		ball.y = 110;

		if (level == Levels::Level1)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 850;
			int Layers = 6;
			int RecsPerLine = 7;
			int iterator = 0;
			int livesForRec = 3;

			for (int i = 0; i < Layers; i++)
			{
				for (int j = 0; j < RecsPerLine; j++)
				{

					Rects[iterator].x = RecXPosAux;
					Rects[iterator].y = RecYPosAux;
					Rects[iterator].width = 140;
					Rects[iterator].height = 50;
					Rects[iterator].lives = livesForRec;

					if (Rects[iterator].lives == 3)
					{
						Rects[iterator].sprite = slLoadTexture("assets/jungle/PNG/game_sprites/Rec3.png");
					}
					else if (Rects[iterator].lives == 2)
					{
						Rects[iterator].sprite = slLoadTexture("assets/jungle/PNG/game_sprites/Rec2.png");
					}
					else
					{
						Rects[iterator].sprite = slLoadTexture("assets/jungle/PNG/game_sprites/Rec.png");
					}
					RecXPosAux += 145;
					iterator++;
				}

				if (iterator == 14 || iterator == 28)
				{
					livesForRec--;
				}

				RecXPosAux = 125;
				RecYPosAux -= 55;
			}
		}
	}

void GameUpdate(Screen& currentScreen)
{
	if (slGetKey(SL_KEY_LEFT) && Player.x > 0)
	{
		Player.x -= Player.SPEED * slGetDeltaTime();
	}
	if (slGetKey(SL_KEY_RIGHT) && Player.x < 900)
	{
		Player.x += Player.SPEED * slGetDeltaTime();
	}

	ShouldContinue();
}

void DrawGame(Screen currentScreen)
{
	if (state == GameState::Playing && level == Levels::Level1)
	{


		double livesAuxX = 160;

		slSprite(BackGround.sprite, BackGround.x, BackGround.y, BackGround.width, BackGround.height);

		for (int i = 0; i < REC_AMOUNT; i++)
		{
			slSprite(Rects[i].sprite, Rects[i].x, Rects[i].y, Rects[i].width, Rects[i].height);
		}
		for (int i = 0; i < Player.lives; i++)
		{
			slSprite(PlayerLive.sprite, livesAuxX, PlayerLive.y, PlayerLive.width, PlayerLive.height);
			livesAuxX += 35;
		}

		slSprite(Player.sprite, Player.x, Player.y, Player.width, Player.height);

	}
}


bool CircleRect(float circleX, float circleY, float radius, float rectangleX, float rectangleY, float rectangleW, float rectangleH)
{

	float testX = circleX;
	float testY = circleY;


	if (circleX < rectangleX)
	{
		testX = rectangleX;
	}
	else if (circleX > rectangleX + rectangleW)
	{
		testX = rectangleX + rectangleW;
	}
	if (circleY < rectangleY)
	{
		testY = rectangleY;
	}
	else if (circleY > rectangleY + rectangleH)
	{
		testY = rectangleY + rectangleH;
	}

	float distX = circleX - testX;
	float distY = circleY - testY;
	float distance = sqrt((distX * distX) + (distY * distY));


	if (distance <= radius)
	{
		return true;
	}
	return false;

}
GameState ShouldContinue()
{
	if (Player.lives < 1)
	{
		return GameState::Lose;
	}
	


	return GameState::Playing;
}
	
}