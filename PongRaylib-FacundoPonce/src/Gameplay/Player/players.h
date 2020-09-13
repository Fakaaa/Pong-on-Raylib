#ifndef PLAYERS_H
#define PLAYERS_H

#include "Gameplay/Screen/screen.h"

const int MAXCOL = 8;

namespace Pong{
	namespace Players {
	
		enum POWER_UPS{
			Switch = 1,
			Slowdown,
			Bullet,
			GodMode,
			Inversion,
			Shield,
			None,
			Empty
		};
	
		enum CONTROLS {
			UP,
			DOWN,
			TAKE_POWER,
			USE_POWER
		};
	
		struct PJS{
			Rectangle BODY;
			Vector2 SPEED;
			bool onTop;
			bool onBot;
			int GAMES;
			int MATCHES;
			bool WON;
			POWER_UPS luck;
			bool powerUp_Pick;
			bool usePowerUp;
			int godTime;
			int inverTime;
	
			int UPk;
			int DOWNk;
			int TAKEPk;
			int USEPk;
			int auxUPk;
			int auxDOWNk;
			int AuxKey;
			
			Rectangle shield;
			bool shieldActive;

			Color selColor;
		};
	
		extern int Key;
		extern bool gotKey;
	
		extern PJS pj1;
		extern PJS pj2;
		extern POWER_UPS powerup;
		extern POWER_UPS ai_power;
		
		extern bool powerUpPlayer_Set;
		extern bool powerUpAi_Set;
		extern float secondsCountP;
	
		extern float speedPlayers;
		extern float posBodyXP1;
		extern float posBodyYP1;
		extern float posBodyXP2;
		extern float posBodyYP2;
		extern float widthPj;
		extern float heightPj;
	
		extern int secsGTime;
		extern int secsINvTime;
	
		void initializePjs();
		void drawPjs(PJS& pjs);
		void drawPowerUpIn();
		void checkLimits(PJS& pjs);
		void inputs();
		void godModePowerUP();
		void shieldPowerUP();
		void inversePowerUP(PJS& pj);
		void disableInverse(PJS& pj);
		void makePowerUp();
		void usePowerUpPlayers();
		void ai_GameplayP1(PJS& IAplayer);
		void ai_GameplayP2(PJS& IAplayer);
		void makePowerUp_For_IA();
		void luck_For_IAs();
		void usePowerUp_For_IA(PJS& IAplayer1, PJS& IAplayer2);
		void shieldPowerUPAI(PJS& IAplayer1, PJS& IAplayer2);
		void choosePaddle();
		void chooseControls();
		void setWinnerPj();
		void getKeyPj(int& pjKey);
		void setKey(int& keypj, int& keySeted);
	}
}
#endif // !PLAYERS_H