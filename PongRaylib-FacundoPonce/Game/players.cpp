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
	bool powerUpShow;
	int pWin;
	int auxFrames = 0;
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
			powerUpShow = false;
			pWin = 0;
			pj1.godTime = 3;
			pj2.godTime = 3;
			pj1.luck = None;
			pj2.luck = None;
		}
		//--------------------------------------------------------------------------------------------------
		void DrawPjs(PJS& pjs) { //Dibujado de paletas
			DrawRectangleRec(pjs.BODY, WHITE);
			DrawText(FormatText("PJ1: %i", pj1.GAMES), posXP1, posYP1, fontSize, WHITE);
			DrawText(FormatText("PJ2: %i", pj2.GAMES), posXP2 , posYP2, fontSize, WHITE);
			if(pj1.powerUp_Pick)
				DrawText("POWER UP AVIABLE", posXP1, posYP1 + 50, fontSize - 10, GREEN);
			if (pj2.powerUp_Pick)
				DrawText("POWER UP AVIABLE", posXP2, posYP2 + 50, fontSize - 10, GREEN);
		}
		//--------------------------------------------------------------------------------------------------
		void DrawPowerUpIn() {
			if (!powerUpSet && (timer[1] == 10 || timer[1] == 25 || timer[1] == 40)) {
				DrawText("Power UP INCOMING!!", posXP1 - 100, posYP1 + 400, fontSize, WHITE);
				DrawText("Press [L] KEY!!", posXP1 - 100, posYP1 + 450, fontSize, WHITE);
				DrawText("Power UP INCOMING!!", posXP2 - 300, posYP2 + 400, fontSize, WHITE);
				DrawText("Press [9] KEY!!", posXP2 - 300, posYP2 + 450, fontSize, WHITE);
			}

			if (powerUpSet && powerUpShow) {
				switch (powerup)
				{
				case Players::Switch: DrawText("SWITCH POWER-UP!!", screenWidth / 3, posYP2 + 400, fontSize, GREEN);
					break;
				case Players::Slowdown: DrawText("SLOWDOWN POWER-UP!!", screenWidth / 3, posYP2 + 400, fontSize, GREEN);
					break;
				case Players::Bullet: DrawText("BULLET POWER-UP!!", screenWidth / 3, posYP2 + 400, fontSize, GREEN);
					break;
				case Players::GodMode: DrawText("GODMODE POWER-UP!!", screenWidth / 3, posYP2 + 400, fontSize, GREEN);
					break;
				case Players::None: // xd
					break;
				default:
					break;
				}
			}

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
				}
			}
			if (IsKeyDown(KEY_S)) {
				if (!p1.onBot) {
					p1.BODY.y += p1.SPEED.y * GetFrameTime();
				}
			}
			//PJ2
			if (IsKeyDown(KEY_UP)) {
				if (!p2.onTop) {
					p2.BODY.y -= p2.SPEED.y * GetFrameTime();
				}
			}
			if (IsKeyDown(KEY_DOWN)) {
				if (!p2.onBot) {
					p2.BODY.y += p2.SPEED.y * GetFrameTime();
				}
			}

			//BOTH PJS PICK POWER UP
			if (powerUpSet) {
				if (IsKeyDown(KEY_L)) {
					p1.powerUp_Pick = true;
					powerUpShow = false;
					randValue = 0;
				}
				if (IsKeyDown(KEY_KP_9)) {
					p2.powerUp_Pick = true;
					powerUpShow = false;
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
		void GodModePowerUP() {
			if (auxFrames >= 60 && pj1.luck == GodMode) {
				pj1.godTime--;
				auxFrames = 0;
				if (pj1.godTime < 0) {
					pj1.BODY.y = screenHeigth / 2;
					pj1.BODY.height = 200;
					pj1.godTime = 3;
					pj1.luck = Empty;
				}
			}
			if (auxFrames >= 60 && pj2.luck == GodMode) {
				pj2.godTime--;
				auxFrames = 0;
				if (pj2.godTime < 0) {
					pj2.BODY.y = screenHeigth / 2;
					pj2.BODY.height = 200;
					pj2.godTime = 3;
					pj2.luck = Empty;
				}
			}
			if (!powerUpSet && (pj1.luck == Empty || pj2.luck == Empty)) {
				pj1.luck = None;
				pj2.luck = None;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void MakePowerUp() {
			if (timer[1] == 15 || timer[1] == 30 || timer[1] == 45 && !powerUpSet) {
				//randValue = GetRandomValue(1, 4);
				randValue = GodMode;
				switch (randValue)
				{	
				case Players::Switch: powerup = Switch;
					break;
				case Players::Slowdown: powerup = Slowdown;
					break;
				case Players::Bullet: powerup = Bullet;
					break;
				case Players::GodMode: powerup = GodMode;
					break;
				case Players::None: powerup = None;
					break;
				default:
					break;
				}
				powerUpSet = true;
				powerUpShow = true;
			}
		}
}