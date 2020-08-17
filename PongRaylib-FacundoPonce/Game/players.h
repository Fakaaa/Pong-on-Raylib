#ifndef PLAYERS_H
#define PLAYERS_H
#include "loop.h"

namespace Players {

	enum POWER_UPS {
		Switch = 1,
		Slowdown,
		Bullet,
		None
	};

	struct PJS{
		Rectangle BODY;
		Vector2 SPEED;
		bool onTop;
		bool onBot;
		bool UP_Force;
		bool DOWN_Force;
		int GAMES;
		bool WON;
		POWER_UPS luck;
		bool powerUp_Pick;
		bool usePowerUp;
	};

	extern PJS pj1;
	extern PJS pj2;
	extern POWER_UPS powerup;
	extern int fontSize;
	extern bool powerUpSet;

	extern void InitializePjs();
	extern void DrawPjs(PJS& pjs);
	void DrawPowerUpIn();
	extern void Inputs(PJS& p1, PJS& p2);
	extern void CheckLimits(PJS& pjs);
	void MakePowerUp();
}
#endif // !PLAYERS_H