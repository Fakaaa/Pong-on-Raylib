#include "players.h"

#include <iostream>

#include "Gameplay/variables.h"
#include "Gameplay/loop.h"
#include "Gameplay/Ball/ball.h"
#include "Menu/menu.h"

using namespace Pong;
using namespace Vars;
using namespace Loop;
using namespace Ball;

namespace Pong{
	namespace Players{

		PJS pj1;
		PJS pj2;
		POWER_UPS powerup;
		POWER_UPS ai_power;
		int Key;
		int posXP1, posYP1, posY2P1;
		int posXP2, posYP2, posY2P2;
		int randValue_PowerPlayer;
		int randValue_PowerIA;
		int exitRandIA;
		int resetSwicth;
		int flag;
		bool powerUpPlayer_Set;
		bool powerUpAi_Set;
		bool powerUpShow;
		static int pWin;
		float secondsCountP = 0;
		static float secondsCountInverse = 0;

		float speedPlayers;
		float posBodyXP1;
		float posBodyYP1;
		float posBodyXP2;
		float posBodyYP2;
		float widthPj;
		float heightPj;

		static int whatPj = 0;
		static int actual = 0;

		int secsGTime;
		int secsINvTime;
		int IAS_Luck;
		bool gotKey;

		Color colorpj[MAXCOL] = { WHITE,RED,GREEN,YELLOW,VIOLET,BROWN,ORANGE,PURPLE };
		int  colorSelec = 0;
		//--------------------------------------------------------------------------------------------------
		void initializePjs(){
			widthPj = 25;
			heightPj = 200;
			speedPlayers = 500.0f;

			posBodyXP1 = static_cast<float>((num10*divMul_3));
			posBodyYP1 = static_cast<float>(screenHeigth / divMul_2);
			posBodyXP2 = static_cast<float>(screenWidth - widthPj - (num10*divMul_3));
			posBodyYP2 = static_cast<float>(screenHeigth / divMul_2);
			secsGTime = 3;
			secsINvTime = 4;
			exitRandIA = 0;
			flag = 0;
			Key = 0;

			//Init atributos/datos principales
			randValue_PowerPlayer = 0;
			randValue_PowerIA = 0;
			pj1.BODY = { posBodyXP1, posBodyYP1, widthPj, heightPj };
			pj2.BODY = { posBodyXP2, posBodyYP2, widthPj, heightPj };
			pj1.shield = { 0 , 0, static_cast<float>(num10*divMul_3), static_cast<float>(screenHeigth)};
			pj2.shield = { static_cast<float>(screenWidth-(num10*divMul_3)), 0, static_cast<float>(num10*divMul_3), static_cast<float>(screenHeigth)};

			pj1.onBot = false;
			pj1.onTop = false;
			pj2.onBot = false;
			pj2.onTop = false;
			pj1.GAMES = 0;
			pj2.GAMES = 0;
			pj1.shieldActive = false;
			whatPj = 1;

			if (Menu::actualGameState == Menu::RESTART && Menu::auxGameState != Menu::PAUSE){
				//PERSONAL THINGS
				pj1.MATCHES = pj1.MATCHES;
				pj2.MATCHES = pj2.MATCHES;

				pj1.UPk = pj1.UPk;
				pj1.DOWNk = pj1.DOWNk;
				pj1.TAKEPk = pj1.TAKEPk;
				pj1.USEPk = pj1.USEPk;

				pj2.UPk = pj2.UPk;
				pj2.DOWNk = pj2.DOWNk;
				pj2.TAKEPk = pj2.TAKEPk;
				pj2.USEPk = pj2.USEPk;

				pj1.auxUPk = pj1.UPk;
				pj1.auxDOWNk = pj1.DOWNk;
				pj2.auxUPk = pj2.UPk;
				pj2.auxDOWNk = pj2.DOWNk;

				pj1.selColor = pj1.selColor;
				pj2.selColor = pj2.selColor;

				pj1.SPEED = { 0, speedPlayers };
				if (Loop::gameMode == PJvsIA){
					if (Loop::gameMode != IAvsIA && Loop::difficulty == Easy) pj2.SPEED = { 0, speedPlayers - num250 };
					else if (Loop::gameMode != IAvsIA && Loop::difficulty == Hard) pj2.SPEED = { 0, speedPlayers - num100 };
					else if (Loop::gameMode != IAvsIA && Loop::difficulty == Impossible) pj2.SPEED = { 0, speedPlayers };
				}else if(Loop::gameMode == IAvsIA)
					pj2.SPEED = { 0, speedPlayers };

			}
			else if (!defaultStart){
				//DEFAULT THINGS
				pj1.UPk = 87;
				pj1.DOWNk = 83;
				pj1.TAKEPk = 76;
				pj1.USEPk = 69;

				pj2.UPk = 85;
				pj2.DOWNk = 74;
				pj2.TAKEPk = 329;
				pj2.USEPk = 322;

				pj1.auxUPk = pj1.UPk;
				pj1.auxDOWNk = pj1.DOWNk;
				pj2.auxUPk = pj2.UPk;
				pj2.auxDOWNk = pj2.DOWNk;

				pj1.selColor = WHITE;
				pj2.selColor = WHITE;

				pj1.SPEED = { 0, speedPlayers };
				pj2.SPEED = { 0, speedPlayers };

				defaultStart = true;
			}
			if (Menu::actualGameState == Menu::WIN){
				std::cout << "ENTRO NEGRI" << std::endl;
				pj1.MATCHES = 0;
				pj2.MATCHES = 0;
			}
			
			posXP1 = num250;
			posYP1 = 0;
			posY2P1 = 40;
			posXP2 = screenWidth - posXP1 - num100;
			posYP2 = 0;
			posY2P2 = 40;

			pj1.WON = false;
			pj2.WON = false;
			pj1.powerUp_Pick = false;
			pj2.powerUp_Pick = false;
			powerUpPlayer_Set = false;
			powerUpShow = false;
			pWin = 0;
			pj1.godTime = secsGTime;
			pj2.godTime = secsGTime;
			pj1.inverTime = secsINvTime;
			pj2.inverTime = secsINvTime;
			pj1.luck = None;
			pj2.luck = None;
		}
		//--------------------------------------------------------------------------------------------------
		void drawPjs(PJS& pjs){
			DrawRectangleRec(pjs.BODY, pjs.selColor);
			DrawText(FormatText("PJ1 score: %i", pj1.GAMES), posXP1, posYP1, fontSize, WHITE);
			DrawText(FormatText("PJ2 score: %i", pj2.GAMES), posXP2, posYP2, fontSize, WHITE);
			DrawText(FormatText("Games: %i", pj1.MATCHES), posXP1, posY2P1, fontSize, WHITE);
			DrawText(FormatText("Games: %i", pj2.MATCHES), posXP2, posY2P2, fontSize, WHITE);

			DrawText(FormatText("GOD TIME: %i", pj1.godTime), posXP1 + num300, posY2P1 + (num10*divMul_2), fontSize2, YELLOW);
			DrawText(FormatText("GOD TIME: %i", pj2.godTime), posXP2 - num400, posY2P2 + (num10*divMul_2), fontSize2, YELLOW);

			if(pj1.shieldActive)
				DrawRectangleRec(pj1.shield, pj1.selColor);
			if (pj2.shieldActive)
				DrawRectangleRec(pj2.shield, pj2.selColor);


			if (pj1.powerUp_Pick)
				DrawText("POWER UP AVIABLE", posXP1, (posYP1 + num100), (fontSize - num10), GREEN);
			if (pj2.powerUp_Pick)
				DrawText("POWER UP AVIABLE", posXP2, (posYP2 + num100), (fontSize - num10), GREEN);
		}
		//--------------------------------------------------------------------------------------------------
		void drawPowerUpIn(){
			if (!powerUpPlayer_Set && (timer[Seconds] == num10 || timer[Seconds] == 25 || timer[Seconds] == 40) && !pj1.powerUp_Pick && !pj2.powerUp_Pick){
				DrawText("Power UP INCOMING!!", posXP1 - num100, posYP1 + num400, fontSize, WHITE);
				DrawText(FormatText("USE KEY: %c", (char)pj1.USEPk), posXP1 - num100, posYP1 + num450, fontSize, GREEN);
				DrawText("Power UP INCOMING!!", posXP2 - num300, posYP2 + num400, fontSize, WHITE);
				DrawText(FormatText("USE KEY: %c", (char)pj1.USEPk), posXP2 - num300, posYP2 + num450, fontSize, GREEN);
				exitRandIA = 0;
			}
			if (powerUpPlayer_Set && powerUpShow){
				switch (powerup){
				case Players::Switch: DrawText("SWITCH POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				case Players::Slowdown: DrawText("SLOWDOWN POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				case Players::Bullet: DrawText("BULLET POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				case Players::GodMode: DrawText("GODMODE POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				case Players::Inversion:  DrawText("INVERSION POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				case Players::Shield: DrawText("SHIELD POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				default:
					break;
				}
			}
			if (powerUpAi_Set && powerUpShow){
				switch (ai_power){
				case Players::Switch: DrawText("SWITCH POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				case Players::Slowdown: DrawText("SLOWDOWN POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				case Players::Bullet: DrawText("BULLET POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				case Players::GodMode: DrawText("GODMODE POWER-UP!!", screenWidth / divMul_3, posYP2 + num400, fontSize, GREEN);
					break;
				default:
					break;
				}
			}
			if (gameMode != IAvsIA){
				if (pj1.powerUp_Pick && pWin == 1 && !pj2.powerUp_Pick){
					DrawText("PLAYER 1 WIN THE PICK!!", screenWidth / divMul_4, posYP2 + num450, fontSize, YELLOW);
					pWin = 0;
				}
				if (pj2.powerUp_Pick && pWin == 2 && !pj1.powerUp_Pick){
					DrawText("PLAYER 2 WIN THE PICK!!", screenWidth / divMul_4, posYP2 + num450, fontSize, VIOLET);
					pWin = 0;
				}
			}
			else{
				if (powerUpShow){
					if (IAS_Luck <= 9){
						DrawText("PLAYER 1 WIN THE PICK!!", screenWidth / divMul_4, posYP2 + num450, fontSize, YELLOW);
						pWin = 0;
					}
					if (IAS_Luck >= 10){
						DrawText("PLAYER 2 WIN THE PICK!!", screenWidth / divMul_4, posYP2 + num450, fontSize, VIOLET);
						pWin = 0;
					}
				}
			}
		}
		//--------------------------------------------------------------------------------------------------
		void checkLimits(PJS& pjs){
			if (pjs.BODY.y < 0)
				pjs.onTop = true;
			else
				pjs.onTop = false;

			if (pjs.BODY.y + pjs.BODY.height > screenHeigth)
				pjs.onBot = true;
			else
				pjs.onBot = false;
		}
		//--------------------------------------------------------------------------------------------------
		void inputs(){
			if (pj1.luck == Inversion || pj2.luck == Inversion)
				secondsCountInverse += GetFrameTime();
			checkLimits(pj1);
			checkLimits(pj2);
			makePowerUp();
			//PJ1
			if (IsKeyDown(pj1.UPk)){
				if (!pj1.onTop){
					pj1.BODY.y -= pj1.SPEED.y * GetFrameTime();
				}
			}
			if (IsKeyDown(pj1.DOWNk)){
				if (!pj1.onBot){
					pj1.BODY.y += pj1.SPEED.y * GetFrameTime();
				}
			}
			//PJ2
			if (gameMode == PJvsPJ){
				if (IsKeyDown(pj2.UPk)){
					if (!pj2.onTop){
						pj2.BODY.y -= pj2.SPEED.y * GetFrameTime();
					}
				}
				if (IsKeyDown(pj2.DOWNk)){
					if (!pj2.onBot){
						pj2.BODY.y += pj2.SPEED.y * GetFrameTime();
					}
				}
			}
			//BOTH PJS PICK POWER UP
			if (powerUpPlayer_Set){
				if (IsKeyDown(pj1.TAKEPk) && !pj2.powerUp_Pick){
					pj1.powerUp_Pick = true;
					powerUpShow = false;
					randValue_PowerPlayer = 0;
				}
				if (IsKeyDown(pj2.TAKEPk) && !pj1.powerUp_Pick){
					pj2.powerUp_Pick = true;
					powerUpShow = false;
					randValue_PowerPlayer = 0;
				}
			}
			//USE POWER UP
			if (IsKeyDown(pj1.USEPk) && powerUpPlayer_Set && !pj2.powerUp_Pick){
				pj1.usePowerUp = true;
			}
			if (IsKeyDown(pj2.USEPk) && powerUpPlayer_Set && !pj1.powerUp_Pick){
				pj2.usePowerUp = true;
			}

			godModePowerUP();

			if (pj2.luck == Inversion)
				disableInverse(pj1);
			else if (pj1.luck == Inversion)
				disableInverse(pj2);
		}
		//--------------------------------------------------------------------------------------------------
		void godModePowerUP(){
			if (secondsCountP >= 1 && pj1.luck == GodMode){
				pj1.godTime--;
				secondsCountP = 0;
				if (pj1.godTime < 0){
					pj1.BODY.y = posBodyYP1;
					pj1.BODY.height = heightPj;
					pj1.godTime = secsGTime;
					pj1.luck = Empty;
				}
			}
			else if (secondsCountP >= 1 && pj2.luck == GodMode){
				pj2.godTime--;
				secondsCountP = 0;
				if (pj2.godTime < 0){
					pj2.BODY.y = posBodyYP2;
					pj2.BODY.height = heightPj;
					pj2.godTime = secsGTime;
					pj2.luck = Empty;
				}
			}
			if (!powerUpPlayer_Set && (pj1.luck == Empty || pj2.luck == Empty)){
				pj1.luck = None;
				pj2.luck = None;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void shieldPowerUP(){
			if (pj1.luck == Shield){
				pj1.shieldActive = true;
			}
			else if (pj2.luck == Shield){
				pj2.shieldActive = true;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void inversePowerUP(PJS& pj){
			pj.AuxKey = pj.UPk;
			pj.UPk = pj.DOWNk;
			pj.DOWNk = pj.AuxKey;
		}
		//--------------------------------------------------------------------------------------------------
		void disableInverse(PJS& pj){
			if (secondsCountInverse >= 1){
				pj.inverTime--;
				secondsCountInverse = 0;
				if(pj.inverTime < 0 && Menu::actualGameState == Menu::GAMEPLAY){
					pj.AuxKey = pj.UPk;
					pj.UPk = pj.DOWNk;
					pj.DOWNk = pj.AuxKey;
					if (pj2.luck == Inversion)
						pj2.luck = Empty;
					else
						pj1.luck = Empty;
					pj.inverTime = secsINvTime;
					secondsCountInverse = 0;
				}
			}
			if (!powerUpPlayer_Set && pj.luck == Empty){
				pj.luck = None;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void makePowerUp(){
			if ((timer[Seconds] == 15 || timer[Seconds] == 30 || timer[Seconds] == 45) && !powerUpPlayer_Set && !pj1.powerUp_Pick && !pj2.powerUp_Pick){
				randValue_PowerPlayer = GetRandomValue(1, 6);
				switch (randValue_PowerPlayer){
				case Players::Switch: powerup = Switch;
					break;
				case Players::Slowdown: powerup = Slowdown;
					break;
				case Players::Bullet: powerup = Bullet;
					break;
				case Players::GodMode: powerup = GodMode;
					break;
				case Players::Inversion: powerup = Inversion;
					break;
				case Players::Shield: powerup = Shield;
					break;
				case Players::None: powerup = None;
					break;
				default:
					break;
				}
				powerUpPlayer_Set = true;
				powerUpShow = true;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void usePowerUpPlayers(){
			if (pj1.powerUp_Pick){
				if (pj1.usePowerUp){
					pj1.luck = powerup;
					switch (pj1.luck){
					case Players::Switch: ball.SPEED.y *= -1.0f;
						break;
					case Players::Slowdown:
						if (ball.SPEED.x < (-speedXBall - divMul_4))
							ball.SPEED.x = ball.SPEED.x + speedXBall;
						else
							ball.SPEED.x = ball.SPEED.x;
						break;
					case Players::Bullet: ball.SPEED.x = bulletPower;
						break;
					case Players::GodMode:
						pj1.BODY.height = screenHeigth;
						pj1.BODY.y = 0;
						break;
					case Players::Inversion:
						inversePowerUP(pj2);
						break;
					case Players::Shield:
						shieldPowerUP();
						break;
					default:
						break;
					}
					powerUpPlayer_Set = false;
					if (pj1.luck != GodMode && pj1.luck != Inversion)
						pj1.luck = Empty;
					pj1.powerUp_Pick = false;
					pj1.usePowerUp = false;
				}
			}
			if (pj2.powerUp_Pick){
				if (pj2.usePowerUp){
					pj2.luck = powerup;
					switch (pj2.luck){
					case Players::Switch: ball.SPEED.y *= -1.0f;
						break;
					case Players::Slowdown:
						if (ball.SPEED.x > (speedXBall + divMul_4))
							ball.SPEED.x = ball.SPEED.x - speedXBall;
						else
							ball.SPEED.x = ball.SPEED.x;
						break;
					case Players::Bullet: ball.SPEED.x = -bulletPower;
						break;
					case Players::GodMode:
						pj2.BODY.height = screenHeigth;
						pj2.BODY.y = 0;
						break;
					case Players::Inversion:
						inversePowerUP(pj1);
						break;
					case Players::Shield:
						shieldPowerUP();
						break;
					default:
						break;
					}
					powerUpPlayer_Set = false;
					if (pj2.luck != GodMode && pj2.luck != Inversion)
						pj2.luck = Empty;
					pj2.powerUp_Pick = false;
					pj2.usePowerUp = false;
				}
			}
		}
		//--------------------------------------------------------------------------------------------------
		void ai_GameplayP1(PJS& IAplayer){
			checkLimits(IAplayer);
			if (ball.POS.y < (IAplayer.BODY.y + ball.RAD)){
				if (!IAplayer.onTop)
					IAplayer.BODY.y -= IAplayer.SPEED.y * GetFrameTime();
			}
			else if (ball.POS.y > IAplayer.BODY.y){
				if (!IAplayer.onBot)
					IAplayer.BODY.y += IAplayer.SPEED.y * GetFrameTime();
			}
		}
		//--------------------------------------------------------------------------------------------------
		void ai_GameplayP2(PJS& IAplayer){
			checkLimits(IAplayer);
			if (ball.POS.y < (IAplayer.BODY.y + ball.RAD)){
				if (!IAplayer.onTop)
					IAplayer.BODY.y -= IAplayer.SPEED.y * GetFrameTime();
			}
			else if (ball.POS.y > IAplayer.BODY.y){
				if (!IAplayer.onBot)
					IAplayer.BODY.y += IAplayer.SPEED.y * GetFrameTime();
			}
		}
		//--------------------------------------------------------------------------------------------------
		void makePowerUp_For_IA(){
			if ((timer[Seconds] == 15 || timer[Seconds] == 30 || timer[Seconds] == 45) && !powerUpAi_Set){

				if (!powerUpAi_Set && !pj1.powerUp_Pick && !pj2.powerUp_Pick && exitRandIA == 0){
					//randValue_PowerIA = GetRandomValue(1, 6);
					randValue_PowerIA = 6;
					switch (randValue_PowerIA){
					case Players::Switch: ai_power = Switch; powerUpAi_Set = true;
						break;
					case Players::Slowdown: ai_power = Slowdown; powerUpAi_Set = true;
						break;
					case Players::Bullet: ai_power = Bullet; powerUpAi_Set = true;
						break;
					case Players::GodMode: ai_power = GodMode; powerUpAi_Set = true;
						break;
					case Players::Shield: ai_power = Shield; powerUpAi_Set = true;
						break;
					default: ai_power = None;
						break;
					}
					powerUpShow = true;
					exitRandIA = 1;
					resetSwicth = 0;
				}
			}
		}
		//--------------------------------------------------------------------------------------------------
		void luck_For_IAs(){
			if (powerUpAi_Set && !pj1.powerUp_Pick && !pj2.powerUp_Pick && exitRandIA == 0)
				IAS_Luck = GetRandomValue(0, 19);
		}
		//--------------------------------------------------------------------------------------------------
		void usePowerUp_For_IA(PJS& IAplayer1, PJS& IAplayer2){
			luck_For_IAs();
			if (powerUpAi_Set){
				if (IAS_Luck <= 9 && exitRandIA == 0){
					IAplayer1.powerUp_Pick = true;
					IAplayer2.powerUp_Pick = false;
					powerUpShow = false;
				}
				else if (IAS_Luck >= 10 && exitRandIA == 0){
					IAplayer2.powerUp_Pick = true;
					IAplayer1.powerUp_Pick = false;
					powerUpShow = false;
				}
			}
			if (powerUpAi_Set){
				if (IAplayer1.powerUp_Pick){
					IAplayer1.luck = ai_power;
					switch (ai_power){

					case Players::Switch:
						if (resetSwicth == 0){
							ball.SPEED.y *= -1.0f;
							resetSwicth = 1;
						}
						break;
					case Players::Slowdown:
						if (ball.SPEED.x < (-speedXBall - divMul_4))
							ball.SPEED.x = ball.SPEED.x + speedXBall;
						break;
					case Players::Bullet:
						if (ball.SPEED.x > 0)
							ball.SPEED.x = bulletPower;
						break;
					case Players::GodMode:
						pj1.BODY.height = screenHeigth;
						pj1.BODY.y = 0;
						break;
					case Players::Shield:
						shieldPowerUPAI(IAplayer1,IAplayer2);
						break;
					default:
						break;
					}
					IAplayer1.powerUp_Pick = false;
					if (IAplayer1.luck != GodMode)
						IAplayer1.luck = Empty;
					powerUpAi_Set = false;
				}
				else if (IAplayer2.powerUp_Pick){
					IAplayer2.luck = ai_power;
					switch (ai_power){

					case Players::Switch:
						ball.SPEED.y *= -1.0f;
						break;
					case Players::Slowdown:
						if (ball.SPEED.x > (speedXBall + divMul_4))
							ball.SPEED.x = ball.SPEED.x - speedXBall;
						break;
					case Players::Bullet:
						if (ball.SPEED.x < 0)
							ball.SPEED.x = -bulletPower;
						break;
					case Players::GodMode:
						pj2.BODY.height = screenHeigth;
						pj2.BODY.y = 0;
						break;
					case Players::Shield: 
						shieldPowerUPAI(IAplayer1, IAplayer2);
						break;
					default:
						break;
					}
					IAplayer2.powerUp_Pick = false;
					if (IAplayer2.luck != GodMode)
						IAplayer2.luck = Empty;
					powerUpAi_Set = false;
				}
			}
		}
		void shieldPowerUPAI(PJS & IAplayer1, PJS & IAplayer2){
			if (IAplayer1.luck == Shield){
				IAplayer1.shieldActive = true;
			}
			else if (IAplayer2.luck == Shield){
				IAplayer2.shieldActive = true;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void choosePaddle(){

			if (IsKeyPressed(KEY_RIGHT)){
				if (colorSelec <= (MAXCOL - 1))
					colorSelec++;
			}
			if (IsKeyPressed(KEY_LEFT)){
				if (colorSelec >= 0)
					colorSelec--;
			}
			if (colorSelec > (MAXCOL - 1))
				colorSelec = 0;
			if (colorSelec < 0)
				colorSelec = (MAXCOL - 1);

			DrawRectangleRec(pj1.BODY, pj1.selColor);
			DrawRectangleRec(pj2.BODY, pj2.selColor);

			if (IsKeyPressed(KEY_UP)){
				if (whatPj <= 2)
					whatPj++;
			}
			if (IsKeyPressed(KEY_DOWN)){
				if (whatPj >= 1)
					whatPj--;
			}
			if (whatPj > 2)
				whatPj = 1;
			if (whatPj < 1)
				whatPj = 2;

			switch (whatPj){
			case 1:
				switch (colorSelec){
				case 0:	pj1.selColor = colorpj[0];
					break;
				case 1: pj1.selColor = colorpj[1];
					break;
				case 2: pj1.selColor = colorpj[2];
					break;
				case 3: pj1.selColor = colorpj[3];
					break;
				case 4: pj1.selColor = colorpj[4];
					break;
				case 5: pj1.selColor = colorpj[5];
					break;
				case 6: pj1.selColor = colorpj[6];
					break;
				case 7: pj1.selColor = colorpj[7];
					break;
				default:
					break;
				}
				break;
			case 2:
				switch (colorSelec){
				case 0:	pj2.selColor = colorpj[0];
					break;
				case 1: pj2.selColor = colorpj[1];
					break;
				case 2: pj2.selColor = colorpj[2];
					break;
				case 3: pj2.selColor = colorpj[3];
					break;
				case 4: pj2.selColor = colorpj[4];
					break;
				case 5: pj2.selColor = colorpj[5];
					break;
				case 6: pj2.selColor = colorpj[6];
					break;
				case 7: pj2.selColor = colorpj[7];
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			DrawText("press [LEFT] & [RIGTH] to change color", C_CONTROLS_X, C_CONTROLS_Y4 + num100, fontSize, WHITE);
			DrawText("press [UP] & [DOWN] to choose pjs", C_CONTROLS_X, C_CONTROLS_Y5 + num100, fontSize, WHITE);
			DrawText("press [Y] to finish", C_CONTROLS_X, C_CONTROLS_Y6 + num100, fontSize, WHITE);

			if (IsKeyPressed(KEY_Y)){
				Menu::actualGameState = Menu::OPTIONS;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void chooseControls(){
			switch (whatPj){
			case 1: //PLAYER 1
				switch (actual){
				case 0:
					DrawText("---PJ1---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, YELLOW);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, WHITE);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, WHITE);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, WHITE);
					getKeyPj(pj1.UPk);
					DrawText("press the Key C to confirm the KEY: ", C_CONTROLS_X, C_CONTROLS_Y6, fontSize, WHITE);
					DrawText(FormatText("%c", (char)pj1.UPk), C_CONTROLS_X + num450, C_CONTROLS_Y6 + num50, fontSize, GREEN);
					break;
				case 1:
					DrawText("---PJ1---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, WHITE);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, YELLOW);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, WHITE);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, WHITE);
					getKeyPj(pj1.DOWNk);
					DrawText("press the Key C to confirm the KEY: ", C_CONTROLS_X, C_CONTROLS_Y6, fontSize, WHITE);
					DrawText(FormatText("%c", (char)pj1.DOWNk), C_CONTROLS_X + num450, C_CONTROLS_Y6 + num50, fontSize, GREEN);
					break;
				case 2:
					DrawText("---PJ1---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, WHITE);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, WHITE);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, YELLOW);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, WHITE);
					getKeyPj(pj1.TAKEPk);
					DrawText("press the Key C to confirm the KEY: ", C_CONTROLS_X, C_CONTROLS_Y6, fontSize, WHITE);
					DrawText(FormatText("%c", (char)pj1.TAKEPk), C_CONTROLS_X + num450, C_CONTROLS_Y6 + num50, fontSize, GREEN);
					break;
				case 3:
					DrawText("---PJ1---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, WHITE);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, WHITE);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, WHITE);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, YELLOW);
					getKeyPj(pj1.USEPk);
					DrawText("press the Key C to confirm the KEY: ", C_CONTROLS_X, C_CONTROLS_Y6, fontSize, WHITE);
					DrawText(FormatText("%c", (char)pj1.USEPk), C_CONTROLS_X + num450, C_CONTROLS_Y6 + num50, fontSize, GREEN);
					break;
				default:
					DrawText("---PJ1---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, WHITE);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, WHITE);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, WHITE);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, WHITE);
					break;
				}
				break;
			case 2: //PLAYER 2
				switch (actual){
				case 0:
					DrawText("---PJ2---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, YELLOW);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, WHITE);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, WHITE);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, WHITE);
					getKeyPj(pj2.UPk);
					DrawText("press the Key C to confirm the KEY: ", C_CONTROLS_X, C_CONTROLS_Y6, fontSize, WHITE);
					DrawText(FormatText("%c", (char)pj2.UPk), C_CONTROLS_X + num450, C_CONTROLS_Y6 + num50, fontSize, GREEN);
					break;
				case 1:
					DrawText("---PJ2---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, WHITE);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, YELLOW);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, WHITE);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, WHITE);
					getKeyPj(pj2.DOWNk);
					DrawText("press the Key C to confirm the KEY: ", C_CONTROLS_X, C_CONTROLS_Y6, fontSize, WHITE);
					DrawText(FormatText("%c", (char)pj2.DOWNk), C_CONTROLS_X + num450, C_CONTROLS_Y6 + num50, fontSize, GREEN);
					break;
				case 2:
					DrawText("---PJ2---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, WHITE);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, WHITE);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, YELLOW);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, WHITE);
					getKeyPj(pj2.TAKEPk);
					DrawText("press the Key C to confirm the KEY: ", C_CONTROLS_X, C_CONTROLS_Y6, fontSize, WHITE);
					DrawText(FormatText("%c", (char)pj2.TAKEPk), C_CONTROLS_X + num450, C_CONTROLS_Y6 + num50, fontSize, GREEN);
					break;
				case 3:
					DrawText("---PJ2---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, WHITE);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, WHITE);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, WHITE);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, YELLOW);
					getKeyPj(pj2.USEPk);
					DrawText("press the Key C to confirm the KEY: ", C_CONTROLS_X, C_CONTROLS_Y6, fontSize, WHITE);
					DrawText(FormatText("%c", (char)pj2.USEPk), C_CONTROLS_X + num450, C_CONTROLS_Y6 + num50, fontSize, GREEN);
					break;
				default:
					DrawText("---PJ2---", C_CONTROLS_X, C_CONTROLS_Y1, fontSize, ORANGE);
					DrawText("Move [UP]:", C_CONTROLS_X, C_CONTROLS_Y2, fontSize, WHITE);
					DrawText("Move [DOWN]:", C_CONTROLS_X, C_CONTROLS_Y3, fontSize, WHITE);
					DrawText("Take Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y4, fontSize, WHITE);
					DrawText("Use Power-Up: ", C_CONTROLS_X, C_CONTROLS_Y5, fontSize, WHITE);
					break;
				}
				break;
			default:
				break;
			}
			if (IsKeyPressed(KEY_UP))
				if (actual <= 4) actual--;
			if (IsKeyPressed(KEY_DOWN))
				if (actual >= 0) actual++;
			if (actual > 4) actual = 0;
			if (actual < 0) actual = 4;
			DrawText("press [Y] to finish", C_CONTROLS_X, C_CONTROLS_Y6 + num100, fontSize, WHITE);
			if (IsKeyPressed(KEY_RIGHT))
				if (whatPj <= 2) whatPj++;
			if (IsKeyPressed(KEY_LEFT))
				if (whatPj >= 1) whatPj--;
			if (whatPj > 2) whatPj = 1;
			if (whatPj < 1) whatPj = 2;

			if (IsKeyPressed(KEY_Y)){ Menu::actualGameState = Menu::OPTIONS; onControlSelect = false; }
		}
		//--------------------------------------------------------------------------------------------------
		void setWinnerPj(){
			if (pj1.GAMES == divMul_8){
				pj1.MATCHES++;
				pj1.WON = true;
			}
			if (pj2.GAMES == divMul_8){
				pj2.MATCHES++;
				pj2.WON = true;
			}
			if (pj1.GAMES == 8 || pj2.GAMES == 8){
				Menu::actualGameState = Menu::WIN;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void getKeyPj(int& pjKey){
			if (!gotKey){
				Key = GetKeyPressed();
				if (Key != 0){
					if (Key > 96) Key -= 32;
					setKey(pjKey, Key);
					gotKey = true;
				}
				else
					gotKey = false;
			}
			if (IsKeyPressed(KEY_C)){
				actual++;
				Key = 0;
				gotKey = false;
			}
		}
		//--------------------------------------------------------------------------------------------------
		void setKey(int& keypj, int& keySeted){
			keypj = keySeted;
		}
	}
}