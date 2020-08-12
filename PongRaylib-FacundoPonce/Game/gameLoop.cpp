#include "loop.h"
#include "players.h"
#include "ball.h"

using namespace Players;
using namespace Ball;

namespace Loop {

	STATE actualGameState; //Enum STATE, que determina el estado actual del juego
	STATE previusGameState; //Enum STATE, que determina el estado previo del juego
	STATE auxGameState;
		//----------------------------------------------------------------------------------------------------	
		void InitializeAll() { //Inicialización de todos los elementos usados en el gameplay
			if (actualGameState != RESTART)
				InitializeScreen();
			InitializePjs();
			SetTargetFPS(60);
			actualGameState = MENU;
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
				if(previusGameState == PAUSE || previusGameState == MENU)
					actualGameState = EXIT;
			}
			if (IsKeyPressed(KEY_P)) {
				if(previusGameState == GAMEPLAY)
					actualGameState = PAUSE;
			}
			if (IsKeyPressed(KEY_O)) {
				if(previusGameState == PAUSE)
					actualGameState = GAMEPLAY;
				if (previusGameState == RESET)
					auxGameState = NONE;
			}
			if (IsKeyPressed(KEY_ENTER)) {
				if(previusGameState == MENU)
					actualGameState = BALL_SELECT;
			}
			if (IsKeyPressed(KEY_R)) {
				if(previusGameState == WIN)
					actualGameState = RESTART;
			}
			if (IsKeyPressed(KEY_C)) {
				if(previusGameState == MENU)
					actualGameState = CONTROLS;
			}
			if (IsKeyPressed(KEY_B)) {
				if (previusGameState == PAUSE || previusGameState == CONTROLS || previusGameState == EXIT) {
					if (previusGameState == PAUSE) {
						actualGameState = RESTART;
						InitializeAll();
					}
						actualGameState = MENU;
				}
			}
			if (actualGameState == MENU) {
				DrawText("Pong On raylib", screenWidth / 2 - 400, 30, fontSize * 2, WHITE);
				DrawText("press [ENTER] to Start", screenWidth / 2 - 320, screenHeigth / 2, fontSize, WHITE);
				DrawText("press [E] to Exit", screenWidth / 2 - 320, screenHeigth / 1.5, fontSize, WHITE);
				DrawText("press [C] to See CONTROLS", screenWidth / 2 - 320, (screenHeigth / 1.5 - 80), fontSize, WHITE);
				previusGameState = MENU;
			}
			if (actualGameState == BALL_SELECT) {
				actualGameState = ON_SELECT;
			}
			if (actualGameState == ON_SELECT) {
				DrawText("press [LEFT] & [RIGHT] to Choose Color", screenWidth / 2 - 480, screenHeigth / 2 + 200, fontSize, WHITE);
				DrawText("press [Y] to Select", screenWidth / 2 - 240, screenHeigth / 1.5, fontSize, WHITE);
				ChooseColor();
				InitializeBall();
			}
			if (actualGameState == PAUSE) {
				DrawText("PAUSE", screenWidth / 2 - 100, screenHeigth / 3, fontSize, YELLOW);
				DrawText("LETRA [O] To RESUME", screenWidth / 2 - 300, screenHeigth / 1.5, fontSize, YELLOW);
				DrawText("LETRA [E] To EXIT", screenWidth / 2 - 300, (screenHeigth / 1.5) - (fontSize + 10), fontSize, YELLOW);
				DrawText("LETRA [B] To Back Menu",screenWidth / 2 - 320,(screenHeigth / 1.5 - 150) - (fontSize + 10), fontSize, YELLOW);
				previusGameState = PAUSE;
			}
			if (actualGameState == EXIT) {
				DrawText("Are you sure?\n[YES] = ESC", screenWidth / 2 - 320, screenHeigth / 2, fontSize, WHITE);
				DrawText("[NO] = B", screenWidth / 2 - 320, screenHeigth / 1.5, fontSize, WHITE);
				previusGameState = EXIT;
			}
			if (actualGameState == RESET) {
					if (scorePj == 1) {
						DrawText("Player 1 SCORES!!", screenWidth / 2 - 250, 430, fontSize, WHITE);
					}
					else if (scorePj == 2) {
						DrawText("Player 2 SCORES!!", screenWidth / 2 - 250, 430, fontSize, WHITE);
					}
				previusGameState = RESET;
				DrawText("Press [O] To Resume!!", screenWidth / 2 - 250, 470, fontSize, GREEN);
					if (auxGameState != SCORE) {
						actualGameState = GAMEPLAY;
					}
			}
			if (actualGameState == GAMEPLAY) {
				previusGameState = GAMEPLAY;
			}
			if (actualGameState == WIN) {
				if(pj1.WON)
					DrawText("PLAYER 1 WIN THE MATCH!!", screenWidth / 2 - 250, 130, fontSize, GREEN);
				if(pj2.WON)
					DrawText("PLAYER 2 WIN THE MATCH!!", screenWidth / 2 - 250, 130, fontSize, YELLOW);

				DrawText("Press [R] to start again!!", screenWidth / 2 - 250, 330, fontSize, WHITE);
				previusGameState = WIN;
			}
			if (actualGameState == CONTROLS) {
				DrawText("Player 1 [W] & [S]", screenWidth / 2 - 310, (screenHeigth / 1.5 - 160) - (fontSize + 10), fontSize, YELLOW);
				DrawText("Player 2 [UP] & [DOWN]", screenWidth / 2 - 310, (screenHeigth / 1.5 - 90) - (fontSize + 10), fontSize, YELLOW);
				DrawText("Press [B] to BACK", screenWidth / 2 - 310, (screenHeigth / 1.5 + 90) - (fontSize + 10), fontSize, YELLOW);
				DrawText("Press [P] to PAUSE", screenWidth / 2 - 310, (screenHeigth / 1.5 - 240) - (fontSize + 10), fontSize, YELLOW);
				previusGameState = CONTROLS;
			}
		}
		//----------------------------------------------------------------------------------------------------		
		void Gameplay() { //Gameplay: fisicas, dibujado y reinicio
			if (actualGameState != PAUSE && actualGameState != MENU && actualGameState == GAMEPLAY && actualGameState != EXIT) {
				Fisicas();
				DrawAll();
				if(pj1.GAMES == 8) {
					pj1.WON = true;
				}
				if (pj2.GAMES == 8) {
					pj2.WON = true;
				}
			}
			if (actualGameState == RESTART) {
				InitializeAll();
			}
		}
		//----------------------------------------------------------------------------------------------------	
		void MainLoop() { //Loop Principal del Juego
			InitializeAll();
			while (actualGameState != EXIT || !WindowShouldClose()){
				States();
				BeginDrawing();
				ClearBackground(BLACK);
				Gameplay();
				EndDrawing();
			}
			CloseWindow();
		}
}