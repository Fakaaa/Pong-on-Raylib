#ifndef BALL_H
#define BALL_H
#include "loop.h"

namespace Ball {

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

	extern void DrawBall();
	extern void InitializeBall();
	extern void MoveBall();
	extern void CheckImpacts();
	extern void ChooseColor();
	extern void UsePowerUp();
	void CalcPoints();
	void DrawDevMode();
}
#endif // !BALL_H