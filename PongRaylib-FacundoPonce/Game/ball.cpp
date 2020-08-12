#include "ball.h"
#include "players.h"

#include <iostream>

using namespace std;

using namespace Players;
using namespace Loop;

namespace Ball {

	BALLON ball;
	const int colorsCant = 8;
	int i = 0;
	Color type[colorsCant] = { WHITE,RED,GREEN,YELLOW,VIOLET,BROWN,ORANGE,PURPLE };
	Color selected;
	int impact;  //Variable que me sierve de salida. Solucionando el error que ocurre cuando la pelota colisiona debajo de las paletas
	int scorePj; //Variable que me permite como un "bool" saber que jugador hizo el punto 
		//-----------------------------------------------------------------------
		void DrawBall() { //Dibuja la pelota 
			DrawCircleV(ball.POS, ball.RAD, ball.COLOR);
		}
		//-----------------------------------------------------------------------
		void ChooseColor() {
			if (IsKeyPressed(KEY_RIGHT)) {
				if(i <= 7)
					i++;
			}
			if (IsKeyPressed(KEY_LEFT)) {
				if (i >= 0)
					i--;
			}
			if (i > 7)
				i = 0;
			if (i < 0)
				i = 7;
			DrawCircleV(ball.POS, ball.RAD, type[i]);

			if (IsKeyPressed(KEY_Y)) {
				actualGameState = BALL_SELECT;
			}
			if (actualGameState == BALL_SELECT) {
				selected = type[i];
			}
		}
		//-----------------------------------------------------------------------
		void InitializeBall() { //Inicializa la pelota, con su posición, radio y demas caracteristicas
			ball.POS = {screenWidth / 2,screenHeigth / 2};
			ball.RAD = 20;
			ball.SPEED = {8.0f,5.0f};
			impact = 0;
			scorePj = 0;
			ball.COLOR = selected;
			if(actualGameState == BALL_SELECT)
				actualGameState = GAMEPLAY;
		}
		//-----------------------------------------------------------------------
		void MoveBall() { //Mueve permanentemente la pelota por la pantalla y llama a la funcion chequear impactos
			CheckImpacts();
				ball.POS.x += ball.SPEED.x;
				ball.POS.y += ball.SPEED.y;
		}
		//-----------------------------------------------------------------------
		void CheckImpacts() { //Se encarga de las colisiones de la pelota con los jugadores y limites de pantalla. Ademas setea las victorias.
			//COLISIONES
			if (ball.POS.y >= (screenHeigth - ball.RAD) || ball.POS.y <= ball.RAD) { ball.SPEED.y *= -1.0f; }
			if (CheckCollisionCircleRec(ball.POS, ball.RAD, pj1.BODY) && impact != 1) {
				impact = 1;
				ball.SPEED.x *= -1.0f;
				if (pj1.UP_Force || pj1.DOWN_Force) { // Condicional que va aumentando la velocidad poco a poco de la pelota al colicionar con las paletas
					//ball.SPEED.y += 0.8f;
					//ball.SPEED.x += 0.8f;
				}
			}
			if (CheckCollisionCircleRec(ball.POS, ball.RAD, pj2.BODY) && impact != 2) {
				impact = 2;
				ball.SPEED.x *= -1.0f;
				if (pj2.UP_Force||pj2.DOWN_Force) {
					ball.SPEED.y += 0.8f;
					ball.SPEED.x += 0.8f;
				}
			}
			//VICTORIAS Y PUNTAJE
			if (ball.POS.x < 0 - ball.RAD) {
				pj2.GAMES += 1;
				actualGameState = RESET;
				auxGameState = SCORE;
				scorePj = 2;
			}
			if (ball.POS.x > screenWidth - ball.RAD) {
				pj1.GAMES += 1;
				actualGameState = RESET;
				auxGameState = SCORE;
				scorePj = 1;
			}
			if (actualGameState == RESET) {
				ball.POS = { screenWidth / 2,screenHeigth / 2 };
			}
			if (pj1.GAMES == 8 || pj2.GAMES == 8) {
				actualGameState = WIN;
			}
		}
}