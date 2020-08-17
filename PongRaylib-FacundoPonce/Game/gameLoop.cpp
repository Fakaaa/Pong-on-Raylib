#include "loop.h"
#include "players.h"
#include "ball.h"

using namespace Players;
using namespace Ball;

namespace Loop {

	STATE actualGameState; //Enum STATE, que determina el estado actual del juego
	STATE previusGameState; //Enum STATE, que determina el estado previo del juego
	STATE auxGameState;
	int gameFrames;
	int timer[maxTime];
	//----------------------------------------------------------------------------------------------------	
	void InitializeAll() { //Inicialización de todos los elementos usados en el gameplay
		if (actualGameState != RESTART)
			InitializeScreen();
		InitializePjs();
		gameFrames = 0;
		SetTargetFPS(60);
		actualGameState = MENU;
	}
	//----------------------------------------------------------------------------------------------------	
	void DrawAll() { //Dibujado de todos los elementos del juego
		DrawPjs(pj1);
		DrawPjs(pj2);
		DrawPowerUpIn();
		DrawLine();
		DrawBall();
		DrawTime();
	}
	//----------------------------------------------------------------------------------------------------	
	void DrawTime() {
		DrawText(FormatText("Min %i", static_cast<int>(timer[0])), screenWidth / 2 - 150, 0, fontSize, WHITE);
		DrawText(FormatText("seg %i", static_cast<int>(timer[1])), screenWidth / 2 + 30, 0, fontSize, WHITE);
	}
	//----------------------------------------------------------------------------------------------------	
	void Fisicas() { //Fisicas del juego, junto al input de ambos jugadores
		Inputs(pj1, pj2);
		MoveBall();
	}
	//----------------------------------------------------------------------------------------------------	
	void InputsMenu() {
		if (IsKeyPressed(KEY_E)) {
			if (previusGameState == PAUSE || previusGameState == MENU)
				actualGameState = EXIT;
		}
		if (IsKeyPressed(KEY_P)) {
			if (previusGameState == GAMEPLAY)
				actualGameState = PAUSE;
		}
		if (IsKeyPressed(KEY_O)) {
			if (previusGameState == PAUSE)
				actualGameState = GAMEPLAY;
			if (previusGameState == RESET)
				auxGameState = NONE;
		}
		if (IsKeyPressed(KEY_ENTER)) {
			if (previusGameState == MENU)
				actualGameState = BALL_SELECT;
		}
		if (IsKeyPressed(KEY_R)) {
			if (previusGameState == WIN)
				actualGameState = RESTART;
		}
		if (IsKeyPressed(KEY_C)) {
			if (previusGameState == MENU)
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
	}
	//----------------------------------------------------------------------------------------------------	
	void StatesFixed() {
		InputsMenu();
		switch (actualGameState){

		case Loop::MENU:
			DrawText("Pong On raylib", screenWidth / 2 - 400, 30, fontSize * 2, WHITE);
			DrawText("press [ENTER] to Start", screenWidth / 2 - 320, screenHeigth / 2, fontSize, WHITE);
			DrawText("press [E] to Exit", screenWidth / 2 - 320, screenHeigth / 1.5, fontSize, WHITE);
			DrawText("press [C] to See CONTROLS", screenWidth / 2 - 320, (screenHeigth / 1.5 - 80), fontSize, WHITE);
			previusGameState = MENU;
			break;
		case Loop::BALL_SELECT:
			actualGameState = ON_SELECT;
			break;
		case Loop::ON_SELECT:
			DrawText("press [LEFT] & [RIGHT] to Choose Color", screenWidth / 2 - 480, screenHeigth / 2 + 200, fontSize, WHITE);
			DrawText("press [Y] to Select", screenWidth / 2 - 240, screenHeigth / 1.5, fontSize, WHITE);
			ChooseColor();
			InitializeBall();
			break;
		case Loop::PAUSE:
			DrawText("PAUSE", screenWidth / 2 - 100, screenHeigth / 3, fontSize, YELLOW);
			DrawText("LETRA [O] To RESUME", screenWidth / 2 - 300, screenHeigth / 1.5, fontSize, YELLOW);
			DrawText("LETRA [E] To EXIT", screenWidth / 2 - 300, (screenHeigth / 1.5) - (fontSize + 10), fontSize, YELLOW);
			DrawText("LETRA [B] To Back Menu", screenWidth / 2 - 320, (screenHeigth / 1.5 - 150) - (fontSize + 10), fontSize, YELLOW);
			previusGameState = PAUSE;
			break;
		case Loop::GAMEPLAY:
			previusGameState = GAMEPLAY;
			break;
		case Loop::RESET:
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
			break;
		case Loop::WIN:
			if (pj1.WON)
				DrawText("PLAYER 1 WIN THE MATCH!!", screenWidth / 2 - 250, 130, fontSize, GREEN);
			if (pj2.WON)
				DrawText("PLAYER 2 WIN THE MATCH!!", screenWidth / 2 - 250, 130, fontSize, YELLOW);

			DrawText("Press [R] to start again!!", screenWidth / 2 - 250, 330, fontSize, WHITE);
			previusGameState = WIN;
			break;
		case Loop::CONTROLS:
			DrawText("Player 1 [W] & [S]", screenWidth / 2 - 310, (screenHeigth / 1.5 - 160) - (fontSize + 10), fontSize, YELLOW);
			DrawText("Player 2 [UP] & [DOWN]", screenWidth / 2 - 310, (screenHeigth / 1.5 - 90) - (fontSize + 10), fontSize, YELLOW);
			DrawText("Press [B] to BACK", screenWidth / 2 - 310, (screenHeigth / 1.5 + 90) - (fontSize + 10), fontSize, YELLOW);
			DrawText("Press [P] to PAUSE", screenWidth / 2 - 310, (screenHeigth / 1.5 - 240) - (fontSize + 10), fontSize, YELLOW);
			previusGameState = CONTROLS;
			break;
		case Loop::EXIT:
			DrawText("Are you sure?\n[YES] = ESC", screenWidth / 2 - 320, screenHeigth / 2, fontSize, WHITE);
			DrawText("[NO] = B", screenWidth / 2 - 320, screenHeigth / 1.5, fontSize, WHITE);
			previusGameState = EXIT;
			break;
		default:
				DrawText("Error se crasehoooo", screenWidth / 2 - 320, screenHeigth / 2, fontSize, WHITE);
			break;
		}
	}
	//----------------------------------------------------------------------------------------------------	
	void Gameplay() { //Gameplay: fisicas, dibujado y reinicio
		if (actualGameState != PAUSE && actualGameState != MENU && actualGameState == GAMEPLAY && actualGameState != EXIT) {
			Fisicas();
			DrawAll();
			if (pj1.GAMES == 8) {
				pj1.WON = true;
			}
			if (pj2.GAMES == 8) {
				pj2.WON = true;
			}
		}
		if (actualGameState == RESTART) {
			InitializeAll();
		}
		GameTime(timer,gameFrames);
	}
	//----------------------------------------------------------------------------------------------------	
	void MainLoop() { //Loop Principal del Juego
		InitializeAll();
		while (actualGameState != EXIT || !WindowShouldClose()) {
			StatesFixed();
			BeginDrawing();
			ClearBackground(BLACK);
			Gameplay();
			EndDrawing();
		}
		CloseWindow();
	}
	void GameTime(int time[maxTime], int &frames) {
		if(actualGameState != PAUSE && previusGameState != RESET)
			frames++;
		if (frames >= 60) {
			time[1]++;
			if (time[1] > 59 && time[1] <= 60) {
				time[1] = 0;
				time[0]++;
			}
			frames = 0;
		}

		if (previusGameState == MENU) {
			frames = 0;
			time[0] = 0;
			time[1] = 0;
		}
	}
}