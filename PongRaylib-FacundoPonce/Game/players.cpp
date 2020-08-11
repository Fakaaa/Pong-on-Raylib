#include "players.h"
#include <iostream>

using namespace std;

namespace Players {

	PJS pj1;
	PJS pj2;

	void InitializePjs() {

		float width = 25;
		float height = 200;

		pj1.BODY = { 0,screenHeigth / 2, width, height };
		pj2.BODY = {screenWidth - width,screenHeigth / 2, width, height};
		pj1.SPEED = 400;
		pj2.SPEED = 400;
		pj1.onBot = false;
		pj1.onTop = false;
		pj2.onBot = false;
		pj2.onTop = false;
	}

	void DrawPjs(PJS& pjs) {
		DrawRectangleRec(pjs.BODY, WHITE);
	}

	void CheckLimits(PJS& pjs) {
		if (pjs.BODY.y < 0)
			pjs.onTop = true;
		else
			pjs.onTop = false;

		if(pjs.BODY.y + pjs.BODY.height > screenHeigth)
			pjs.onBot = true;
		else
			pjs.onBot = false;
	}

	void Inputs(PJS& p1, PJS& p2) {

		CheckLimits(p1);
		CheckLimits(p2);

		if (IsKeyDown(KEY_W)) {
			if (!p1.onTop) {
				p1.BODY.y -= p1.SPEED * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_S)) {
			if (!p1.onBot) {
				p1.BODY.y += p1.SPEED * GetFrameTime();
			}
		}

		if (IsKeyDown(KEY_UP)) {
			if (!p2.onTop) {
				p2.BODY.y -= p2.SPEED * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_DOWN)) {
			if (!p2.onBot) {
				p2.BODY.y += p2.SPEED * GetFrameTime();
			}
		}
	}
}