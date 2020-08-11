#ifndef BALL_H
#define BALL_H
#include "loop.h"

namespace Ball {

	struct BALLON{
		Vector2 POS;
		float RAD;
		Vector2 SPEED;
	};

	extern BALLON ball;
	extern int impact;
	extern int scorePj;
	extern int bounceCount;

	extern void DrawBall();
	extern void InitializeBall();
	extern void MoveBall();
	extern void CheckImpacts();
}
#endif // !BALL_H