#include "Game.h"

#include "ProyectUtilities/Utilities.h"
#include "Objects/Rectangles.h"
#include "Objects/Ball.h"
#include "Objects/PowerUp.h"

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
	static void DrawRecSprite(RecSprites Sprite);
	static void DrawBallSprite(Ball Sprite);

	static const int SCREEN_WIDTH = 1100;
	static const int TOP_HEIGHT = 865;
	static const int REC_AMOUNT = 42;
	static const int FIX_PLAYER_HEIGHT = 8;
	static const int FIX_PLAYER_WIDTH = 120;
	static const int MAX_BALLS = 50; // NO SE SI SE PODIA USAR PUNTEROS ASI QUE PONGO UN NUMERO "Inalcanzable"
	static int actualBalls = 1;
	static float timer = 0;
	static const float TIME_FOR_FIRST_ANIMATION = 0.18f;
	static const float TIME_FOR_SECOND_ANIMATION = 0.5f;
	static bool removeLife = false;
	static bool multiBall = false;
	static bool extraLife = false;

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
	static RecSprites PaperBackGround_Pause;
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
	static RecSprites Top_Height_Line;
	static RecSprites Rects[REC_AMOUNT];
	static Ball PowerDownRemoveLife;
	static Ball PowerUpMultiBall;
	static Ball PowerUpExtraLife;
	static Levels Actuallevel;
	static GameState state;

	void InitGame(Levels level)
	{

		state = GameState::ControlRules;
		Actuallevel = level;


		initStatesSprites();

		LevelGenerator();

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
			if (Player.currentSprite != 0)
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
			
			powerUp::PowerUpsUpdate(PowerUpMultiBall, PowerDownRemoveLife, PowerUpExtraLife, multiBall, extraLife, removeLife, actualBalls, Player, ball[0]);

			state = ShouldContinue();
		}

	}

	void DrawGame(Screen currentScreen)
	{

		if (state == GameState::Playing)
		{
			double livesAuxX = 160;

			DrawRecSprite(BackGround);
			for (int i = 0; i < REC_AMOUNT; i++)
			{
				if (Rects[i].isAlive)
				{
					DrawRecSprite(Rects[i]);
					/*slRectangleFill(Rects[i].x, Rects[i].y, Rects[i].width, Rects[i].height);*/
				}
			}

			slSetForeColor(Player.color.r, Player.color.g, Player.color.b, 1);
			slSprite(Player.sprite[Player.currentSprite], Player.x, Player.y, Player.width + FIX_PLAYER_WIDTH, Player.height * FIX_PLAYER_HEIGHT);

			if (removeLife)
			{
			DrawBallSprite(PowerDownRemoveLife);
			}
			if (multiBall)
			{
			DrawBallSprite(PowerUpMultiBall);
			}
			if (extraLife)
			{	
			DrawBallSprite(PowerUpExtraLife);
			}

			for (int i = 0; i < actualBalls; i++)
			{
				DrawBallSprite(ball[i]);
			/*slRectangleFill(ball[i].x, ball[i].y, ball[i].width, ball[i].height);*/
			}

			DrawRecSprite(Top_Height_Line);

			DrawRecSprite(Lives_Board);

			DrawRecSprite(Pause_Button);

			for (int i = 0; i < Player.lives; i++)
			{
				slSetForeColor(PlayerLive.color.r, PlayerLive.color.g, PlayerLive.color.b, 1);
				slSprite(PlayerLive.sprite[PlayerLive.currentSprite], livesAuxX, PlayerLive.y, PlayerLive.width, PlayerLive.height);
				livesAuxX += 35;
			}

			/*slRectangleFill(Player.x, Player.y, Player.width, Player.height);*/
		}
		else if (state == GameState::Win)
		{
			DrawRecSprite(BackGround2);

			DrawRecSprite(WoodBackGround);

			DrawRecSprite(PaperBackGround);

			if (Player.lives == 3)
			{
				DrawRecSprite(Win_3Star);
			}
			else if (Player.lives == 2)
			{
				DrawRecSprite(Win_2Star);
			}
			else
			{
				DrawRecSprite(Win_1Star);
			}

			DrawRecSprite(Win_Leaf);

			DrawRecSprite(Next_Button);

			DrawRecSprite(Menu_Button);
		}
		else if (state == GameState::Lose)
		{
			DrawRecSprite(BackGround2);

			DrawRecSprite(WoodBackGround);

			DrawRecSprite(PaperBackGround);

			DrawRecSprite(Lose_0Star);

			DrawRecSprite(Lose_Leaf);

			DrawRecSprite(Menu_Button);

			DrawRecSprite(Restart_Button);
		}
		else if (state == GameState::Paused)
		{
			DrawRecSprite(BackGround2);

			DrawRecSprite(WoodBackGround);

			DrawRecSprite(PaperBackGround_Pause);

			DrawRecSprite(Pause_Leaf);

			DrawRecSprite(Menu_Button);

			DrawRecSprite(Close_Button);

			DrawRecSprite(Restart_Button);

		}
		else if (state == GameState::ControlRules)
		{
			DrawRecSprite(BackGround);

			DrawRecSprite(WoodBackGround);

			DrawRecSprite(Control_Rules);

			DrawRecSprite(Rules_Leaf);

			DrawRecSprite(Next_Button);
		}
		else if (state == GameState::PowerUpRules)
		{
			DrawRecSprite(BackGround);

			DrawRecSprite(WoodBackGround);

			DrawRecSprite(PowerUp_Rules);

			DrawRecSprite(Rules_Leaf);

			DrawRecSprite(Back_Button);

			DrawRecSprite(Play_Button);

		}
	}

	GameState ShouldContinue()
	{
		int aliveRecCounter = 0;

		for (int i = 0; i < REC_AMOUNT; i++)
		{
			if (Rects[i].isAlive)
			{
					if (Rects[i].lives < 1)
					{
						Rects[i].isAlive = false;

						if (Rects[i].havePowerUp)
						{
							int randomNum = rand() % 3 + 1;

							if (randomNum == 1)
							{
								removeLife = true;
								PowerDownRemoveLife.x = Rects[i].x;
								PowerDownRemoveLife.y = Rects[i].y;
							}
							else if (randomNum == 2)
							{
								multiBall = true;
								PowerUpMultiBall.x = Rects[i].x;
								PowerUpMultiBall.y = Rects[i].y;
							}
							else
							{
								extraLife = true;
								PowerUpExtraLife.x = Rects[i].x;
								PowerUpExtraLife.y = Rects[i].y;
							}


						}
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
	
	void LevelGenerator()
	{
		Player.sprite[0] = slLoadTexture("assets/jungle/PNG/game_sprites/Rest.png");
		Player.sprite[1] = slLoadTexture("assets/jungle/PNG/game_sprites/Hold.png");
		Player.sprite[2] = slLoadTexture("assets/jungle/PNG/game_sprites/Release.png");
		Player.x = 600;
		Player.y = 90;
		Player.width = 200;
		Player.height = 30;
		Player.lives = 3;

		PlayerLive.sprite[PlayerLive.currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/BananaLive.png");
		PlayerLive.x = 160;
		PlayerLive.y = 910;
		PlayerLive.width = 65;
		PlayerLive.height = 65;

		BackGround.sprite[BackGround.currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/BackGround2.png");
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
			ball[i].speed = ball[i].BASE_SPEED;
		}

		for (int i = 0; i < REC_AMOUNT; i++)
		{
			Rects[i].isAlive = true;
		}

		int brick0 = slLoadTexture("assets/jungle/PNG/game_sprites/Rec3.png");
		int brick1 = slLoadTexture("assets/jungle/PNG/game_sprites/Rec2.png");
		int brick2 = slLoadTexture("assets/jungle/PNG/game_sprites/Rec.png");


		multiBall = false;
		extraLife = false;
		removeLife = false;

		actualBalls = 1;

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
					Rects[iterator].havePowerUp = RandomizeBool();

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
					Rects[iterator].havePowerUp = RandomizeBool();

					if (index == Layers - 1 && j != 2 && j != 3 && j != 4)
					{
						Rects[iterator].lives = 3;
					}
					
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
					Rects[iterator].havePowerUp = RandomizeBool();

					if (index == Layers - 3 && j != 0 && j != 6)
					{
						Rects[iterator].lives = 3;
					}
					
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
					Rects[iterator].havePowerUp = RandomizeBool();

					if ((index == 0) || (index == Layers - 1) && (j != 3))
					{
						Rects[iterator].lives = 3;
					}
					
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
					Rects[iterator].havePowerUp = RandomizeBool();

					if ((index == 0) || (index == 1 && j == 0 || j == 3 || j == 6) || (index == 2 && j == 0 || j == 6) || (index == 3 && j == 0 || j == 3 || j == 6) || (index == 4 && j == 0 || j == 6) || (index == 5 && j == 0 || j == 3 || j == 6))
					{
						Rects[iterator].lives = 3;
					}
					
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
	
	void CollisionCkeck(Screen& currentScreen)
	{
		int mousePositionX = slGetMouseX();
		int mousePositionY = slGetMouseY();

		if (state == GameState::Playing)
		{
			int aliveBalls = 0;
			for (int i = 0; i < actualBalls; i++)
			{
				if (ball[i].y < 0)
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
				if (ball[i].y > TOP_HEIGHT- ball[i].radius)
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
									ball[j].x += ball[j].radius;
									ball[j].directionX *= -1;
								}
								else if (leftRec > ball[j].x + ball[j].radius)
								{
									ball[j].x -= ball[j].radius;
									ball[j].directionX *= -1;
								}


								if (downRec < ball[j].y + ball[j].radius)
								{
									ball[j].y -= ball[j].radius;
									ball[j].directionY *= -1;
								}
								else if (upRec > ball[j].y + ball[j].radius)
								{
									ball[j].y += ball[j].radius;
									ball[j].directionY *= -1;
								}


								AddBallSpeed(ball[j]);

									Rects[i].lives -= 1;
									if (Rects[i].lives > 0)
									{
										Rects[i].currentSprite--;
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
						Rects[i].isAlive = true;
					}

					state = GameState::Playing;
					LevelGenerator();
				}
			}
		}
		else if (state == GameState::ControlRules)
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
		else if (state == GameState::PowerUpRules)
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
		if (rand() % 5 == 1)
		{
			return true;
		}
		return false;
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

	void initStatesSprites()
	{
		Win_Leaf.sprite[Win_Leaf.currentSprite] = slLoadTexture("assets/jungle/PNG/you_win/leaf.png");
		Win_Leaf.x = 550;
		Win_Leaf.y = 730;
		Win_Leaf.width = 600;
		Win_Leaf.height = 220;

		Win_3Star.sprite[Win_3Star.currentSprite] = slLoadTexture("assets/jungle/PNG/you_win/3star.png");
		Win_3Star.x = 550;
		Win_3Star.y = 530;
		Win_3Star.width = 600;
		Win_3Star.height = 220;

		Win_2Star.sprite[Win_2Star.currentSprite] = slLoadTexture("assets/jungle/PNG/you_win/2star.png");
		Win_2Star.x = 550;
		Win_2Star.y = 530;
		Win_2Star.width = 600;
		Win_2Star.height = 220;

		Win_1Star.sprite[Win_1Star.currentSprite] = slLoadTexture("assets/jungle/PNG/you_win/1star.png");
		Win_1Star.x = 550;
		Win_1Star.y = 530;
		Win_1Star.width = 600;
		Win_1Star.height = 220;

		WoodBackGround.sprite[WoodBackGround.currentSprite] = slLoadTexture("assets/jungle/PNG/you_win/WoodBackGround.png");
		WoodBackGround.x = 550;
		WoodBackGround.y = 420;
		WoodBackGround.width = 760;
		WoodBackGround.height = 700;

		PaperBackGround.sprite[PaperBackGround.currentSprite] = slLoadTexture("assets/jungle/PNG/you_win/PaperBackGround.png");
		PaperBackGround.x = 550;
		PaperBackGround.y = 420;
		PaperBackGround.width = 660;
		PaperBackGround.height = 600;

		PaperBackGround_Pause.sprite[PaperBackGround.currentSprite] = slLoadTexture("assets/jungle/PNG/pause/PaperBackGround.png");
		PaperBackGround_Pause.x = 550;
		PaperBackGround_Pause.y = 420;
		PaperBackGround_Pause.width = 700;
		PaperBackGround_Pause.height = 600;

		BackGround2.sprite[BackGround2.currentSprite] = slLoadTexture("assets/jungle/PNG/pause/BackGround.png");
		BackGround2.x = 550;
		BackGround2.y = 375;
		BackGround2.width = 1100;
		BackGround2.height = 1150;

		Lose_0Star.sprite[Lose_0Star.currentSprite] = slLoadTexture("assets/jungle/PNG/you_lose/0star.png");
		Lose_0Star.x = 550;
		Lose_0Star.y = 530;
		Lose_0Star.width = 600;
		Lose_0Star.height = 220;

		Lose_Leaf.sprite[Lose_Leaf.currentSprite] = slLoadTexture("assets/jungle/PNG/you_lose/leaf.png");
		Lose_Leaf.x = 550;
		Lose_Leaf.y = 730;
		Lose_Leaf.width = 600;
		Lose_Leaf.height = 220;

		Next_Button.sprite[Next_Button.currentSprite] = slLoadTexture("assets/jungle/PNG/buttons/next.png");
		Next_Button.x = 750;
		Next_Button.y = 250;
		Next_Button.width = 120;
		Next_Button.height = 120;

		Back_Button.sprite[Back_Button.currentSprite] = slLoadTexture("assets/jungle/PNG/buttons/prew.png");
		Back_Button.x = 350;
		Back_Button.y = 250;
		Back_Button.width = 120;
		Back_Button.height = 120;

		Pause_Button.sprite[Pause_Button.currentSprite] = slLoadTexture("assets/jungle/PNG/buttons/pause.png");
		Pause_Button.x = 1050;
		Pause_Button.y = 905;
		Pause_Button.width = 80;
		Pause_Button.height = 80;

		Menu_Button.sprite[Menu_Button.currentSprite] = slLoadTexture("assets/jungle/PNG/buttons/menu.png");
		Menu_Button.x = 430;
		Menu_Button.y = 250;
		Menu_Button.width = 120;
		Menu_Button.height = 120;

		Play_Button.sprite[Play_Button.currentSprite] = slLoadTexture("assets/jungle/PNG/buttons/play.png");
		Play_Button.x = 550;
		Play_Button.y = 250;
		Play_Button.width = 120;
		Play_Button.height = 120;

		Restart_Button.sprite[Restart_Button.currentSprite] = slLoadTexture("assets/jungle/PNG/buttons/restart.png");
		Restart_Button.x = 680;
		Restart_Button.y = 250;
		Restart_Button.width = 120;
		Restart_Button.height = 120;

		Close_Button.sprite[Close_Button.currentSprite] = slLoadTexture("assets/jungle/PNG/pause/close.png");
		Close_Button.x = 240;
		Close_Button.y = 680;
		Close_Button.width = 120;
		Close_Button.height = 120;

		Pause_Leaf.sprite[Pause_Leaf.currentSprite] = slLoadTexture("assets/jungle/PNG/pause/leaf.png");
		Pause_Leaf.x = 550;
		Pause_Leaf.y = 730;
		Pause_Leaf.width = 600;
		Pause_Leaf.height = 220;

		PlayerPoints.sprite[PlayerPoints.currentSprite] = slLoadTexture("assets/jungle/PNG/buttons/pause.png");
		PlayerPoints.x = 1050;
		PlayerPoints.y = 905;
		PlayerPoints.width = 80;
		PlayerPoints.height = 80;

		Control_Rules.sprite[Control_Rules.currentSprite] = slLoadTexture("assets/jungle/PNG/rules/ControlRules.png");
		Control_Rules.x = 550;
		Control_Rules.y = 420;
		Control_Rules.width = 660;
		Control_Rules.height = 600;

		PowerUp_Rules.sprite[PowerUp_Rules.currentSprite] = slLoadTexture("assets/jungle/PNG/rules/PowerUpRules.png");
		PowerUp_Rules.x = 550;
		PowerUp_Rules.y = 420;
		PowerUp_Rules.width = 660;
		PowerUp_Rules.height = 600;

		Rules_Leaf.sprite[Rules_Leaf.currentSprite] = slLoadTexture("assets/jungle/PNG/rules/leaf.png");
		Rules_Leaf.x = 550;
		Rules_Leaf.y = 730;
		Rules_Leaf.width = 600;
		Rules_Leaf.height = 220;

		Lives_Board.sprite[Lives_Board.currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/LivesBoard.png");
		Lives_Board.x = 150;
		Lives_Board.y = 910;
		Lives_Board.width = 250;
		Lives_Board.height = 60;

		Top_Height_Line.sprite[Top_Height_Line.currentSprite] = slLoadTexture("assets/jungle/PNG/game_sprites/TopLine.png");
		Top_Height_Line.x = 350;
		Top_Height_Line.y = TOP_HEIGHT;
		Top_Height_Line.width = 1600;
		Top_Height_Line.height = 20;

		PowerDownRemoveLife.sprite = slLoadTexture("assets/jungle/PNG/game_sprites/RottenBanana.png");
		PowerDownRemoveLife.height = 60;
		PowerDownRemoveLife.width = 60;
		PowerDownRemoveLife.radius = 30;
		PowerDownRemoveLife.directionY = -1;

		PowerUpMultiBall.sprite = slLoadTexture("assets/jungle/PNG/game_sprites/CoconoutPowerUp.png");
		PowerUpMultiBall.height = 60;
		PowerUpMultiBall.width = 60;
		PowerUpMultiBall.radius = 30;
		PowerUpMultiBall.directionY = -1;

		PowerUpExtraLife.sprite = slLoadTexture("assets/jungle/PNG/game_sprites/BananaPowerUp.png");
		PowerUpExtraLife.height = 60;
		PowerUpExtraLife.width = 60;
		PowerUpExtraLife.radius = 30;
		PowerUpExtraLife.directionY = -1;
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
		else if (randomFloat == 2)
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

	void DrawRecSprite(RecSprites Sprite)
	{
		slSetForeColor(Sprite.color.r, Sprite.color.g, Sprite.color.b, 1);
		slSprite(Sprite.sprite[Sprite.currentSprite], Sprite.x, Sprite.y, Sprite.width, Sprite.height);
	}

	void DrawBallSprite(Ball Sprite)
	{
		slSetForeColor(Sprite.color.r, Sprite.color.g, Sprite.color.b, 1);
		slSprite(Sprite.sprite, Sprite.x, Sprite.y, Sprite.width, Sprite.height);
	}
}
