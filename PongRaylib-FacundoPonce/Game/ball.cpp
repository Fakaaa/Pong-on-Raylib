#include "ball.h"
#include "players.h"

using namespace Players;

namespace Ball {

	BALLON ball;
	int impact;

	void DrawBall() {
		DrawCircleV(ball.POS, ball.RAD, WHITE);
	}
	
	void InitializeBall() {
		ball.POS = {screenWidth / 4,screenHeigth / 2};
		ball.RAD = 20;
		ball.SPEED = {8.0f,5.0f};
		impact = 0;
	}
	
	void MoveBall() {

		CheckImpacts();

		ball.POS.x += ball.SPEED.x;
		ball.POS.y += ball.SPEED.y;
	}

	void CheckImpacts() {
		if (ball.POS.y >= (screenHeigth - ball.RAD) || ball.POS.y <= ball.RAD) { ball.SPEED.y *= -1.0f; }

		if (CheckCollisionCircleRec(ball.POS, ball.RAD, pj1.BODY) && impact != 1) {
			impact = 1;
			ball.SPEED.x *= -1.0f;
			if (pj1.UP_Force || pj1.DOWN_Force) {
				ball.SPEED.y += 0.5f;
				ball.SPEED.x += 0.5f;
			}
		}
		if (CheckCollisionCircleRec(ball.POS, ball.RAD, pj2.BODY) && impact != 2) {
			impact = 2;
			ball.SPEED.x *= -1.0f;
			if (pj2.UP_Force || pj2.DOWN_Force) {
				ball.SPEED.y += 0.5f;
				ball.SPEED.x += 0.5f;
			}
		}

		if (ball.POS.x < 0 - ball.RAD || ball.POS.x > screenWidth + ball.RAD) {

		}
	}
}