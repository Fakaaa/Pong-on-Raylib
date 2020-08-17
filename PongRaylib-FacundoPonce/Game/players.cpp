#include "players.h"
#include "loop.h"
#include <iostream>

using namespace Loop;
using namespace std;

namespace Players {

	PJS pj1;
	PJS pj2;
	POWER_UPS powerup;
	int posXP1, posYP1;
	int posXP2, posYP2;
	int fontSize;
	int randValue = 0;
	bool powerUpSet;
	int pWin;
		//--------------------------------------------------------------------------------------------------
		void InitializePjs() { //Inicializacion de los jugadores y sus valores
			float width = 25;
			float height = 200;
			pj1.BODY = { 0,screenHeigth / 2, width, height };
			pj2.BODY = {screenWidth - width,screenHeigth / 2, width, height};
			pj1.SPEED = { 400.0f, 400.0f};
			pj2.SPEED = { 400.0f, 400.0f};
			pj1.onBot = false;
			pj1.onTop = false;
			pj2.onBot = false;
			pj2.onTop = false;
			pj1.GAMES = 0;
			pj2.GAMES = 0;
			posXP1 = 250;
			posYP2 = 0;
			fontSize = 50;
			posXP2 = screenWidth - posXP1 - 100;
			posYP2 = 0;
			pj1.WON = false;
			pj2.WON = false;
			powerUpSet = false;
			pWin = 0;
		}
		//--------------------------------------------------------------------------------------------------
		void DrawPjs(PJS& pjs) { //Dibujado de paletas
			DrawRectangleRec(pjs.BODY, WHITE);
			DrawText(FormatText("PJ1: %i", pj1.GAMES), posXP1, posYP1, fontSize, WHITE);
			DrawText(FormatText("PJ2: %i", pj2.GAMES), posXP2 , posYP2, fontSize, WHITE);
		}
		//--------------------------------------------------------------------------------------------------
		void DrawPowerUpIn() {
			if (!powerUpSet && (timer[1] == 10 || timer[1] == 25 || timer[1] == 40)) {
				DrawText("Power UP INCOMING!!", posXP1 - 100, posYP1 + 400, fontSize, WHITE);
				DrawText("Press [L] KEY!!", posXP1 - 100, posYP1 + 450, fontSize, WHITE);
				DrawText("Power UP INCOMING!!", posXP2 - 300, posYP2 + 400, fontSize, WHITE);
				DrawText("Press [9] KEY!!", posXP2 - 300, posYP2 + 450, fontSize, WHITE);
			}

			if(powerup == Switch && powerUpSet)
				DrawText("SWITCH POWER-UP!!", screenWidth / 3, posYP2 + 400, fontSize, GREEN);
			else if (powerup == Slowdown && powerUpSet)
				DrawText("SLOWDOWN POWER-UP!!", screenWidth / 3, posYP2 + 400, fontSize, GREEN);
			else if (powerup == Bullet && powerUpSet)
				DrawText("BULLET POWER-UP!!", screenWidth / 3, posYP2 + 400, fontSize, GREEN);

			if (pj1.powerUp_Pick && pWin == 1) {
				DrawText("PLAYER 1 WIN THE PICK!!", screenWidth / 4, posYP2 + 450, fontSize, YELLOW);
				pWin = 0;
			}
			if (pj2.powerUp_Pick && pWin == 2) {
				DrawText("PLAYER 2 WIN THE PICK!!", screenWidth / 4, posYP2 + 450, fontSize, VIOLET);
				pWin = 0;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void CheckLimits(PJS& pjs) { //Chequeo de limites en las paletas [Limites en Y: menor a 0 y mayor al tamaño max]
			if (pjs.BODY.y < 0)
				pjs.onTop = true;
			else
				pjs.onTop = false;

			if(pjs.BODY.y + pjs.BODY.height > screenHeigth)
				pjs.onBot = true;
			else
				pjs.onBot = false;
		}
		//--------------------------------------------------------------------------------------------------
		void Inputs(PJS& p1, PJS& p2) { //Inputs de los jugadores, desplazamiento de paletas
			CheckLimits(p1);
			CheckLimits(p2);
			MakePowerUp();
			//PJ1
			if (IsKeyDown(KEY_W)) {
				if (!p1.onTop) {
					p1.BODY.y -= p1.SPEED.y * GetFrameTime();
					p1.UP_Force = true;
				}
			}
			else {
				p1.UP_Force = false;
			}
			if (IsKeyDown(KEY_S)) {
				if (!p1.onBot) {
					p1.BODY.y += p1.SPEED.y * GetFrameTime();
					p1.DOWN_Force = true;
				}
			}
			else {
				p1.DOWN_Force = false;
			}
			//PJ2
			if (IsKeyDown(KEY_UP)) {
				if (!p2.onTop) {
					p2.BODY.y -= p2.SPEED.y * GetFrameTime();
					p2.UP_Force = true;
				}
			}
			else {
				p2.UP_Force = false;
			}
			if (IsKeyDown(KEY_DOWN)) {
				if (!p2.onBot) {
					p2.BODY.y += p2.SPEED.y * GetFrameTime();
					p2.DOWN_Force = true;
				}
			}
			else {
				p2.DOWN_Force = false;
			}

			//BOTH PJS PICK POWER UP
			if (powerUpSet) {
				if (IsKeyDown(KEY_L)) {
					p1.powerUp_Pick = true;
					p1.luck = powerup;
					randValue = 0;
				}
				if (IsKeyDown(KEY_KP_9)) {
					p2.powerUp_Pick = true;
					p2.luck = powerup;
					randValue = 0;
				}
			}
			//USE POWER UP
			if (IsKeyDown(KEY_E) && powerUpSet) {
				p1.usePowerUp = true;
			}
			if (IsKeyDown(KEY_KP_2) && powerUpSet) {
				p2.usePowerUp = true;
			}

		}
		//--------------------------------------------------------------------------------------------------
		void MakePowerUp() {
			if (timer[1] == 15 || timer[1] == 30 || timer[1] == 45 && !powerUpSet) {
				randValue = GetRandomValue(1, 3);
					if (randValue == 1) { powerup = Switch; }
					if (randValue == 2) { powerup = Slowdown; }
					if (randValue == 3) { powerup = Bullet; }
				powerUpSet = true;
			}
		}
}