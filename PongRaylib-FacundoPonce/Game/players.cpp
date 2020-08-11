#include "players.h"

namespace Players {
	PJS pj1;
	PJS pj2;

	void InitializePjs() {

		float width = 0;
		float height = 0;

		pj1.POS = { 0, screenHeigth / 2 };
		pj2.POS = {screenWidth - pj2.BODY.width, screenHeigth / 2};
		pj1.BODY = { pj1.POS.x,pj1.POS.y,width,height };
		pj2.BODY = {pj2.POS.x,pj2.POS.y,width,height};
	}

	void DrawPjs(PJS &pjs) {
		DrawRectangleRec(pjs.BODY, WHITE);
	}

	void Inputs(PJS &p1, PJS &p2) {
		if (IsKeyDown(KEY_W)) {
			p1.POS.y--;
		}
		if (IsKeyDown(KEY_S)) {
			p1.POS.y++;
		}

		if (IsKeyDown(KEY_UP)) {
			p2.POS.y--;
		}
		if (IsKeyDown(KEY_DOWN)) {
			p2.POS.y++;
		}
	}
}