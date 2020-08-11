#ifndef LOOP
#define LOOP
#include "screen.h"

using namespace Screen;

namespace Loop {

	extern bool onGame;

	extern void DrawAll();
	extern void InitializeAll();
	extern void MacroInputs();
	extern void MainLoop();
}
#endif // !LOOP