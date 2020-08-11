#ifndef LOOP_H
#define LOOP_H
#include "screen.h"

using namespace Screen;

namespace Loop {

	enum STATE{
		MENU,
		PAUSE,
		GAMEPLAY,
		RESET,
		WIN,
		RESTART,
		EXIT
	};
	extern STATE gameState;

	extern void DrawAll();
	extern void InitializeAll();
	extern void Fisicas();
	extern void MainLoop();
	extern void Gameplay();
	extern void States();
}
#endif // !LOOP_H