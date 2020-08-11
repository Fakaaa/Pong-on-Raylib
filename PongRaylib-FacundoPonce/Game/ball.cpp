#include "ball.h"
#include "players.h"

using namespace Players;
using namespace Loop;

namespace Ball {

	BALLON ball;
	int impact;
	int scorePj;

		void DrawBall() {
			DrawCircleV(ball.POS, ball.RAD, WHITE);
		}
		
		void InitializeBall() {
			ball.POS = {screenWidth / 2,screenHeigth / 2};
			ball.RAD = 20;
			ball.SPEED = {8.0f,5.0f};
			impact = 0;
			scorePj = 0;
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
					ball.SPEED.y += 0.8f;
					ball.SPEED.x += 0.8f;
				}
			}
			if (CheckCollisionCircleRec(ball.POS, ball.RAD, pj2.BODY) && impact != 2) {
				impact = 2;
				ball.SPEED.x *= -1.0f;
				if (pj2.UP_Force || pj2.DOWN_Force) {
					ball.SPEED.y += 0.8f;
					ball.SPEED.x += 0.8f;
				}
			}

			if (ball.POS.x < 0 - ball.RAD) {
				pj2.GAMES += 1;
				gameState = RESET;
				scorePj = 2;
			}
			if (ball.POS.x > screenWidth - ball.RAD) {
				pj1.GAMES += 1;
				gameState = RESET;
				scorePj = 1;
			}

			if (gameState == RESET) {
				ball.POS = { screenWidth / 2,screenHeigth / 2 };
			}
			if (pj1.GAMES == 8 || pj2.GAMES == 8) {
				gameState = WIN;
			}
		}
}