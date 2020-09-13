#include "ball.h"

#include "Gameplay/Player/players.h"
#include "Gameplay/variables.h"
#include "Menu/menu.h"
#include "Gameplay/loop.h"

using namespace Pong;
using namespace Players;
using namespace Vars;
using namespace Loop;

namespace Pong{
	namespace Ball{

		BALLON ball;
		const int colorsCant = 8;
		int i = 0;
		Color type[colorsCant] = { WHITE,RED,GREEN,YELLOW,VIOLET,BROWN,ORANGE,PURPLE };
		Color selected;
		int impact;
		int scorePj;
		bool growSpeed;
		float speedBoost;

		float speedXBall;
		float speedYBall;
		float bulletPower;

		//-----------------------------------------------------------------------
		void chooseColor(){
			if (IsKeyPressed(KEY_RIGHT)){
				if (i <= 7)
					i++;
			}
			if (IsKeyPressed(KEY_LEFT)){
				if (i >= 0)
					i--;
			}
			if (i > 7)
				i = 0;
			if (i < 0)
				i = 7;
			DrawCircleV(ball.POS, ball.RAD, type[i]);

			if (IsKeyPressed(KEY_Y)){
				Menu::actualGameState = Menu::BALL_SELECT;
			}
			if (Menu::actualGameState == Menu::BALL_SELECT){
				selected = type[i];
			}
		}
		//-----------------------------------------------------------------------
		void initializeBall(){
			speedXBall = 10.0f;
			speedYBall = 7.0f;
			bulletPower = static_cast<float>(35.0f);
			ball.POS = { static_cast<float>(screenWidth / divMul_2), static_cast<float>(screenHeigth / divMul_2) };
			ball.RAD = (float)(num10 * divMul_2);
			ball.SPEED = { speedXBall,speedYBall };
			speedBoost = 0.5f;

			ball.pointRigth = { (ball.POS.x + ball.RAD), ball.POS.y };
			ball.pointTop = { ball.POS.x, (ball.POS.y + ball.RAD) };
			ball.pointBot = { ball.POS.x, (ball.POS.y - ball.RAD) };
			ball.pointLeft = { (ball.POS.x - ball.RAD), ball.POS.y };

			impact = 0;
			scorePj = 0;
			ball.COLOR = selected;
			if (Menu::actualGameState == Menu::BALL_SELECT)
				Menu::actualGameState = Menu::MODE_SELECT;
		}
		//-----------------------------------------------------------------------
		void drawBall(){
			DrawCircleV(ball.POS, ball.RAD, ball.COLOR);
			//drawDevMode();
		}
		//-----------------------------------------------------------------------
		void checkImpacts(){ //Se encarga de las colisiones de la pelota con los jugadores y limites de pantalla. Ademas setea las victorias.
			int speedMultiplyer = 50;

			if (pj1.luck == GodMode || pj2.luck == GodMode)
				secondsCountP += GetFrameTime();
			//COLISIONES
			if (ball.POS.y >= (screenHeigth - ball.RAD) || ball.POS.y <= ball.RAD){ ball.SPEED.y *= -1.0f; }
			if (ball.SPEED.x <= 25.0f && ball.SPEED.x >= -25.0f){ growSpeed = true; }
			else{ growSpeed = false; }

			//COLLI ON X
			if (CheckCollisionPointRec(ball.pointRigth, pj2.BODY) && impact != 1){
				impact = 1;
				ball.SPEED.x *= -1.0f;
				if (growSpeed){
					ball.SPEED.x = ball.SPEED.x - 1.0f;
					pj1.SPEED.y = pj1.SPEED.y + ((speedBoost + speedBoost) * speedMultiplyer);

					if (Loop::difficulty == Easy)
						pj2.SPEED.y = pj2.SPEED.y + ((speedBoost) * (speedMultiplyer - num10));
					else if (Loop::difficulty == Hard)
						pj2.SPEED.y = pj2.SPEED.y + ((speedBoost + speedBoost) * (speedMultiplyer - num10));
					else if (Loop::difficulty == Impossible)
						pj2.SPEED.y = pj2.SPEED.y + ((speedBoost + speedBoost) * (speedMultiplyer + num10));

					if (ball.SPEED.y > 0){
						ball.SPEED.y = ball.SPEED.y + speedBoost;
					}
					else{
						ball.SPEED.y = ball.SPEED.y - speedBoost;
					}
				}
			}
			if (CheckCollisionPointRec(ball.pointLeft, pj1.BODY) && impact != 2){
				impact = 2;
				ball.SPEED.x *= -1.0f;
				if (growSpeed){
					ball.SPEED.x = ball.SPEED.x + 1.0f;
					pj1.SPEED.y = pj1.SPEED.y + ((speedBoost + speedBoost) * speedMultiplyer);

					if (Loop::difficulty == Easy)
						pj2.SPEED.y = pj2.SPEED.y + ((speedBoost) * (speedMultiplyer - num10));
					else if (Loop::difficulty == Hard)
						pj2.SPEED.y = pj2.SPEED.y + ((speedBoost + speedBoost) * (speedMultiplyer - num10));
					else if (Loop::difficulty == Impossible)
						pj2.SPEED.y = pj2.SPEED.y + ((speedBoost + speedBoost) * (speedMultiplyer + num10));

					if (ball.SPEED.y > 0){
						ball.SPEED.y = ball.SPEED.y + speedBoost;
					}
					else{
						ball.SPEED.y = ball.SPEED.y - speedBoost;
					}
				}
			}
			//COLLI ON Y
			if (CheckCollisionPointRec(ball.pointTop, pj1.BODY) || CheckCollisionPointRec(ball.pointTop, pj2.BODY) || CheckCollisionPointRec(ball.pointBot, pj1.BODY) || CheckCollisionPointRec(ball.pointBot, pj2.BODY)){
				ball.SPEED.y *= -1.0f;
			}

			if (pj1.shieldActive){
				if (CheckCollisionPointRec(ball.pointLeft, pj1.shield)){
					impact = 2;
					ball.SPEED.x *= -1.0f;
					pj1.shieldActive = false;
				}
			}
			if (pj2.shieldActive){
				if (CheckCollisionPointRec(ball.pointRigth, pj2.shield)){
					impact = 1;
					ball.SPEED.x *= -1.0f;
					pj2.shieldActive = false;
				}
			}

			//VICTORIAS Y PUNTAJE
			if (ball.POS.x < -ball.RAD){
				pj2.GAMES += 1;
				Menu::actualGameState = Menu::RESET;
				if (gameMode == PJvsPJ || gameMode == PJvsIA)
					Menu::auxGameState = Menu::SCORE;
				else
					Menu::auxGameState = Menu::NONE;
				scorePj = 2;
			}
			if (ball.POS.x > screenWidth + ball.RAD){
				pj1.GAMES += 1;
				Menu::actualGameState = Menu::RESET;
				if (gameMode == PJvsPJ || gameMode == PJvsIA)
					Menu::auxGameState = Menu::SCORE;
				else
					Menu::auxGameState = Menu::NONE;
				scorePj = 1;
			}
			//RESET AFTER SCOREING
			if (Menu::actualGameState == Menu::RESET){
				ball.POS = { static_cast<float>(screenWidth / divMul_2), static_cast<float>(screenHeigth / divMul_2) };
				if (ball.SPEED.x > 0)
					ball.SPEED.x = speedXBall;
				else
					ball.SPEED.x = -speedXBall;
				if (ball.SPEED.y > 0)
					ball.SPEED.y = speedYBall;
				else
					ball.SPEED.y = -speedYBall;

				pj1.BODY = { posBodyXP1,posBodyYP1,widthPj,heightPj };
				pj2.BODY = { posBodyXP2,posBodyYP2,widthPj,heightPj };
				pj1.SPEED.y = speedPlayers;
				pj2.SPEED.y = speedPlayers;
				pj1.luck = Empty;
				pj2.luck = Empty;
				pj1.godTime = secsGTime;
				pj2.godTime = secsGTime;
				pj1.inverTime = secsINvTime;
				pj2.inverTime = secsINvTime;

				pj1.UPk = pj1.auxUPk;
				pj1.DOWNk = pj1.auxDOWNk;
				pj2.UPk = pj2.auxUPk;
				pj2.DOWNk = pj2.auxDOWNk;
			}
		}
		//-----------------------------------------------------------------------
		void calcPoints(){
			ball.pointRigth = { (ball.POS.x + ball.RAD), ball.POS.y };
			ball.pointTop = { ball.POS.x, (ball.POS.y + ball.RAD) };
			ball.pointBot = { ball.POS.x, (ball.POS.y - ball.RAD) };
			ball.pointLeft = { (ball.POS.x - ball.RAD), ball.POS.y };
		}
		//-----------------------------------------------------------------------
		void moveBall(){
			checkImpacts();
			ball.POS.x += ball.SPEED.x;
			ball.POS.y += ball.SPEED.y;
			calcPoints();
		}
		//-----------------------------------------------------------------------
		void drawDevMode(){
			DrawText(FormatText("Invert TIME p1 %i", (int)pj1.inverTime), screenWidth / divMul_3, (num250 * divMul_2), fontSize, YELLOW);
			DrawText(FormatText("Invert TIME p2 %i", (int)pj2.inverTime), screenWidth / divMul_3, (num300 + num250), fontSize, GREEN);
			//DrawCircleV(ball.pointTop, divMul_2, GREEN);
			//DrawCircleV(ball.pointBot, divMul_2, GREEN);
			//DrawCircleV(ball.pointRigth, divMul_2, GREEN);
			//DrawCircleV(ball.pointLeft, divMul_2, GREEN);
			DrawText(FormatText("Ball Speed X: %i", static_cast<int>(ball.SPEED.x)), screenWidth / divMul_2, num400, fontSize, GREEN);
			DrawText(FormatText("Ball Speed Y: %i", static_cast<int>(ball.SPEED.y)), screenWidth / divMul_2, num450, fontSize, GREEN);
			//DrawText(FormatText("God TIME p1 %i", (int)pj1.godTime), screenWidth / divMul_3, (num250 * divMul_2), fontSize, YELLOW);
			//DrawText(FormatText("God TIME p2 %i", (int)pj2.godTime), screenWidth / divMul_3, (num300 + num250), fontSize, GREEN);
			//DrawText(FormatText("Speed Y PJ1 %i", (int)pj1.SPEED.y), screenWidth / divMul_4, (num300 + num250), fontSize, RED);
			//DrawText(FormatText("Speed Y PJ2 %i", (int)pj2.SPEED.y), screenWidth / divMul_4, (num400 + (num100*divMul_2)), fontSize, RED);
		}
	}
}