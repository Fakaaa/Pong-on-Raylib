#include "players.h"
#include <iostream>

using namespace std;

namespace Players {

	PJS pj1;
	PJS pj2;
	int posXP1, posYP1;
	int posXP2, posYP2;
	int fontSize;
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
		}
		//--------------------------------------------------------------------------------------------------
		void DrawPjs(PJS& pjs) { //Dibujado de paletas
			DrawRectangleRec(pjs.BODY, WHITE);
			DrawText(FormatText("PJ1: %i", pj1.GAMES), posXP1, posYP1, fontSize, WHITE);
			DrawText(FormatText("PJ2: %i", pj2.GAMES), posXP2 , posYP2, fontSize, WHITE);
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
			//PJ1
			if (IsKeyDown(KEY_W)) {
				if (!p1.onTop) {
					p1.BODY.y -= p1.SPEED.y * GetFrameTime();
					p1.UP_Force = true;
					p1.DOWN_Force = false;
				}
			}
			if (IsKeyDown(KEY_S)) {
				if (!p1.onBot) {
					p1.BODY.y += p1.SPEED.y * GetFrameTime();
					p1.UP_Force = false;
					p1.DOWN_Force = true;
				}
			}
			//PJ2
			if (IsKeyDown(KEY_UP)) {
				if (!p2.onTop) {
					p2.BODY.y -= p2.SPEED.y * GetFrameTime();
					p2.UP_Force = true;
					p2.DOWN_Force = false;
				}
			}
			if (IsKeyDown(KEY_DOWN)) {
				if (!p2.onBot) {
					p2.BODY.y += p2.SPEED.y * GetFrameTime();
					p2.UP_Force = false;
					p2.DOWN_Force = true;
				}
			}
		}
}