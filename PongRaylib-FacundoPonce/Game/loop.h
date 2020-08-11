#ifndef LOOP_H
#define LOOP_H
#include "screen.h"

using namespace Screen;

namespace Loop {

	enum STATE{
		NONE,
		MENU,
		PAUSE,
		GAMEPLAY,
		RESET,
		EXIT
	};
	extern STATE gameState;

	extern void DrawAll();
	extern void InitializeAll();
	extern void MacroInputs();
	extern void MainLoop();
	extern void Gameplay();
	extern void States();
}
#endif // !LOOP_H