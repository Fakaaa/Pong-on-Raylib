#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"
#define screenWidth 1600
#define screenHeigth 900

namespace Screen {

	extern Vector2 start;
	extern Vector2 end;
	extern float thickLine;

	extern void InitializeScreen();
	extern void DrawLine();
}
#endif // !SCREEN_H