#include "loop.h"
#include "players.h"
using namespace Players;

namespace Loop {

	bool onGame = false;

	void InitializeAll() {
		InitializeScreen();
		InitializePjs();
		SetTargetFPS(60);

		onGame = true;
	}

	void DrawAll() {
		DrawPjs(pj1);
		DrawPjs(pj2);
	}

	void MacroInputs() {
		Inputs(pj1,pj2);
		
		if (IsKeyPressed(KEY_ENTER)) {
			onGame = false;
		}
	}

	void MainLoop() {

		InitializeAll();

		while (onGame){
			
			MacroInputs();

			BeginDrawing();

			ClearBackground(BLACK);

			DrawAll();

			EndDrawing();
		}

		CloseWindow();
	}
}