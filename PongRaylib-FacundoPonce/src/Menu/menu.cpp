#include "menu.h"

#include "Gameplay/Screen/screen.h"
#include "Gameplay/variables.h"
#include "Gameplay/Ball/ball.h"
#include "Gameplay/Player/players.h"
#include "Gameplay/Sfx/music.h"
#include "Gameplay/loop.h"

using namespace Pong;
using namespace Vars;

namespace Pong{
	namespace Menu{

		STATE previusGameState;
		STATE actualGameState;
		STATE auxGameState;
		COLORMENU colorTitle;
		static int growTitleColor;
		bool onPause;
		
		void inputsMenu(){
			if (IsKeyPressed(KEY_E)){
				if (previusGameState == PAUSE || previusGameState == MENU)
					actualGameState = EXIT;
			}
			if (IsKeyPressed(KEY_P)){
				if (previusGameState == GAMEPLAY){ actualGameState = PAUSE;	onPause = true; }
			}
			if (IsKeyPressed(KEY_O)){
				if (previusGameState == PAUSE){ actualGameState = GAMEPLAY; onPause = false; }
				if (previusGameState == RESET)
					auxGameState = NONE;
				if (previusGameState == MENU)
					actualGameState = OPTIONS;
			}
			if (IsKeyPressed(KEY_ENTER)){
				if (previusGameState == MENU)
					actualGameState = BALL_SELECT;
				if (previusGameState == EXIT)
					WindowShouldClose();
				if (previusGameState == OPTIONS)
					actualGameState = VOLUM_SELECT;
			}
			if (IsKeyPressed(KEY_R)){
				if (previusGameState == GAMEPLAY && actualGameState == WIN)
					actualGameState = RESTART;
			}
			if (IsKeyPressed(KEY_H)){
				if (previusGameState == MENU)
					actualGameState = CONTROLS;
				if (previusGameState == OPTIONS)
					actualGameState = PLAYER_SELECT;
			}
			if (IsKeyPressed(KEY_C)){
				if (previusGameState == MENU)
					actualGameState = CREDITS;
				if (previusGameState == OPTIONS)
					actualGameState = CONTROL_SELECT;
			}
			if (IsKeyPressed(KEY_B)){
				if (actualGameState == WIN){
					Loop::initializeAll();
					//actualGameState = MENU;
				}
				else if (actualGameState == PAUSE)
					auxGameState = PAUSE;
				if (previusGameState == PAUSE || previusGameState == CONTROLS || previusGameState == CREDITS){
					actualGameState = RESTART;
					Loop::initializeAll();
					actualGameState = MENU;
				}
				else if (actualGameState == EXIT && auxGameState == PAUSE){
					actualGameState = PAUSE;
				}
				else{
					actualGameState = MENU;
				}
				if (actualGameState == OPTIONS){
					actualGameState = MENU;
				}
			}
		}
		//----------------------------------------------------------------------------------------------------	
		void mainMenu(){
			alternateTitleColor();
			DrawText(" -Dubstep Pong-", MENU_TITLE_X, MENU_TITLE_Y, static_cast<int>(fontSize * divMul_2), colorTitle.colorTitle);
			DrawText("press [ENTER] to Start", MENU_X, MENU_Y, fontSize, WHITE);
			DrawText("press [H] to Help", MENU_X, MENU_Y_2, fontSize, WHITE);
			DrawText("press [C] to Credits", MENU_X, MENU_Y_3, fontSize, WHITE);
			DrawText("press [O] to Options", MENU_X, MENU_Y_5, fontSize, WHITE);
			DrawText("press [E] to Exit", MENU_X, MENU_Y_4, fontSize, WHITE);

			DrawText("v1.0", num10, screenHeigth-fontSize2, fontSize2, WHITE);
			previusGameState = MENU;
		}
		//----------------------------------------------------------------------------------------------------	
		void ballSelec(){
			DrawText("press [LEFT] & [RIGHT] to Choose Color", ONSELEC_X, ONSELEC_Y, fontSize, WHITE);
			DrawText("press [Y] to Select", ONSELEC_X_2, ONSELEC_Y_2, fontSize, WHITE);
			Ball::chooseColor();
			Ball::initializeBall();
		}
		//----------------------------------------------------------------------------------------------------	
		void modeSelec(){
			DrawText("press [LEFT] & [RIGHT] to Choose Game Mode", ONSELEC_X, ONSELEC_Y, fontSize, WHITE);
			DrawText("press [Y] to Select", ONSELEC_X_2, ONSELEC_Y_2, fontSize, WHITE);
		}
		//----------------------------------------------------------------------------------------------------	
		void controlSelec(){
			DrawText("Press [UP & DOWN] to choose what KEY", static_cast<int>(screenWidth/divMul_2), num10, fontSize2, GREEN);
			DrawText("Press [LEFT & RIGTH] to choose PJS", static_cast<int>(screenWidth/divMul_2), num50, fontSize2, GREEN);
			DrawText("Press a Key and confirm", static_cast<int>(screenWidth/divMul_2), num100, fontSize2, GREEN);
			onControlSelect = true;
			if (onControlSelect)
				Players::chooseControls();
		}
		//----------------------------------------------------------------------------------------------------	
		void pause(){
			Loop::drawAll();
			Screen::drawBackP();
			DrawText("PAUSE", PAUSE_X, PAUSE_Y, fontSize, YELLOW);
			DrawText("LETRA [O] To RESUME", PAUSE_X_2, PAUSE_Y_2, fontSize, YELLOW);
			DrawText("LETRA [E] To EXIT", PAUSE_X_2, PAUSE_Y_3, fontSize, YELLOW);
			DrawText("LETRA [B] To Back Menu", PAUSE_X_4, PAUSE_Y_4, fontSize, YELLOW);
			previusGameState = PAUSE;
			auxGameState = EXIT;
		}
		//----------------------------------------------------------------------------------------------------	
		void options(){
			DrawText(" [ENTER] Audio ", OPTIONS_X, OPTIONS_Y, fontSize, WHITE);
			DrawText(" [H] Set Pjs color", OPTIONS_X, OPTIONS_Y_2, fontSize, WHITE);
			DrawText(" [C] Set Pjs Controls", OPTIONS_X, OPTIONS_Y_3, fontSize, WHITE);
			DrawText(" [B] to Back", OPTIONS_X, OPTIONS_Y_5, fontSize, WHITE);
			previusGameState = OPTIONS;
		}
		//----------------------------------------------------------------------------------------------------	
		void showScores(){
			AudioGame::playAudioGame();
			if (Ball::scorePj == 1){
				DrawText("Player 1 SCORES!!", RESET_X, RESET_Y, fontSize, WHITE);
			}
			else if (Ball::scorePj == 2){
				DrawText("Player 2 SCORES!!", RESET_X, RESET_Y, fontSize, WHITE);
			}
			previusGameState = RESET;
			DrawText("Press [O] To Resume!!", RESET_X, RESET_Y_2, fontSize, GREEN);
			if (auxGameState != SCORE){
				actualGameState = GAMEPLAY;
			}
		}
		//----------------------------------------------------------------------------------------------------	
		void showWinner(){
			if (Players::pj1.WON)
				DrawText("PLAYER 1 WIN THE MATCH!!", WIN_X, WIN_Y, fontSize, GREEN);
			if (Players::pj2.WON)
				DrawText("PLAYER 2 WIN THE MATCH!!", WIN_X, WIN_Y, fontSize, YELLOW);

			DrawText("Press [R] to start again!!", WIN_X, WIN_Y_2, fontSize, WHITE);
			DrawText("Press [B] to Back menu..", WIN_X, WIN_Y_2 + num250, fontSize, WHITE);
			previusGameState = GAMEPLAY;
		}
		//----------------------------------------------------------------------------------------------------	
		void help(){
			DrawText("Player 1", CONTROLS_X, CONTROLS_Y, fontSize, YELLOW);
			DrawText(FormatText("UP: %c", (char)Players::pj1.UPk), CONTROLS_X + num250, CONTROLS_Y, fontSize, YELLOW);
			DrawText(FormatText("DOWN: %c", (char)Players::pj1.DOWNk), CONTROLS_X + (num250*divMul_2), CONTROLS_Y, fontSize, YELLOW);
			DrawText(FormatText("TAKE: %c", (char)Players::pj1.TAKEPk), CONTROLS_X + num250, CONTROLS_Y_2, fontSize, YELLOW);
			DrawText(FormatText("USE: %c", (char)Players::pj1.USEPk), CONTROLS_X + (num250*divMul_2), CONTROLS_Y_2, fontSize, YELLOW);
			DrawText("Player 2", CONTROLS_X, CONTROLS_Y_3, fontSize, GREEN);
			DrawText(FormatText("UP: %c", (char)Players::pj2.UPk), CONTROLS_X + num250, CONTROLS_Y_3, fontSize, GREEN);
			DrawText(FormatText("DOWN: %c", (char)Players::pj2.DOWNk), CONTROLS_X + (num250*divMul_2), CONTROLS_Y_3, fontSize, GREEN);
			DrawText(FormatText("TAKE: %c", (char)Players::pj2.TAKEPk), CONTROLS_X + num250, CONTROLS_Y_4, fontSize, GREEN);
			DrawText(FormatText("USE: %c", (char)Players::pj2.USEPk), CONTROLS_X + (num250*divMul_2), CONTROLS_Y_4, fontSize, GREEN);
			DrawText("Press [B] to BACK", CONTROLS_X, CONTROLS_Y_5, fontSize, WHITE);
			DrawText("Press [P] to PAUSE", CONTROLS_X, CONTROLS_Y_6, fontSize, VIOLET);
			previusGameState = CONTROLS;
		}
		//----------------------------------------------------------------------------------------------------	
		void exit(){
			DrawText("Are you sure?\n[YES] = Esc", EXIT_X, EXIT_Y, fontSize, WHITE);
			DrawText("[NO] = B", EXIT_X, EXIT_Y_2, fontSize, WHITE);
			if (previusGameState == PAUSE)
				auxGameState = PAUSE;
			previusGameState = EXIT;
		}
		//----------------------------------------------------------------------------------------------------	
		void credits(){
			DrawText("Song 1: Doom Eternal OST - The Only Thing They Fear is You", CREDITS_X_1, CREDITS_Y_1, fontSize2, RED);
			DrawText("Song 2: KROWW - HYSTERIA", CREDITS_X_1, CREDITS_Y_2, fontSize2, YELLOW);
			DrawText("Song 3: SYN - Steel", CREDITS_X_1, CREDITS_Y_3, fontSize2, ORANGE);
			DrawText("Song 4: Evilwave & Antima - Tinnitus", CREDITS_X_1, CREDITS_Y_4, fontSize2, VIOLET);
			DrawText("Background: Usuario anonimo 4chan subidas en Imgur", CREDITS_X_1, CREDITS_Y_6, fontSize2, VIOLET);
			DrawText("Dev: Facundo Mateo Ponce				Mail: mrfacu125@gmail.com", CREDITS_X_1, CREDITS_Y_6 - num100, fontSize2, GREEN);
			DrawText("Librerias de programacion: RAYLIB", CREDITS_X_1, CREDITS_Y_6 - (num100 + num50), fontSize2, BROWN);

			DrawText("v1.0", num10, screenHeigth - fontSize2, fontSize2, WHITE);
			DrawText("Press [B] to BACK", CREDITS_X_2, CREDITS_Y_5, fontSize, WHITE);
			previusGameState = CREDITS;
		}
		//----------------------------------------------------------------------------------------------------	
		void alternateTitleColor(){
			switch (growTitleColor){
			case 0:
				colorTitle.colorTitle = RED;
				break;
			case 5:
				colorTitle.colorTitle = BLUE;
				break;
			case 10:
				colorTitle.colorTitle = ORANGE;
				break;
			case 15:
				colorTitle.colorTitle = YELLOW;
				break;
			case 30:
				colorTitle.colorTitle = VIOLET;
				break;
			case 35:
				colorTitle.colorTitle = GREEN;
				break;
			case 40:
				colorTitle.colorTitle = WHITE;
				break;
			case 45:
				colorTitle.colorTitle = BROWN;
				break;
			}
			if(growTitleColor >= 0 && growTitleColor <= 45)
				growTitleColor++;
			if (growTitleColor >= 45)
				growTitleColor = 0;
		}
	}
}