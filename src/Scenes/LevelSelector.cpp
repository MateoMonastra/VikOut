#include "LevelSelector.h"

#include "ProyectUtilities/Colours.h"
#include "ProyectUtilities/Utilities.h"

namespace levelSelector 
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

Button Level1_Button;
Button Level2_Button;
Button Level3_Button;
Button Level4_Button;
Button Level5_Button;
Button BackGround;
Button WoodBackGround;
Button PaperBackGround;
Button LevelSelector_Leaf;
Button Menu_Button;


void LevelSelectorInit()
{
		/*Level1_Button.image = slLoadTexture("assets/jungle/PNG/level_select/BackGround.png");
		Level1_Button.TexturePosition.x =
		Level1_Button.TexturePosition.y =
		Level1_Button.SpriteW =
		Level1_Button.SpriteH =
		Level1_Button.color = colors::WHITE;*/

}
void LevelSelectorUpdate(Screen& currentScreen)
{


}

void LevelSelectorDraw()
{


}
}