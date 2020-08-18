#include "ball.h"
#include "players.h"

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
	bool growSpeed; //Variable que me permite aumentar o no la velocidad de la pelota
	float speedBoost; //Valor que aumenta X cantidad la velocidad
		//-----------------------------------------------------------------------
		void DrawBall() { //Dibuja la pelota 
			DrawCircleV(ball.POS, ball.RAD, ball.COLOR);
			//DrawDevMode();
		}
		//-----------------------------------------------------------------------
		void DrawDevMode() {
			DrawCircleV(ball.pointTop, 5, GREEN);
			DrawCircleV(ball.pointBot, 5, GREEN);
			DrawCircleV(ball.pointRigth, 5, GREEN);
			DrawCircleV(ball.pointLeft, 5, GREEN);
			DrawText(FormatText("Ball Speed X: %i", static_cast<int>(ball.SPEED.x)), screenWidth / 2, 400, fontSize, RED);
			DrawText(FormatText("Ball Speed Y: %i", static_cast<int>(ball.SPEED.y)), screenWidth / 2, 450, fontSize, RED);
			DrawText(FormatText("Power Up %i", (int)powerup), screenWidth / 2, 500, fontSize, YELLOW);
			DrawText(FormatText("God TIME p1 %i", (int)pj1.godTime), screenWidth / 2, 500, fontSize, YELLOW);
			DrawText(FormatText("God TIME p2 %i", (int)pj2.godTime), screenWidth / 2, 550, fontSize, GREEN);
			DrawText(FormatText("Power Up PJ1 %i", (int)pj1.luck), screenWidth / 2, 550, fontSize, GREEN);
			DrawText(FormatText("Power Up PJ2 %i", (int)pj2.luck), screenWidth / 2, 600, fontSize, GREEN);
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
			speedBoost = 0.5f;

			ball.pointRigth = { (ball.POS.x + ball.RAD), ball.POS.y };
			ball.pointTop = { ball.POS.x, (ball.POS.y + ball.RAD) };
			ball.pointBot = { ball.POS.x, (ball.POS.y - ball.RAD)};
			ball.pointLeft = { (ball.POS.x - ball.RAD), ball.POS.y };

			impact = 0;
			scorePj = 0;
			ball.COLOR = selected;
			if(actualGameState == BALL_SELECT)
				actualGameState = GAMEPLAY;
		}
		//-----------------------------------------------------------------------
		void MoveBall() { //Mueve permanentemente la pelota por la pantalla, llama a la funcion chequear impactos y usar power
			UsePowerUp();
			CheckImpacts();
				ball.POS.x += ball.SPEED.x;
				ball.POS.y += ball.SPEED.y;
			CalcPoints();
		}
		//-----------------------------------------------------------------------
		void CalcPoints() {
			ball.pointRigth = { (ball.POS.x + ball.RAD), ball.POS.y };
			ball.pointTop = { ball.POS.x, (ball.POS.y + ball.RAD) };
			ball.pointBot = { ball.POS.x, (ball.POS.y - ball.RAD) };
			ball.pointLeft = { (ball.POS.x - ball.RAD), ball.POS.y };
		}
		//-----------------------------------------------------------------------
		void CheckImpacts() { //Se encarga de las colisiones de la pelota con los jugadores y limites de pantalla. Ademas setea las victorias.
			if(pj1.luck == GodMode || pj2.luck == GodMode)
				auxFrames++;
			//COLISIONES
			if (ball.POS.y >= (screenHeigth - ball.RAD) || ball.POS.y <= ball.RAD) { ball.SPEED.y *= -1.0f; }
			if (ball.SPEED.x <= 17.0f && ball.SPEED.x >= -17.0f) { growSpeed = true; } else { growSpeed = false; }

			//COLLI ON X
			if (CheckCollisionPointRec(ball.pointRigth, pj2.BODY) && impact != 1) {
				impact = 1;
				ball.SPEED.x *= -1.0f;
				if (growSpeed) {
					ball.SPEED.x = ball.SPEED.x - 1.0f;
					if (ball.SPEED.y > 0) {
						ball.SPEED.y = ball.SPEED.y + speedBoost;
					}
					else {
						ball.SPEED.y = ball.SPEED.y - speedBoost;
					}
				}
			}
			if (CheckCollisionPointRec(ball.pointLeft, pj1.BODY) && impact != 2) {
				impact = 2;
				ball.SPEED.x *= -1.0f;
				if (growSpeed) {
					ball.SPEED.x = ball.SPEED.x + 1.0f;
					if (ball.SPEED.y > 0) {
						ball.SPEED.y = ball.SPEED.y + speedBoost;
					}
					else {
						ball.SPEED.y = ball.SPEED.y - speedBoost;
					}
				}
			}
			//COLLI ON Y
			if (CheckCollisionPointRec(ball.pointTop, pj1.BODY) || CheckCollisionPointRec(ball.pointTop, pj2.BODY) || CheckCollisionPointRec(ball.pointBot, pj1.BODY) || CheckCollisionPointRec(ball.pointBot, pj2.BODY)) {
				ball.SPEED.y *= -1.0f;
			}

			//VICTORIAS Y PUNTAJE
			if (ball.POS.x < -ball.RAD) {
				pj2.GAMES += 1;
				actualGameState = RESET;
				auxGameState = SCORE;
				scorePj = 2;
			}
			if (ball.POS.x > screenWidth + ball.RAD) {
				pj1.GAMES += 1;
				actualGameState = RESET;
				auxGameState = SCORE;
				scorePj = 1;
			}
			//RESET AFTER SCOREING
			if (actualGameState == RESET) {
				ball.POS = { screenWidth / 2,screenHeigth / 2 };
				if (ball.SPEED.x > 0)
					ball.SPEED.x = 8.0;
				else
					ball.SPEED.x = -8.0;
				if (ball.SPEED.y > 0)
					ball.SPEED.y = 5.0;
				else
					ball.SPEED.y = -5.0;
				pj1.BODY.x = 0;
				pj1.BODY.y = screenHeigth / 2;
				pj2.BODY.x = screenWidth - 25;
				pj2.BODY.y = screenHeigth / 2;
				pj1.BODY.height = 200;
				pj2.BODY.height = 200;
				
				pj1.luck = Empty;
				pj2.luck = Empty;
				pj1.godTime = 3;
				pj2.godTime = 3;
			}

			GodModePowerUP();

			//END THE MATCH IF SOMEONE WINS (8 POINTS)
			if (pj1.GAMES == 8 || pj2.GAMES == 8) {
				actualGameState = WIN;
			}
		}
		//-----------------------------------------------------------------------
		void UsePowerUp() {
			if (pj1.powerUp_Pick && pj1.luck != Empty) {
				if (pj1.usePowerUp) {
					pj1.luck = powerup;
					switch (pj1.luck)
					{
					case Players::Switch: ball.SPEED.y *= -1.0f;
						break;
					case Players::Slowdown:
						if (ball.SPEED.x < 0)
							ball.SPEED.x = ball.SPEED.x + 8.0f;
						break;
					case Players::Bullet: ball.SPEED.x = 35.0f;
						break;
					case Players::GodMode:
							pj1.BODY.height = screenHeigth;
							pj1.BODY.y = 0;
						break;
					case Players::None: //Nada xd
						break;
					default:
						break;
					}
					powerUpSet = false;
					if (pj1.luck != GodMode)
						pj1.luck = Empty;
					pj1.powerUp_Pick = false;
					pj1.usePowerUp = false;
				}
			}
			if (pj2.powerUp_Pick && pj2.luck != Empty) {
				if (pj2.usePowerUp) {
					if (pj2.usePowerUp) {
						pj2.luck = powerup;
						switch (pj2.luck)
						{
						case Players::Switch: ball.SPEED.y *= -1.0f;
							break;
						case Players::Slowdown:
							if (ball.SPEED.x < 0)
								ball.SPEED.x = ball.SPEED.x - 8.0f;
							break;
						case Players::Bullet: ball.SPEED.x = -35.0f;
							break;
						case Players::GodMode: 
							pj2.BODY.height = screenHeigth;
							pj2.BODY.y = 0;
							break;
						case Players::None: //Nada xd
							break;
						default:
							break;
						}
						powerUpSet = false;
						if(pj2.luck != GodMode)
							pj2.luck = Empty;
						pj2.powerUp_Pick = false;
						pj2.usePowerUp = false;
					}
				}
			}
		}
}