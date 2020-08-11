#ifndef SCREEN
#define SCREEN

#include "raylib.h"
#define screenWidth 1280
#define screenHeigth 720

namespace Screen {

	extern Vector2 start;
	extern Vector2 end;
	extern float thickLine;

	extern void InitializeScreen();
	extern void DrawUI();
}
#endif // !SCREEN