#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"

const int screenWidth = 1600;
const int screenHeigth = 900;
const int MAX_FRAME_SPEED = 15;
const int MIN_FRAME_SPEED = 1;

#define BACKGROUND  CLITERAL(Color){ 0, 0, 0, 100 }
#define MUSIC_GAMEPLAY  CLITERAL(Color){ 253, 249, 0, 100 }

namespace Pong{
	namespace Screen{

		void initializeScreen();
		void drawLine();
		void drawBackP();
		void drawBackground();
		void loadBackground();
		void unloadBackground();
	}
}
#endif // !SCREEN_H