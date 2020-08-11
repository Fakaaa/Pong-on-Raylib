#ifndef LOOP
#define LOOP
#include "screen.h"

namespace Loop {

	extern bool onGame;

	extern void GameLoop();
	extern void DrawAll();
	extern void InitializeAll();
	extern void MacroInputs();
}
#endif // !LOOP