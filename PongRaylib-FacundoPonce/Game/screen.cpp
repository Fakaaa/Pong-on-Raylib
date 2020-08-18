#include "screen.h"
#include "loop.h"

namespace Screen {

	Vector2 start;
	Vector2 end;
	Rectangle backPause;
	float thickLine;
		//-----------------------------------------------------------------------
		void InitializeScreen() { //Inicia la ventana de raylib
			InitWindow(screenWidth, screenHeigth, "Pong on Raylib");
			start = { screenWidth / 2, 0 };
			end = {screenWidth / 2, screenHeigth};
			thickLine = 3;
			backPause = {0,0,screenWidth,screenHeigth};
		}
		//-----------------------------------------------------------------------
		void DrawLine() { //Dibuja la linea del centro la cual le brinda mas belleza al entorno del juego :3
			DrawLineEx(start, end, thickLine, WHITE);
		}
		//-----------------------------------------------------------------------
		void DrawBackP(){
			DrawRectangleRec(backPause, BACKGROUND);
		}
}