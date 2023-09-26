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

	static GameState ShouldContinue();
	static void LevelGenerator();
	static bool CircleRect(Ball& ball, RecSprites& Rec);
	static void CollisionCkeck(Screen& currentScreen);
	static void PlayerColision(Ball& ball);
	static bool RandomizeBool();
	static void PlayerInput();
	static void initStatesSprites();
	static bool MouseColision(float mousex, float mousey, RecSprites rec);
	static float RandomPullOut();
	static void DrawSprite(RecSprites Sprite);

	static const int SCREEN_WIDTH = 1100;
	static const int SCREEN_HEIGHT = 950;
	static const int REC_AMOUNT = 42;
	static const int MAX_BALLS = 13;
	static int actualBalls = 1;
	static float timer = 0;
	static const float TIME_FOR_FIRST_ANIMATION = 0.18f;
	static const float TIME_FOR_SECOND_ANIMATION = 0.5f;
	static Ball ball[MAX_BALLS];
	static RecSprites Player;
	static RecSprites PlayerLive;
	static RecSprites PlayerPoints;
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
	static RecSprites Play_Button;
	static RecSprites Restart_Button;
	static RecSprites Close_Button;
	static RecSprites Pause_Leaf;
	static RecSprites Control_Rules;
	static RecSprites PowerUp_Rules;
	static RecSprites Rules_Leaf;
	static RecSprites Lives_Board;
	static RecSprites Rects[REC_AMOUNT];
	static Levels Actuallevel;
	static GameState state;

	void InitGame(Levels level)
	{

		state = GameState::ControlRules;
		Actuallevel = level;


		initStatesSprites();

		LevelGenerator();

	}

	void initStatesSprites()
	{
		Win_Leaf.sprite[0] = slLoadTexture("assets/jungle/PNG/you_win/leaf.png");
		Win_Leaf.x = 550;
		Win_Leaf.y = 730;
		Win_Leaf.width = 600;
		Win_Leaf.height = 220;

		Win_3Star.sprite[0] = slLoadTexture("assets/jungle/PNG/you_win/3star.png");
		Win_3Star.x = 550;
		Win_3Star.y = 530;
		Win_3Star.width = 600;
		Win_3Star.height = 220;

		Win_2Star.sprite[0] = slLoadTexture("assets/jungle/PNG/you_win/2star.png");
		Win_2Star.x = 550;
		Win_2Star.y = 530;
		Win_2Star.width = 600;
		Win_2Star.height = 220;

		Win_1Star.sprite[0] = slLoadTexture("assets/jungle/PNG/you_win/1star.png");
		Win_1Star.x = 550;
		Win_1Star.y = 530;
		Win_1Star.width = 600;
		Win_1Star.height = 220;

		WoodBackGround.sprite[0] = slLoadTexture("assets/jungle/PNG/you_win/WoodBackGround.png");
		WoodBackGround.x = 550;
		WoodBackGround.y = 420;
		WoodBackGround.width = 760;
		WoodBackGround.height = 700;

		PaperBackGround.sprite[0] = slLoadTexture("assets/jungle/PNG/you_win/PaperBackGround.png");
		PaperBackGround.x = 550;
		PaperBackGround.y = 420;
		PaperBackGround.width = 660;
		PaperBackGround.height = 600;

		BackGround2.sprite[0] = slLoadTexture("assets/jungle/PNG/pause/BackGround.png");
		BackGround2.x = 550;
		BackGround2.y = 375;
		BackGround2.width = 1100;
		BackGround2.height = 1150;

		Lose_0Star.sprite[0] = slLoadTexture("assets/jungle/PNG/you_lose/0star.png");
		Lose_0Star.x = 550;
		Lose_0Star.y = 530;
		Lose_0Star.width = 600;
		Lose_0Star.height = 220;

		Lose_Leaf.sprite[0] = slLoadTexture("assets/jungle/PNG/you_lose/leaf.png");
		Lose_Leaf.x = 550;
		Lose_Leaf.y = 730;
		Lose_Leaf.width = 600;
		Lose_Leaf.height = 220;

		Next_Button.sprite[0] = slLoadTexture("assets/jungle/PNG/buttons/next.png");
		Next_Button.x = 750;
		Next_Button.y = 250;
		Next_Button.width = 120;
		Next_Button.height = 120;

		Back_Button.sprite[0] = slLoadTexture("assets/jungle/PNG/buttons/prew.png");
		Back_Button.x = 350;
		Back_Button.y = 250;
		Back_Button.width = 120;
		Back_Button.height = 120;

		Pause_Button.sprite[0] = slLoadTexture("assets/jungle/PNG/buttons/pause.png");
		Pause_Button.x = 1050;
		Pause_Button.y = 905;
		Pause_Button.width = 80;
		Pause_Button.height = 80;

		Menu_Button.sprite[0] = slLoadTexture("assets/jungle/PNG/buttons/menu.png");
		Menu_Button.x = 430;
		Menu_Button.y = 250;
		Menu_Button.width = 120;
		Menu_Button.height = 120;
		
		Play_Button.sprite[0] = slLoadTexture("assets/jungle/PNG/buttons/play.png");
		Play_Button.x = 550;
		Play_Button.y = 250;
		Play_Button.width = 120;
		Play_Button.height = 120;

		Restart_Button.sprite[0] = slLoadTexture("assets/jungle/PNG/buttons/restart.png");
		Restart_Button.x = 680;
		Restart_Button.y = 250;
		Restart_Button.width = 120;
		Restart_Button.height = 120;

		Close_Button.sprite[0] = slLoadTexture("assets/jungle/PNG/pause/close.png");
		Close_Button.x = 240;
		Close_Button.y = 680;
		Close_Button.width = 120;
		Close_Button.height = 120;

		Pause_Leaf.sprite[0] = slLoadTexture("assets/jungle/PNG/pause/leaf.png");
		Pause_Leaf.x = 550;
		Pause_Leaf.y = 730;
		Pause_Leaf.width = 600;
		Pause_Leaf.height = 220;

		PlayerPoints.sprite[0] = slLoadTexture("assets/jungle/PNG/buttons/pause.png");
		PlayerPoints.x = 1050;
		PlayerPoints.y = 905;
		PlayerPoints.width = 80;
		PlayerPoints.height = 80;

		Control_Rules.sprite[0] = slLoadTexture("assets/jungle/PNG/rules/ControlRules.png");
		Control_Rules.x = 550;
		Control_Rules.y = 420;
		Control_Rules.width = 660;
		Control_Rules.height = 600;

		PowerUp_Rules.sprite[0] = slLoadTexture("assets/jungle/PNG/rules/PowerUpRules.png");
		PowerUp_Rules.x = 550;
		PowerUp_Rules.y = 420;
		PowerUp_Rules.width = 660;
		PowerUp_Rules.height = 600;

		Rules_Leaf.sprite[0] = slLoadTexture("assets/jungle/PNG/rules/leaf.png");
		Rules_Leaf.x = 550;
		Rules_Leaf.y = 730;
		Rules_Leaf.width = 600;
		Rules_Leaf.height = 220;

		Lives_Board.sprite[0] = slLoadTexture("assets/jungle/PNG/game_sprites/LivesBoard.png");
		Lives_Board.x = 150;
		Lives_Board.y = 910;
		Lives_Board.width = 280;
		Lives_Board.height = 80;

	}

	void LevelGenerator()
	{
		Player.sprite[0] = slLoadTexture("assets/jungle/PNG/game_sprites/Rest.png");
		Player.sprite[1] = slLoadTexture("assets/jungle/PNG/game_sprites/Hold.png");
		Player.sprite[2] = slLoadTexture("assets/jungle/PNG/game_sprites/Release.png");
		Player.x = 600;
		Player.y = 90;
		Player.width = 260;
		Player.height = 30;
		Player.lives = 3;

		PlayerLive.sprite[0] = slLoadTexture("assets/jungle/PNG/game_sprites/heart.png");
		PlayerLive.x = 160;
		PlayerLive.y = 910;
		PlayerLive.width = 65;
		PlayerLive.height = 65;

		BackGround.sprite[0] = slLoadTexture("assets/jungle/PNG/game_sprites/BackGround2.png");
		BackGround.x = 550;
		BackGround.y = 475;
		BackGround.width = 1100;
		BackGround.height = 950;

		for (int i = 0; i < MAX_BALLS; i++)
		{
		ball[i].sprite = slLoadTexture("assets/jungle/PNG/game_sprites/ball.png");
		ball[i].x = 600;
		ball[i].y = 160;
		ball[i].height = 50;
		ball[i].width = 50;
		ball[i].radius = 25;
		ball[i].directionX = RandomPullOut();
		}

		for (int i = 0; i < REC_AMOUNT; i++)
		{
			Rects[i].isaRock = false;
			Rects[i].isAlive = true;
		}

		int brick0 = slLoadTexture("assets/jungle/PNG/game_sprites/Rec3.png");
		int brick1 = slLoadTexture("assets/jungle/PNG/game_sprites/Rec2.png");
		int brick2 = slLoadTexture("assets/jungle/PNG/game_sprites/Rec.png");
		int brickRock = slLoadTexture("assets/jungle/PNG/game_sprites/Rec4.png");


		if (Actuallevel == Levels::Level1)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 830;
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
					Rects[iterator].sprite[2] = brick2;
					Rects[iterator].sprite[1] = brick1;
					Rects[iterator].sprite[0] = brick0;

					if (Rects[iterator].lives == 3)
					{
						Rects[iterator].currentSprite = 2;
					}
					else if (Rects[iterator].lives == 2)
					{
						Rects[iterator].currentSprite = 1;
					}
					else
					{
						Rects[iterator].currentSprite = 0;
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
		else if (Actuallevel == Levels::Level2)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 830;
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

					if (index == Layers - 1 && j != 2 && j != 3 && j != 4)
					{
						Rects[iterator].sprite[Rects[iterator].currentSprite] = brickRock;
						Rects[iterator].isaRock = true;
					}
					else
					{
						if (Rects[iterator].lives == 3)
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec3.png");
						}
						else if (Rects[iterator].lives == 2)
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec2.png");
						}
						else
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec.png");
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
		else if (Actuallevel == Levels::Level3)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 830;
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
						Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec4.png");
						Rects[iterator].isaRock = true;
					}
					else
					{
						if (Rects[iterator].lives == 3)
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec3.png");
						}
						else if (Rects[iterator].lives == 2)
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec2.png");
						}
						else
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec.png");
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
		else if (Actuallevel == Levels::Level4)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 830;
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
						Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec4.png");
						Rects[iterator].isaRock = true;
					}
					else
					{
						if (Rects[iterator].lives == 3)
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec3.png");
						}
						else if (Rects[iterator].lives == 2)
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec2.png");
						}
						else
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec.png");
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
		else if (Actuallevel == Levels::Level5)
		{
			double RecXPosAux = 125;
			double RecYPosAux = 830;
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

					if ((index==0) || (index==1 && j==0 || j == 3 || j == 6) ||(index == 2 && j == 0 || j == 6) || (index == 3 && j == 0 || j == 3 || j == 6) || (index == 4 && j == 0 || j == 6) || (index == 5 && j == 0 || j == 3 || j == 6))
					{
						Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec4.png");
						Rects[iterator].isaRock = true;
					}
					else
					{
						if (Rects[iterator].lives == 3)
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec3.png");
						}
						else if (Rects[iterator].lives == 2)
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec2.png");
						}
						else
						{
							Rects[iterator].sprite[Rects[iterator].currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/Rec.png");
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
			for (int i = 0; i < actualBalls; i++)
			{
			BallMovement(ball[i]);
			}

			PlayerInput();
			if (Player.currentSprite != 0 )
			{
				timer += slGetDeltaTime();
				if (timer > TIME_FOR_SECOND_ANIMATION)
				{
					Player.currentSprite = 0;
				}
				else if (timer > TIME_FOR_FIRST_ANIMATION)
				{
					Player.currentSprite = 2;
				}
			}
			else 
			{
				timer = 0;
			}

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

			DrawSprite(BackGround);
			for (int i = 0; i < REC_AMOUNT; i++)
			{
				if (Rects[i].isAlive)
				{
					DrawSprite(Rects[i]);
					/*slRectangleFill(Rects[i].x, Rects[i].y, Rects[i].width, Rects[i].height);*/
				}
			}
			slSetForeColor(Player.color.r, Player.color.g, Player.color.b, 1);
			slSprite(Player.sprite[Player.currentSprite], Player.x, Player.y, Player.width + 60, Player.height * 8);

			for (int i = 0; i < actualBalls; i++)
			{
			slSetForeColor(ball[i].color.r, ball[i].color.g, ball[i].color.b, 1);
			slSprite(ball[i].sprite, ball[i].x, ball[i].y, ball[i].width, ball[i].height);
			}
			
			DrawSprite(Lives_Board);

			DrawSprite(Pause_Button);

			for (int i = 0; i < Player.lives; i++)
			{
				slSetForeColor(PlayerLive.color.r, PlayerLive.color.g, PlayerLive.color.b, 1);
				slSprite(PlayerLive.sprite[PlayerLive.currentSprite], livesAuxX, PlayerLive.y, PlayerLive.width, PlayerLive.height);
				livesAuxX += 35;
			}
			/*slRectangleFill(ball.x, ball.y, ball.width, ball.height);

			slRectangleFill(Player.x, Player.y, Player.width, Player.height);*/
		}
		else if (state == GameState::Win)
		{
			DrawSprite(BackGround2);

			DrawSprite(WoodBackGround);

			DrawSprite(PaperBackGround);

			if (Player.lives == 3)
			{
				DrawSprite(Win_3Star);
			}
			else if (Player.lives == 2)
			{
				DrawSprite(Win_2Star);
			}
			else
			{
				DrawSprite(Win_1Star);
			}

			DrawSprite(Win_Leaf);

			DrawSprite(Next_Button);

			DrawSprite(Menu_Button);
		}
		else if (state == GameState::Lose)
		{
			DrawSprite(BackGround2);

			DrawSprite(WoodBackGround);

			DrawSprite(PaperBackGround);
			
			DrawSprite(Lose_0Star);
			
			DrawSprite(Lose_Leaf);

			DrawSprite(Menu_Button);

			DrawSprite(Restart_Button);
		}
		else if (state == GameState::Paused)
		{
			DrawSprite(BackGround2);

			DrawSprite(WoodBackGround);

			DrawSprite(PaperBackGround);

			DrawSprite(Pause_Leaf);

			DrawSprite(Menu_Button);

			DrawSprite(Close_Button);

			DrawSprite(Restart_Button);

		}
		else if (state == GameState::ControlRules)
		{
			DrawSprite(BackGround);

			DrawSprite(WoodBackGround);

			DrawSprite(Control_Rules);
			
			DrawSprite(Rules_Leaf);
			
			DrawSprite(Next_Button);
		}
		else if(state == GameState::PowerUpRules)
		{
			DrawSprite(BackGround);

			DrawSprite(WoodBackGround);

			DrawSprite(PowerUp_Rules);

			DrawSprite(Rules_Leaf);

			DrawSprite(Back_Button);

			DrawSprite(Play_Button);
		
		}
	}

	void DrawSprite(RecSprites Sprite)
	{
		slSetForeColor(Sprite.color.r, Sprite.color.g, Sprite.color.b, 1);
		slSprite(Sprite.sprite[Sprite.currentSprite], Sprite.x, Sprite.y, Sprite.width, Sprite.height);
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
			int aliveBalls = 0;
			for (int i = 0; i < actualBalls; i++)
			{
				if (ball[i].y < Player.y - Player.height/2)
				{
					ball[i].speed = ball[i].BASE_SPEED;
					ball[i].isAlive = false;
				}

				if (ball[i].x > SCREEN_WIDTH - ball[i].radius)
				{
					ball[i].directionX *= -1;
					ball[i].x = SCREEN_WIDTH - ball[i].radius;
				}
				if (ball[i].x < ball[i].radius)
				{
					ball[i].directionX *= -1;
					ball[i].x = ball[i].radius;
				}
				if (ball[i].y > SCREEN_HEIGHT - 120 - ball[i].radius)
				{
					ball[i].directionY *= -1;
					ball[i].y -= ball[i].radius;
				}
				if (ball[i].isAlive)
				{
					aliveBalls++;
				}

				PlayerColision(ball[i]);
			}

			if (aliveBalls == 0)
			{
			actualBalls = 1;
			ball[0].isAlive = true;
			ball[0].y = 160;
			ball[0].x = 550;
			ball[0].directionY *= -1;
			ball[0].directionX += RandomPullOut();
			ball[0].speed = ball[0].BASE_SPEED;
			Player.lives--;
			}
			
			
			for (int i = 0; i < REC_AMOUNT; i++)
			{
				for (int j = 0; j < actualBalls; j++)
				{
					if (Rects[i].isAlive)
					{

						if (CircleRect(ball[j], Rects[i]))
						{
							float leftRec = Rects[j].x - Rects[i].width / 2;
							float rightRec = Rects[i].x + Rects[i].width / 2;
							float upRec = Rects[i].y + Rects[i].height / 2;
							float downRec = Rects[i].y - Rects[i].height / 2;

							if (rightRec < ball[j].x + ball[j].radius)
							{
								ball[j].x += ball[j].radius / 2;
								ball[j].directionX *= -1;
							}
							else if (leftRec > ball[j].x + ball[j].radius)
							{
								ball[j].x -= ball[j].radius / 2;
								ball[j].directionX *= -1;
							}

							if (downRec < ball[j].y + ball[j].radius)
							{
								ball[j].y -= ball[j].radius / 2;
								ball[j].directionY *= -1;
							}
							else if (upRec > ball[j].y + ball[j].radius)
							{
								ball[j].y += ball[j].radius / 2;
								ball[j].directionY *= -1;
							}


							if (!Rects[i].isaRock)
							{
								Rects[i].lives -= 1;
							}
						}


					}
				}
			}

			Pause_Button.color = colors::WHITE;

			if (MouseColision(mousePositionX, mousePositionY, Pause_Button))
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

			if (MouseColision(mousePositionX, mousePositionY, Menu_Button))
			{
				Menu_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::ControlRules;
					currentScreen = Screen::Menu;
				}
			}
			else if (MouseColision(mousePositionX, mousePositionY, Next_Button))
			{
				Next_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					if (Actuallevel == Levels::Level1)
					{
						Actuallevel = Levels::Level2;
					}
					else if (Actuallevel == Levels::Level2)
					{
						Actuallevel = Levels::Level3;
					}
					else if (Actuallevel == Levels::Level3)
					{
						Actuallevel = Levels::Level4;
					}
					else if (Actuallevel == Levels::Level4)
					{
						Actuallevel = Levels::Level5;
					}
					else if (Actuallevel == Levels::Level5)
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
		else if (state == GameState::Lose)
		{
			Menu_Button.color = colors::WHITE;
			Restart_Button.color = colors::WHITE;

			if (MouseColision(mousePositionX, mousePositionY, Menu_Button))
			{
				Menu_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{

					state = GameState::ControlRules;
					currentScreen = Screen::Menu;
				}
			}
			else if (MouseColision(mousePositionX, mousePositionY, Restart_Button))
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
		else if (state == GameState::Paused)
		{
			Close_Button.color = colors::WHITE;
			Menu_Button.color = colors::WHITE;
			Restart_Button.color = colors::WHITE;

			if (MouseColision(mousePositionX, mousePositionY, Close_Button))
			{
				Close_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::Playing;
				}
			}
			else if (MouseColision(mousePositionX, mousePositionY, Menu_Button))
			{
				Menu_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::ControlRules;
					currentScreen = Screen::Menu;
				}
			}
			else if (MouseColision(mousePositionX, mousePositionY, Restart_Button))
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
		else if(state == GameState::ControlRules)
		{
			Next_Button.color = colors::WHITE;

			if (MouseColision(mousePositionX, mousePositionY, Next_Button))
			{
				Next_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::PowerUpRules;
				}
			}
		}
		else if(state == GameState::PowerUpRules)
		{
			Play_Button.color = colors::WHITE;
			Back_Button.color = colors::WHITE;

			if (MouseColision(mousePositionX, mousePositionY, Play_Button))
			{
				Play_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::Playing;
				}
			}
			if (MouseColision(mousePositionX, mousePositionY, Back_Button))
			{
				Back_Button.color = colors::GRAY;

				if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				{
					state = GameState::ControlRules;
				}
			}
		}
	}

	void PlayerColision(Ball& ball)
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

			AddBallSpeed(ball);
			ball.y += ball.radius / 2;

			
			Player.currentSprite = 1;
			
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

	bool MouseColision(float mousex, float mousey, RecSprites rec)
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

	float RandomPullOut()
	{
		float randomFloat = rand() % 4 + 1;

		if (randomFloat == 1)
		{
			randomFloat = -1;
		} 
		else if(randomFloat == 2)
		{
			randomFloat = -0.5;
		}
		else if (randomFloat == 3)
		{
			randomFloat = 0.5;
		}
		else if (randomFloat == 4)
		{
			randomFloat = 1;
		}

		return randomFloat;
	}
}
