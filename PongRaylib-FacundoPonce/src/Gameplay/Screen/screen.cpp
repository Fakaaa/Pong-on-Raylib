#include "screen.h"

#include "Gameplay/variables.h"
#include "Gameplay/loop.h"
#include "Menu/menu.h"

using namespace Pong;
using namespace Vars;

namespace Pong{
	namespace Screen{

		static Vector2 start;
		static Vector2 end;
		static float thickLine;

		Vector2 posFrameRec;
		static Rectangle backPause;
		static Texture2D backGround;
		static Rectangle frameRecStage;
		float posXStart;
		float posYStart;
		float posXEnd;
		float posYEnd;

		int framesAnim = 0;
		int currentFrame = 0;
		int framesCounter = 0;
		int framesSpeed = 9;

		//-----------------------------------------------------------------------
		void initializeScreen(){
			posXStart = static_cast<float>(screenWidth / divMul_2);
			posYStart = 0;
			posXEnd = static_cast<float>(screenWidth / divMul_2);
			posYEnd = screenHeigth;
			frameRecStage = { 0.0f,0.0f, screenWidth,screenHeigth };
			posFrameRec = { 0.0f,0.0f };
			framesAnim = 8;

			InitWindow(screenWidth, screenHeigth, "Pong on Raylib - v1.0");
			start = { posXStart , posYStart };
			end = { posXEnd, posYEnd };
			thickLine = 3;
			backPause = { 0,0,screenWidth,screenHeigth };
		}
		//-----------------------------------------------------------------------
		void drawLine(){
			DrawLineEx(start, end, thickLine, WHITE);
		}
		//-----------------------------------------------------------------------
		void drawBackP(){
			DrawRectangleRec(backPause, BACKGROUND);
		}
		//-----------------------------------------------------------------------
		void drawBackground(){
			if (Menu::actualGameState != Menu::PAUSE)
				framesCounter++;
			if (framesCounter >= (maxFrames / framesSpeed)){
				framesCounter = 0;
				currentFrame++;

				if (currentFrame > framesAnim) currentFrame = 0;

				frameRecStage.x = ((float)currentFrame) * ((float)backGround.width / framesAnim);
			}
			if (framesSpeed > MAX_FRAME_SPEED){ framesSpeed = MAX_FRAME_SPEED; }
			else if (framesSpeed < MIN_FRAME_SPEED){ framesSpeed = MIN_FRAME_SPEED; }

			DrawTextureRec(backGround, frameRecStage, posFrameRec, WHITE);
		}
		//-----------------------------------------------------------------------
		void loadBackground(){
			Image rescale;
			//-----------------------------------------------------------------------
			rescale = LoadImage("res/textures/BACKGROUND.png");
			ImageResize(&rescale, screenWidth * divMul_8, screenHeigth);
			backGround = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}
		//-----------------------------------------------------------------------
		void unloadBackground(){
			UnloadTexture(backGround);
		}
	}
}