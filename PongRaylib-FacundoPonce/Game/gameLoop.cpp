#include "loop.h"
#include "players.h"
using namespace Players;

namespace Loop {

	bool onGame;

	void InitializeAll() {
		InitializeScreen();
		onGame = true;
	}

	void DrawAll() {
		DrawPjs(pj1);
		DrawPjs(pj2);
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