#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"
#define screenWidth 1600
#define screenHeigth 900

#define BACKGROUND  CLITERAL(Color){ 0, 0, 0, 100 }
namespace Screen {

	extern Vector2 start;
	extern Vector2 end;
	extern float thickLine;
	extern Rectangle backPause;

	extern void InitializeScreen();
	extern void DrawLine();
	extern void DrawBackP();
}
#endif // !SCREEN_H