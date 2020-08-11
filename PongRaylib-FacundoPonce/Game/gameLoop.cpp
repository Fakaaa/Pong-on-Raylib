#include "loop.h"
#include "players.h"
#include "ball.h"

using namespace Players;
using namespace Ball;

namespace Loop {

	bool onGame = false;

	void InitializeAll() {
		InitializeScreen();
		InitializePjs();
		InitializeBall();
		SetTargetFPS(60);

		onGame = true;
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