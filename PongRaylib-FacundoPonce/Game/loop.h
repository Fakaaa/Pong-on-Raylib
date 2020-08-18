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

	const int maxTime = 2;
	extern STATE actualGameState;
	extern STATE auxGameState;
	extern int gameFrames;
	extern int timer[maxTime];

	void DrawAll();
	void DrawTime();
	void InitializeAll();
	void Fisicas();
	void MainLoop();
	void Gameplay();
	void InputsMenu();
	void StatesFixed();
	void GameTime(int time[maxTime], int &frames);
}
#endif // !LOOP_H