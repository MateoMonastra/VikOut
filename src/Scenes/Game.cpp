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
	static void CollisionCkeck(Screen& currentScreen);
	static bool PlayerColision();
	static bool RandomizeBool();
	static void PlayerInput();
	static void initStatesSprites();
	static bool MouseMenuColision(float mousex, float mousey, RecSprites rec);

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
	static RecSprites BackGround2;
	static RecSprites Lose_0Star;
	static RecSprites Lose_Leaf;
	static RecSprites Next_Button;
	static RecSprites Back_Button;
	static RecSprites Pause_Button;
	static RecSprites Menu_Button;
	static RecSprites Restart_Button;
	static RecSprites Pause_Leaf;
	static RecSprites Close_Button;
	static RecSprites Rects[REC_AMOUNT];
	static Levels level;
	static GameState state;

	void InitGame()
	{

		state = GameState::Playing;
		level = Levels::Level1;

		initStatesSprites();

		LevelGenerator();
	}

	void initStatesSprites()
	{
		Win_Leaf.sprite = slLoadTexture("assets/jungle/PNG/you_win/leaf.png");
		Win_Leaf.x = 550;
		Win_Leaf.y = 730;
		Win_Leaf.width = 600;
		Win_Leaf.height = 220;

		Win_3Star.sprite = slLoadTexture("assets/jungle/PNG/you_win/3star.png");
		Win_3Star.x = 550;
		Win_3Star.y = 530;
		Win_3Star.width = 600;
		Win_3Star.height = 220;

		Win_2Star.sprite = slLoadTexture("assets/jungle/PNG/you_win/2star.png");
		Win_2Star.x = 550;
		Win_2Star.y = 530;
		Win_2Star.width = 600;
		Win_2Star.height = 220;

		Win_1Star.sprite = slLoadTexture("assets/jungle/PNG/you_win/1star.png");
		Win_1Star.x = 550;
		Win_1Star.y = 530;
		Win_1Star.width = 600;
		Win_1Star.height = 220;

		WoodBackGround.sprite = slLoadTexture("assets/jungle/PNG/you_win/WoodBackGround.png");
		WoodBackGround.x = 550;
		WoodBackGround.y = 420;
		WoodBackGround.width = 760;
		WoodBackGround.height = 700;

		PaperBackGround.sprite = slLoadTexture("assets/jungle/PNG/you_win/PaperBackGround.png");
		PaperBackGround.x = 550;
		PaperBackGround.y = 420;
		PaperBackGround.width = 660;
		PaperBackGround.height = 600;

		BackGround2.sprite = slLoadTexture("assets/jungle/PNG/pause/BackGround.png");
		BackGround2.x = 550;
		BackGround2.y = 375;
		BackGround2.width = 1100;
		BackGround2.height = 1150;

		Lose_0Star.sprite = slLoadTexture("assets/jungle/PNG/you_lose/0star.png");
		Lose_0Star.x = 550;
		Lose_0Star.y = 530;
		Lose_0Star.width = 600;
		Lose_0Star.height = 220;

		Lose_Leaf.sprite = slLoadTexture("assets/jungle/PNG/you_lose/leaf.png");
		Lose_Leaf.x = 550;
		Lose_Leaf.y = 730;
		Lose_Leaf.width = 600;
		Lose_Leaf.height = 220;

		Next_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/next.png");
		Next_Button.x = 750;
		Next_Button.y = 250;
		Next_Button.width = 120;
		Next_Button.height = 120;

		Back_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/prew.png");
		Back_Button.x = 600;
		Back_Button.y = 90;
		Back_Button.width = 120;
		Back_Button.height = 120;

		Pause_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/pause.png");
		Pause_Button.x = 1050;
		Pause_Button.y = 905;
		Pause_Button.width = 80;
		Pause_Button.height = 80;

		Menu_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/menu.png");
		Menu_Button.x = 430;
		Menu_Button.y = 250;
		Menu_Button.width = 120;
		Menu_Button.height = 120;

		Restart_Button.sprite = slLoadTexture("assets/jungle/PNG/buttons/restart.png");
		Restart_Button.x = 680;
		Restart_Button.y = 250;
		Restart_Button.width = 120;
		Restart_Button.height = 120;

		Close_Button.sprite = slLoadTexture("assets/jungle/PNG/pause/close.png");
		Close_Button.x = 240;
		Close_Button.y = 680;
		Close_Button.width = 120;
		Close_Button.height = 120;

		Pause_Leaf.sprite = slLoadTexture("assets/jungle/PNG/pause/leaf.png");
		Pause_Leaf.x = 550;
		Pause_Leaf.y = 730;
		Pause_Leaf.width = 600;
		Pause_Leaf.height = 220;

		

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

		for (int i = 0; i < REC_AMOUNT; i++)
		{
			Rects[i].isaRock = false;
			Rects[i].isAlive = true;
		}


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
		CollisionCkeck(currentScreen);

		if (state == GameState::Playing)
		{
			BallMovement(ball);

			PlayerInput();

			state = ShouldContinue();
		}

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
			slSetForeColor(BackGround.color.r, BackGround.color.g, BackGround.color.b, 1);
			slSprite(BackGround.sprite, BackGround.x, BackGround.y, BackGround.width, BackGround.height);

			for (int i = 0; i < REC_AMOUNT; i++)
			{
				if (Rects[i].isAlive)
				{
					slSetForeColor(Rects[i].color.r, Rects[i].color.g, Rects[i].color.b, 1);
					slSprite(Rects[i].sprite, Rects[i].x, Rects[i].y, Rects[i].width, Rects[i].height);
				}
			}
			for (int i = 0; i < Player.lives; i++)
			{
				slSetForeColor(PlayerLive.color.r, PlayerLive.color.g, PlayerLive.color.b, 1);
				slSprite(PlayerLive.sprite, livesAuxX, PlayerLive.y, PlayerLive.width, PlayerLive.height);
				livesAuxX += 35;
			}
			slSetForeColor(Player.color.r, Player.color.g, Player.color.b, 1);
			slSprite(Player.sprite, Player.x, Player.y, Player.width, Player.height);

			slSetForeColor(ball.color.r, ball.color.g, ball.color.b, 1);
			slSprite(ball.sprite, ball.x, ball.y, ball.width, ball.height);

			slSetForeColor(Pause_Button.color.r, Pause_Button.color.g, Pause_Button.color.b, 1);
			slSprite(Pause_Button.sprite, Pause_Button.x, Pause_Button.y, Pause_Button.width, Pause_Button.height);

			/*slRectangleFill(ball.x, ball.y, ball.width, ball.height);

			slRectangleFill(Player.x, Player.y, Player.width, Player.height);*/

		}
		else if (state == GameState::Win)
		{
			slSetForeColor(BackGround2.color.r, BackGround2.color.g, BackGround2.color.b, 1);
			slSprite(BackGround2.sprite, BackGround2.x, BackGround2.y, BackGround2.width, BackGround2.height);

			slSetForeColor(WoodBackGround.color.r, WoodBackGround.color.g, WoodBackGround.color.b, 1);
			slSprite(WoodBackGround.sprite, WoodBackGround.x, WoodBackGround.y, WoodBackGround.width, WoodBackGround.height);

			slSetForeColor(PaperBackGround.color.r, PaperBackGround.color.g, PaperBackGround.color.b, 1);
			slSprite(PaperBackGround.sprite, PaperBackGround.x, PaperBackGround.y, PaperBackGround.width, PaperBackGround.height);

			if (Player.lives == 3)
			{
				slSetForeColor(Win_3Star.color.r, Win_3Star.color.g, Win_3Star.color.b, 1);
				slSprite(Win_3Star.sprite, Win_3Star.x, Win_3Star.y, Win_3Star.width, Win_3Star.height);
			}
			else if (Player.lives == 2)
			{
				slSetForeColor(Win_2Star.color.r, Win_2Star.color.g, Win_2Star.color.b, 1);
				slSprite(Win_2Star.sprite, Win_2Star.x, Win_2Star.y, Win_2Star.width, Win_2Star.height);
			}
			else
			{
				slSetForeColor(Win_1Star.color.r, Win_1Star.color.g, Win_1Star.color.b, 1);
				slSprite(Win_1Star.sprite, Win_1Star.x, Win_1Star.y, Win_1Star.width, Win_1Star.height);
			}
			slSetForeColor(Win_Leaf.color.r, Win_Leaf.color.g, Win_Leaf.color.b, 1);
			slSprite(Win_Leaf.sprite, Win_Leaf.x, Win_Leaf.y, Win_Leaf.width, Win_Leaf.height);

			slSetForeColor(Next_Button.color.r, Next_Button.color.g, Next_Button.color.b, 1);
			slSprite(Next_Button.sprite, Next_Button.x, Next_Button.y, Next_Button.width, Next_Button.height);

			slSetForeColor(Menu_Button.color.r, Menu_Button.color.g, Menu_Button.color.b, 1);
			slSprite(Menu_Button.sprite, Menu_Button.x, Menu_Button.y, Menu_Button.width, Menu_Button.height);
		}
		else if (state == GameState::Lose)
		{
			slSetForeColor(BackGround2.color.r, BackGround2.color.g, BackGround2.color.b, 1);
			slSprite(BackGround2.sprite, BackGround2.x, BackGround2.y, BackGround2.width, BackGround2.height);

			slSetForeColor(WoodBackGround.color.r, WoodBackGround.color.g, WoodBackGround.color.b, 1);
			slSprite(WoodBackGround.sprite, WoodBackGround.x, WoodBackGround.y, WoodBackGround.width, WoodBackGround.height);

			slSetForeColor(PaperBackGround.color.r, PaperBackGround.color.g, PaperBackGround.color.b, 1);
			slSprite(PaperBackGround.sprite, PaperBackGround.x, PaperBackGround.y, PaperBackGround.width, PaperBackGround.height);

			slSetForeColor(Lose_0Star.color.r, Lose_0Star.color.g, Lose_0Star.color.b, 1);
			slSprite(Lose_0Star.sprite, Lose_0Star.x, Lose_0Star.y, Lose_0Star.width, Lose_0Star.height);

			slSetForeColor(Lose_Leaf.color.r, Lose_Leaf.color.g, Lose_Leaf.color.b, 1);
			slSprite(Lose_Leaf.sprite, Lose_Leaf.x, Lose_Leaf.y, Lose_Leaf.width, Lose_Leaf.height);

			slSetForeColor(Menu_Button.color.r, Menu_Button.color.g, Menu_Button.color.b, 1);
			slSprite(Menu_Button.sprite, Menu_Button.x, Menu_Button.y, Menu_Button.width, Menu_Button.height);

			slSetForeColor(Restart_Button.color.r, Restart_Button.color.g, Restart_Button.color.b, 1);
			slSprite(Restart_Button.sprite, Restart_Button.x, Restart_Button.y, Restart_Button.width, Restart_Button.height);
		}
		else if (state == GameState::Paused)
		{
			slSetForeColor(BackGround2.color.r, BackGround2.color.g, BackGround2.color.b, 1);
			slSprite(BackGround2.sprite, BackGround2.x, BackGround2.y, BackGround2.width, BackGround2.height);

			slSetForeColor(WoodBackGround.color.r, WoodBackGround.color.g, WoodBackGround.color.b, 1);
			slSprite(WoodBackGround.sprite, WoodBackGround.x, WoodBackGround.y, WoodBackGround.width, WoodBackGround.height);

			slSetForeColor(PaperBackGround.color.r, PaperBackGround.color.g, PaperBackGround.color.b, 1);
			slSprite(PaperBackGround.sprite, PaperBackGround.x, PaperBackGround.y, PaperBackGround.width, PaperBackGround.height);

			slSetForeColor(Pause_Leaf.color.r, Pause_Leaf.color.g, Pause_Leaf.color.b, 1);
			slSprite(Pause_Leaf.sprite, Pause_Leaf.x, Pause_Leaf.y, Pause_Leaf.width, Pause_Leaf.height);

			slSetForeColor(Menu_Button.color.r, Menu_Button.color.g, Menu_Button.color.b, 1);
			slSprite(Menu_Button.sprite, Menu_Button.x, Menu_Button.y, Menu_Button.width, Menu_Button.height);

			slSetForeColor(Close_Button.color.r, Close_Button.color.g, Close_Button.color.b, 1);
			slSprite(Close_Button.sprite, Close_Button.x, Close_Button.y, Close_Button.width, Close_Button.height);

			slSetForeColor(Restart_Button.color.r, Restart_Button.color.g, Restart_Button.color.b, 1);
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

	void CollisionCkeck(Screen& currentScreen)
	{
		int mousePositionX = slGetMouseX();
		int mousePositionY = slGetMouseY();

		if (state == GameState::Playing)
		{
			if (ball.y < Player.y)
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
				ball.y += ball.radius / 2;
				AddBallSpeed(ball);
			}

			for (int i = 0; i < REC_AMOUNT; i++)
			{
				if (Rects[i].isAlive)
				{
					if (CircleRect(ball, Rects[i]))
					{
						if (!Rects[i].isaRock)
						{
							Rects[i].lives -= 3;
						}
					}

				}
			}

			Pause_Button.color = colors::WHITE;

			if (MouseMenuColision(mousePositionX, mousePositionY, Pause_Button))
			{
				Pause_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::Paused;
				}
			}


		}
		else if (state == GameState::Win)
		{
			Menu_Button.color = colors::WHITE;
			Next_Button.color = colors::WHITE;

			if (MouseMenuColision(mousePositionX, mousePositionY, Menu_Button))
			{
				Menu_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::ControlRules;
					currentScreen = Screen::Menu;
				}
			}
			else if (MouseMenuColision(mousePositionX, mousePositionY, Next_Button))
			{
				Next_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					if (level == Levels::Level1)
					{
						level = Levels::Level2;
					}
					else if (level == Levels::Level2)
					{
						level = Levels::Level3;
					}
					else if (level == Levels::Level3)
					{
						level = Levels::Level4;
					}
					else if (level == Levels::Level4)
					{
						level = Levels::Level5;
					}
					else if (level == Levels::Level5)
					{
						currentScreen = Screen::LevelSelector;
					}


					for (int i = 0; i < REC_AMOUNT; i++)
					{
						Rects[i].isaRock = false;
						Rects[i].isAlive = true;
					}

					state = GameState::Playing;
					LevelGenerator();
				}
			}

		}
		else if(state == GameState::Lose)
		{
			Menu_Button.color = colors::WHITE;
			Restart_Button.color = colors::WHITE;

			if (MouseMenuColision(mousePositionX, mousePositionY, Menu_Button))
			{
				Menu_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{

					state = GameState::ControlRules;
					currentScreen = Screen::Menu;
				}
			}
			else if (MouseMenuColision(mousePositionX, mousePositionY, Restart_Button))
			{
				Restart_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{

					for (int i = 0; i < REC_AMOUNT; i++)
					{
						Rects[i].isaRock = false;
						Rects[i].isAlive = true;
					}

					state = GameState::Playing;
					LevelGenerator();
				}
			}
		
		}
		else if(state == GameState::Paused)
		{
			Close_Button.color = colors::WHITE;
			Menu_Button.color = colors::WHITE;
			Restart_Button.color = colors::WHITE;

			if (MouseMenuColision(mousePositionX, mousePositionY, Close_Button))
			{
				Close_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::Playing;
				}
			}
			else if (MouseMenuColision(mousePositionX, mousePositionY, Menu_Button))
			{
				Menu_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::ControlRules;
					currentScreen = Screen::Menu;
				}
			}
			else if (MouseMenuColision(mousePositionX, mousePositionY, Restart_Button))
			{
				Restart_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{

					for (int i = 0; i < REC_AMOUNT; i++)
					{
						Rects[i].isaRock = false;
						Rects[i].isAlive = true;
					}

					state = GameState::Playing;
					LevelGenerator();
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

	bool MouseMenuColision(float mousex, float mousey, RecSprites rec)
	{
		if (state == GameState::Playing)
		{
		int bugCorrectionX = 40;
		int bugCorrectionY = 35;

		if (mousex >= rec.x - bugCorrectionX &&
			mousex <= rec.x - bugCorrectionX + rec.width &&
			mousey >= rec.y - bugCorrectionY &&
			mousey <= rec.y - bugCorrectionY + rec.height)
		{
			return true;
		}
		return false;

		}
		else
		{
			int bugCorrectionX = 60;
			int bugCorrectionY = 60;


			if (mousex >= rec.x - bugCorrectionX &&
				mousex <= rec.x - bugCorrectionX + rec.width &&
				mousey >= rec.y - bugCorrectionY &&
				mousey <= rec.y - bugCorrectionY + rec.height)
			{
				return true;
			}
			return false;
		}
	}
}
