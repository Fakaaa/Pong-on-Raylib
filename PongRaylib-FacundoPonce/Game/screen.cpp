#include "screen.h"
#include "loop.h"

namespace Screen {

	Vector2 start;
	Vector2 end;
	float thickLine;

	void InitializeScreen() {
		InitWindow(screenWidth, screenHeigth, "Pong on Raylib");
		start = { screenWidth / 2, 0 };
		end = {screenWidth / 2, screenHeigth};
		thickLine = 5;
	}

	void DrawUI() {
		DrawLineEx(start, end, thickLine, WHITE);
		
	}
}