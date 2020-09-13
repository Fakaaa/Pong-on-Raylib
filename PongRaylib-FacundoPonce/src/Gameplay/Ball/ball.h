#ifndef BALL_H
#define BALL_H

#include "Gameplay/Screen/screen.h"

namespace Pong{
	namespace Ball{

		struct BALLON{
			Vector2 POS;
			float RAD;
			Vector2 SPEED;
			Color COLOR;

			Vector2 pointTop;
			Vector2 pointBot;
			Vector2 pointLeft;
			Vector2 pointRigth;
		};

		extern BALLON ball;
		extern int impact;
		extern int scorePj;
		extern int bounceCount;

		extern float speedXBall;
		extern float speedYBall;
		extern float bulletPower;

		void chooseColor();
		void initializeBall();
		void drawBall();
		void checkImpacts();
		void calcPoints();
		void moveBall();
		void drawDevMode();
	}
}
#endif // !BALL_H