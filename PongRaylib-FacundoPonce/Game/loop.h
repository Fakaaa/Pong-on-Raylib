#ifndef LOOP_H
#define LOOP_H
#include "screen.h"

using namespace Screen;

namespace Loop {

	enum STATE{
		NONE,
		MENU,
		BALL_SELECT,
		ON_SELECT,
		PAUSE,
		GAMEPLAY,
		RESET,
		WIN,
		RESTART,
		CONTROLS,
		SCORE,
		EXIT
	};
	extern STATE actualGameState;
	extern STATE auxGameState;

	extern void DrawAll();
	extern void InitializeAll();
	extern void Fisicas();
	extern void MainLoop();
	extern void Gameplay();
	extern void States();
}
#endif // !LOOP_H