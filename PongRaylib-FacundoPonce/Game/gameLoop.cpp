#include "loop.h"
#include "players.h"
#include "ball.h"

using namespace Players;
using namespace Ball;

namespace Loop {

	STATE gameState;

	void InitializeAll() {
		InitializeScreen();
		InitializePjs();
		InitializeBall();
		SetTargetFPS(60);

		gameState = MENU;
	}

	void DrawAll() {
		DrawUI();
		DrawPjs(pj1);
		DrawPjs(pj2);
		DrawBall();
	}

	void MacroInputs() {
		Inputs(pj1,pj2);
		MoveBall();
	}

	void States() {
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

		if (gameState == MENU) {
			DrawText("Pong On raylib", screenWidth / 2 - 200, 0, fontSize, WHITE);
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

			DrawText("", screenWidth / 2 - 200, 0, fontSize, WHITE);
			DrawText("press [ENTER] to Start", screenWidth / 2 - 320, screenHeigth / 2, fontSize, WHITE);
			DrawText("press [E] to Exit", screenWidth / 2 - 320, screenHeigth / 1.5, fontSize, WHITE);
		}
	}

	void Gameplay() {
		if (gameState != PAUSE && gameState != MENU && gameState == GAMEPLAY && gameState != EXIT) {
			MacroInputs();
			DrawAll();
		}
	}

	void MainLoop() {

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