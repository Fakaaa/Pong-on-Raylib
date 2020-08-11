#include "loop.h"

namespace Loop {

	bool onGame;

	void InitializeAll() {
		InitializeScreen();
		onGame = true;
	}

	void DrawAll() {

	}

	void MacroInputs() {
		if (IsKeyPressed(KEY_ESCAPE))
			onGame = false;

		if (!onGame)
			WindowShouldClose();
	}

	void MainLoop() {

		InitializeAll();

		while (!WindowShouldClose()){

			ClearBackground(BLACK);

			BeginDrawing();

			MacroInputs();

			DrawAll();

			EndDrawing();
		}

		CloseWindow();
	}
}