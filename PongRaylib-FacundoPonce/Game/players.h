#ifndef PLAYERS
#define PLAYERS
#include "loop.h"

namespace Players {

	struct PJS{
		Rectangle BODY;
		float SPEED;
		bool onTop;
		bool onBot;
	};

	extern PJS pj1;
	extern PJS pj2;

	extern void InitializePjs();
	extern void DrawPjs(PJS& pjs);
	extern void Inputs(PJS& p1, PJS& p2);
	extern void CheckLimits(PJS& pjs);
}
#endif // !PLAYERS