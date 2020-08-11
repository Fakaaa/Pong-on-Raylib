#ifndef PLAYERS_H
#define PLAYERS_H
#include "loop.h"

namespace Players {

	struct PJS{
		Rectangle BODY;
		Vector2 SPEED;
		bool onTop;
		bool onBot;
		bool UP_Force;
		bool DOWN_Force;
		int GAMES;
		bool WON;
	};

	extern PJS pj1;
	extern PJS pj2;
	extern int fontSize;

	extern void InitializePjs();
	extern void DrawPjs(PJS& pjs);
	extern void Inputs(PJS& p1, PJS& p2);
	extern void CheckLimits(PJS& pjs);
}
#endif // !PLAYERS_H