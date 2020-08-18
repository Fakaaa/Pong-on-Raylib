#ifndef PLAYERS_H
#define PLAYERS_H
#include "loop.h"

namespace Players {

	enum POWER_UPS {
		Switch = 1,
		Slowdown,
		Bullet,
		GodMode,
		None,
		Empty
	};

	struct PJS{
		Rectangle BODY;
		Vector2 SPEED;
		bool onTop;
		bool onBot;
		int GAMES;
		bool WON;
		POWER_UPS luck;
		bool powerUp_Pick;
		bool usePowerUp;
		int godTime;
	};

	extern PJS pj1;
	extern PJS pj2;
	extern POWER_UPS powerup;
	extern int fontSize;
	extern bool powerUpSet;
	extern int auxFrames;

	extern void InitializePjs();
	extern void DrawPjs(PJS& pjs);
	void DrawPowerUpIn();
	extern void Inputs(PJS& p1, PJS& p2);
	extern void CheckLimits(PJS& pjs);
	void MakePowerUp();
	extern void GodModePowerUP();
}
#endif // !PLAYERS_H