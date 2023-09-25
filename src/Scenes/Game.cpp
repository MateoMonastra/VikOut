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
	static bool CircleRect(Ball& ball, RecSprites& Rec);
	static void CollisionCkeck();
	static bool PlayerColision();
	static bool RandomizeBool();

	
	static const int SCREEN_WIDTH = 1100;
	static const int SCREEN_HEIGHT = 950;
	static const int REC_AMOUNT = 42;
	static RecSprites Player;
	static RecSprites PlayerLive;
	static Ball ball;
	static RecSprites BackGround;
	static RecSprites Win_Leaf;
	static RecSprites Win_3Star;
	static RecSprites Win_2Star;
	static RecSprites Win_1Star;
	static RecSprites WoodBackGround;
	static RecSprites PaperBackGround;
	static RecSprites SkyBackGround;
	static RecSprites Lose_0Star;
	static RecSprites Lose_Leaf;
	static RecSprites Next_Button;
	static RecSprites Back_Button;
	static RecSprites Pause_Button;
	static RecSprites Menu_Button;
	static RecSprites Restart_Button;
	static RecSprites Rects[REC_AMOUNT];
	static Levels level;
	static GameState state;

	void InitGame(Screen currentScreen)
	{

		state = GameState::ControlRules;
		level = Levels::Level5;

		initStatesSprites();
		
		LevelGenerator();
	}

	void initStatesSprites()
	{
		Win_Leaf.sprite = slLoadTexture("assets/jungle/PNG/you_win/leaf.png");
		Win_Leaf.x = 550;
		Win_Leaf.y = 830;
		Win_Leaf.width = 600;
		Win_Leaf.height = 220;

		Win_3Star.sprite = slLoadTexture("assets/jungle/PNG/you_win/3star.png");
		Win_3Star.x = 550;
		Win_3Star.y = 630;
		Win_3Star.width = 600;
		Win_3Star.height = 220;

		Win_2Star.sprite = slLoadTexture("assets/jungle/PNG/you_win/2star.png");
		Win_2Star.x = 550;
		Win_2Star.y = 630;
		Win_2Star.width = 600;
		Win_2Star.height = 220;

		Win_1Star.sprite = slLoadTexture("assets/jungle/PNG/you_win/1star.png");
		Win_1Star.x = 550;
		Win_1Star.y = 630;
		Win_1Star.width = 600;
		Win_1Star.height = 220;

		WoodBackGround.sprite = slLoadTexture("assets/jungle/PNG/you_win/WoodBackGround.png");
		WoodBackGround.x = 550;
		WoodBackGround.y = 520;
		WoodBackGround.width = 760;
		WoodBackGround.height = 700;

		PaperBackGround.sprite = slLoadTexture("assets/jungle/PNG/you_win/PaperBackGround.png");
		PaperBackGround.x = 550;
		PaperBackGround.y = 520;
		PaperBackGround.width = 660;
		PaperBackGround.height = 600;

		SkyBackGround.sprite = slLoadTexture("assets/jungle/PNG/you_win/SkyBackGround.png");
		SkyBackGround.x = 550;
		SkyBackGround.y = 475;
		SkyBackGround.width = 1100;
		SkyBackGround.height = 950;

		Lose_0Star.sprite = slLoadTexture("assets/jungle/PNG/you_lose/0star.png");
		Lose_0Star.x = 550;
		Lose_0Star.y = 630;
		Lose_0Star.width = 600;
		Lose_0Star.height = 220;

		Lose_Leaf.sprite = slLoadTexture("assets/jungle/PNG/you_lose/leaf.png");
		Lose_Leaf.x = 550;
		Lose_Leaf.y = 830;
		Lose_Leaf.width = 600;
		Lose_Leaf.height = 220;

		Next_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/next.png");
		Next_Button.x = 750;
		Next_Button.y = 350;
		Next_Button.width = 100;
		Next_Button.height = 100;

		Back_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/prew.png");
		Back_Button.x = 600;
		Back_Button.y = 90;
		Back_Button.width = 100;
		Back_Button.height = 100;

		Pause_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/pause.png");
		Pause_Button.x = 600;
		Pause_Button.y = 90;
		Pause_Button.width = 100;
		Pause_Button.height = 100;

		Menu_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/menu.png");
		Menu_Button.x = 350;
		Menu_Button.y = 350;
		Menu_Button.width = 100;
		Menu_Button.height = 100;

		Restart_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/restart.png");
		Restart_Button.x = 350;
		Restart_Button.y = 350;
		Restart_Button.width = 100;
		Restart_Button.height = 100;

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
		else if (level == Levels::Level2)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 850;
			const int Layers = 6;
			int RecsPerLine = 7;
			int iterator = 0;
			int livesForRec = 3;

			for (int index = 0; index < Layers; index++)
			{
				for (int j = 0; j < RecsPerLine; j++)
				{

					Rects[iterator].x = RecXPosAux;
					Rects[iterator].y = RecYPosAux;
					Rects[iterator].width = 140;
					Rects[iterator].height = 50;
					Rects[iterator].lives = livesForRec;

					if (index == Layers - 1 && j != 2 && j != 4)
					{
						Rects[iterator].sprite = slLoadTexture("assets/jungle/PNG/game_sprites/Rec4.png");
						Rects[iterator].isaRock = true;
					}
					else
					{
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
		else if (level == Levels::Level3)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 850;
			const int Layers = 6;
			int RecsPerLine = 7;
			int iterator = 0;
			int livesForRec = 3;

			for (int index = 0; index < Layers; index++)
			{
				for (int j = 0; j < RecsPerLine; j++)
				{

					Rects[iterator].x = RecXPosAux;
					Rects[iterator].y = RecYPosAux;
					Rects[iterator].width = 140;
					Rects[iterator].height = 50;
					Rects[iterator].lives = livesForRec;

					if (index == Layers - 3 && j != 0 && j != 6)
					{
						Rects[iterator].sprite = slLoadTexture("assets/jungle/PNG/game_sprites/Rec4.png");
						Rects[iterator].isaRock = true;
					}
					else
					{
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
		else if (level == Levels::Level4)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 850;
			const int Layers = 6;
			int RecsPerLine = 7;
			int iterator = 0;
			int livesForRec = 3;

			for (int index = 0; index < Layers; index++)
			{
				for (int j = 0; j < RecsPerLine; j++)
				{

					Rects[iterator].x = RecXPosAux;
					Rects[iterator].y = RecYPosAux;
					Rects[iterator].width = 140;
					Rects[iterator].height = 50;
					Rects[iterator].lives = livesForRec;

					if ((index == 0) || (index == Layers - 1) && (j != 3))
					{
						Rects[iterator].sprite = slLoadTexture("assets/jungle/PNG/game_sprites/Rec4.png");
						Rects[iterator].isaRock = true;
					}
					else
					{
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
		else if (level == Levels::Level5)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 850;
			const int Layers = 6;
			int RecsPerLine = 7;
			int iterator = 0;
			int livesForRec = 3;

			for (int index = 0; index < Layers; index++)
			{
				for (int j = 0; j < RecsPerLine; j++)
				{

					Rects[iterator].x = RecXPosAux;
					Rects[iterator].y = RecYPosAux;
					Rects[iterator].width = 140;
					Rects[iterator].height = 50;
					Rects[iterator].lives = livesForRec;

					if ((index == 0) && (j == 6) || (index == 1) && (j != 5) || (index == 2) && (j == 0) || (index == 2) && (j == 6) || (index == 3) && (j != 1) || (index == 4) && (j == 0) || (index == 5) && (j != 6))
					{
						Rects[iterator].sprite = slLoadTexture("assets/jungle/PNG/game_sprites/Rec4.png");
						Rects[iterator].isaRock = true;
					}
					else
					{
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

		if (state == GameState::Playing)
		{
			double livesAuxX = 160;
			
		slSprite(BackGround.sprite, BackGround.x, BackGround.y, BackGround.width, BackGround.height);

			for (int i = 0; i < REC_AMOUNT; i++)
			{
				if (Rects[i].isAlive)
				{
				slSprite(Rects[i].sprite, Rects[i].x, Rects[i].y, Rects[i].width, Rects[i].height);
				}
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
		else if (state == GameState::Win)
		{
			slSprite(SkyBackGround.sprite, SkyBackGround.x, SkyBackGround.y, SkyBackGround.width, SkyBackGround.height);
			slSprite(WoodBackGround.sprite, WoodBackGround.x, WoodBackGround.y, WoodBackGround.width, WoodBackGround.height);
			slSprite(PaperBackGround.sprite, PaperBackGround.x, PaperBackGround.y, PaperBackGround.width, PaperBackGround.height);
			if (Player.lives==3)
			{
			slSprite(Win_3Star.sprite, Win_3Star.x, Win_3Star.y, Win_3Star.width, Win_3Star.height);
			}
			else if (Player.lives == 2)
			{
			slSprite(Win_2Star.sprite, Win_2Star.x, Win_2Star.y, Win_2Star.width, Win_2Star.height);
			}
			else
			{
			slSprite(Win_1Star.sprite, Win_1Star.x, Win_1Star.y, Win_1Star.width, Win_1Star.height);
			}
			slSprite(Win_Leaf.sprite, Win_Leaf.x, Win_Leaf.y, Win_Leaf.width, Win_Leaf.height);
			slSprite(Next_Button.sprite, Next_Button.x, Next_Button.y, Next_Button.width, Next_Button.height);
			slSprite(Menu_Button.sprite, Menu_Button.x, Menu_Button.y, Menu_Button.width, Menu_Button.height);
		}
		else if( state == GameState::Lose)
		{
			slSprite(SkyBackGround.sprite, SkyBackGround.x, SkyBackGround.y, SkyBackGround.width, SkyBackGround.height);
			slSprite(WoodBackGround.sprite, WoodBackGround.x, WoodBackGround.y, WoodBackGround.width, WoodBackGround.height);
			slSprite(PaperBackGround.sprite, PaperBackGround.x, PaperBackGround.y, PaperBackGround.width, PaperBackGround.height);			
			slSprite(Lose_0Star.sprite, Lose_0Star.x, Lose_0Star.y, Lose_0Star.width, Lose_0Star.height);
			slSprite(Lose_Leaf.sprite, Lose_Leaf.x, Lose_Leaf.y, Lose_Leaf.width, Lose_Leaf.height);
			slSprite(Next_Button.sprite, Next_Button.x, Next_Button.y, Next_Button.width, Next_Button.height);
			slSprite(Restart_Button.sprite, Restart_Button.x, Restart_Button.y, Restart_Button.width, Restart_Button.height);
		}
		
		
		}
	
	bool CircleRect(Ball& ball, RecSprites& rec)
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
			ball.directionY *= -1;
			return true;
		}
		return false;

	}

	GameState ShouldContinue()
	{
		int aliveRecCounter = 0;

		for (int i = 0; i < REC_AMOUNT; i++)
		{
			if (!Rects[i].isaRock)
			{
				if (Rects[i].lives < 1)
				{
					Rects[i].isAlive = false;
				}
				else
				{
					aliveRecCounter++;
				}
			}

		}

		if (aliveRecCounter == 0)
		{
			return GameState::Win;
		}
		if (Player.lives < 1)
		{
			return GameState::Lose;
		}



		return GameState::Playing;
	}

	void CollisionCkeck()
	{
		if (ball.y < Player.y )
		{
			Player.lives--;
			ball.y = 160;
			ball.directionY *= -1;
		}

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

		if (PlayerColision() && ball.y > Player.y + Player.height)
		{
		
			ball.y += ball.radius/2;
			AddBallSpeed(ball);
		}

		for (int i = 0; i < REC_AMOUNT; i++)
		{
			if(Rects[i].isAlive)
			{
				if (CircleRect(ball, Rects[i]))
				{
					if (!Rects[i].isaRock)
					{
					Rects[i].lives -= 1;
					}
				}
			
			}
		}


	}

	bool PlayerColision()
	{
		float testX = ball.x;
		float testY = ball.y;

		float leftRec = Player.x - Player.width / 2;
		float rightRec = Player.x + Player.width / 2;
		float upRec = Player.y + Player.height / 2;
		float downRec = Player.y - Player.height / 2;

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
			ball.y = Player.y + (Player.height / 2) + ball.radius;
			float angle = atanf((ball.x - Player.x) / (Player.height / 2 - Player.y)) + deg2rad(90);

			float maxAngle = 175.0f;
			float minAngle = 5.0f;
			
			angle = Clampf(deg2rad(minAngle), deg2rad(maxAngle), angle);

			ball.directionX = cosf(angle);
			ball.directionY = sinf(angle);

			return true;
		}
		return false;
	}

	bool RandomizeBool()
	{
		if (rand() % 2 == 1)
		{
			return true;
		}
		return false;
	}
}
