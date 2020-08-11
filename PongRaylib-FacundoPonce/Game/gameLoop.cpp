#include "loop.h"
#include "players.h"
#include "ball.h"

using namespace Players;
using namespace Ball;

namespace Loop {

	STATE gameState; //Enum STATE, que determina el estado actual del juego
		//----------------------------------------------------------------------------------------------------	
		void InitializeAll() { //Inicialización de todos los elementos usados en el gameplay
			if (gameState != RESTART)
				InitializeScreen();
			InitializePjs();
			InitializeBall();
			SetTargetFPS(60);
			gameState = MENU;
		}
		//----------------------------------------------------------------------------------------------------	
		void DrawAll() { //Dibujado de todos los elementos del juego
			DrawLine();
			DrawPjs(pj1);
			DrawPjs(pj2);
			DrawBall();
		}
		//----------------------------------------------------------------------------------------------------	
		void Fisicas() { //Fisicas del juego, junto al input de ambos jugadores
			Inputs(pj1,pj2);
			MoveBall();
		}
		//----------------------------------------------------------------------------------------------------	
		void States() { //Estados del juego e inputs de control
			if (IsKeyPressed(KEY_E)) {
				gameState = EXIT;
			}
			if (IsKeyPressed(KEY_P)) {
				gameState = PAUSE;
			}
			if (IsKeyPressed(KEY_O)) {
				gameState = GAMEPLAY;
			}
			if (IsKeyPressed(KEY_ENTER)) {
				gameState = GAMEPLAY;
			}
			if (IsKeyPressed(KEY_R)) {
				gameState = RESTART;
			}
			if (gameState == MENU) {
				DrawText("Pong On raylib", screenWidth / 2 - 400, 30, fontSize * 2, WHITE);
				DrawText("press [ENTER] to Start", screenWidth / 2 - 320, screenHeigth / 2, fontSize, WHITE);
				DrawText("press [E] to Exit", screenWidth / 2 - 320, screenHeigth / 1.5, fontSize, WHITE);
			}
			if (gameState == PAUSE) {
				DrawText("PAUSE", screenWidth / 2 - 100, screenHeigth / 3, fontSize, YELLOW);
				DrawText("LETRA [O] To RESUME", screenWidth / 2 - 300, screenHeigth / 1.5, fontSize, YELLOW);
				DrawText("LETRA [E] To EXIT",screenWidth / 2 - 300,(screenHeigth / 1.5) - (fontSize + 10), fontSize, YELLOW);
			}
			if (gameState == EXIT) {
				DrawText("Are you sure?\n[YES] = ESC", screenWidth / 2 - 320, screenHeigth / 2, fontSize, WHITE);
				DrawText("[NO] = O", screenWidth / 2 - 320, screenHeigth / 1.5, fontSize, WHITE);
			}
			if (gameState == RESET) {
				if (scorePj == 1) {
					DrawText("Player 1 SCORES!!", screenWidth / 2 - 250, 30, fontSize, WHITE);
				}
				else if (scorePj == 2) {
					DrawText("Player 2 SCORES!!", screenWidth / 2 - 250, 30, fontSize, WHITE);
				}
				gameState = GAMEPLAY;
			}
			if (gameState == WIN) {
				if(pj1.WON)
					DrawText("PLAYER 1 WIN THE MATCH!!", screenWidth / 2 - 250, 130, fontSize, GREEN);
				if(pj2.WON)
					DrawText("PLAYER 2 WIN THE MATCH!!", screenWidth / 2 - 250, 130, fontSize, YELLOW);

				DrawText("Press [R] to start again!!", screenWidth / 2 - 250, 330, fontSize, WHITE);
			}
		}
		//----------------------------------------------------------------------------------------------------		
		void Gameplay() { //Gameplay: fisicas, dibujado y reinicio
			if (gameState != PAUSE && gameState != MENU && gameState == GAMEPLAY && gameState != EXIT) {
				Fisicas();
				DrawAll();
				if(pj1.GAMES == 8) {
					pj1.WON = true;
				}
				if (pj2.GAMES == 8) {
					pj2.WON = true;
				}
			}
			if (gameState == RESTART) {
				InitializeAll();
			}
		}
		//----------------------------------------------------------------------------------------------------	
		void MainLoop() { //Loop Principal del Juego
			InitializeAll();
			while (gameState != EXIT || !WindowShouldClose()){
				States();
				BeginDrawing();
				ClearBackground(BLACK);
				Gameplay();
				EndDrawing();
			}
			CloseWindow();
		}
}