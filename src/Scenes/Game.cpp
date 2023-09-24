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


	static int CheckColisionRecZone(Ball ball, RecSprites player);
	static GameState ShouldContinue();
	static void LevelGenerator();
	static bool CircleRect(Ball ball, RecSprites Rec);
	static void CollisionCkeck();
	static bool RandomizeBool();

	static const int SCREEN_WIDTH = 1100;
	static const int SCREEN_HEIGHT = 950;
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

		state = GameState::Playing;
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

		ball.sprite = slLoadTexture("assets/jungle/PNG/game_sprites/ball.png");
		ball.x = 600;
		ball.y = 160;
		ball.height = 60;
		ball.width = 60;
		ball.radius = 30;


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
		CollisionCkeck();

		if (state == GameState::Playing)
		{
			BallMovement(ball);

			PlayerInput();
		}

		state = ShouldContinue();
	}

	void PlayerInput()
	{
		if (state == GameState::Playing)
		{
			if (slGetKey(SL_KEY_LEFT) && Player.x > 0 + Player.width / 2)
			{
				Player.x -= Player.SPEED * slGetDeltaTime();
			}
			if (slGetKey(SL_KEY_RIGHT) && Player.x < SCREEN_WIDTH - Player.width / 2)
			{
				Player.x += Player.SPEED * slGetDeltaTime();
			}
		}

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

			slSprite(ball.sprite, ball.x, ball.y, ball.width, ball.height);

			/*slRectangleFill(ball.x, ball.y, ball.width, ball.height);

			slRectangleFill(Player.x, Player.y, Player.width, Player.height);*/

		}
	}


	bool CircleRect(Ball ball, RecSprites rec)
	{

		float testX = ball.x;
		float testY = ball.y;

		float leftRec = rec.x - rec.width / 2;
		float rightRec = rec.x + rec.width / 2;
		float upRec = rec.y + rec.height / 2;
		float downRec = rec.y - rec.height / 2;

		if (ball.x < leftRec)
		{
			testX = leftRec;
		}
		else if (ball.x > rightRec)
		{
			testX = rightRec;
		}
		if (ball.y < downRec)
		{
			testY = downRec;
		}
		else if (ball.y > upRec)
		{
			testY = upRec;
		}

		float distX = ball.x - testX;
		float distY = ball.y - testY;
		float distance = sqrt((distX * distX) + (distY * distY));


		if (distance <= ball.radius)
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


	void CollisionCkeck()
	{
		if (ball.x > SCREEN_WIDTH - ball.radius)
		{
			ball.directionX *= -1;
			ball.x = SCREEN_WIDTH - ball.radius;
		}
		if (ball.x < ball.radius)
		{
			ball.directionX *= -1;
			ball.x = ball.radius;
		}
		if (ball.y > SCREEN_HEIGHT - ball.radius)
		{
			ball.directionY *= -1;
			ball.y = SCREEN_HEIGHT - ball.radius;
		}

		if (CircleRect(ball, Player))
		{
			ball.y += ball.radius/2;
			ball.directionX *= -1;
			ball.directionY *= -1;

			AddBallSpeed(ball);


		}

	}

	bool RandomizeBool()
	{
		if (rand() % 2 == 1)
		{
			return true;
		}
		return false;
	}

	int CheckColisionRecZone(Ball ball, RecSprites player)
	{
		int rightRecPart = player.y + player.width / 3;
		int leftRecPart = player.y + (player.width / 3 * 2);

		if (ball.y < rightRecPart)
		{
			return 1;
		}
		else if (ball.y >= rightRecPart && ball.y <= leftRecPart)
		{
			return 2;
		}
		else if (ball.y > leftRecPart)
		{
			return 3;
		}
		return 0;
	}

}