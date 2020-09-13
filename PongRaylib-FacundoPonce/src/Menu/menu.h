#ifndef MENU_H
#define MENU_H

#include "Gameplay/Screen/screen.h"

namespace Pong{
	namespace Menu{
		enum STATE{
			NONE,
			MENU,
			BALL_SELECT,
			ON_SELECT,
			MODE_SELECT,
			CONTROL_SELECT,
			PLAYER_SELECT,
			VOLUM_SELECT,
			PAUSE,
			GAMEPLAY,
			RESET,
			WIN,
			RESTART,
			CONTROLS,
			OPTIONS,
			SCORE,
			EXIT,
			CREDITS
		};

		struct COLORMENU{
			CLITERAL(Color)colorTitle;
		};

		extern STATE previusGameState;
		extern STATE actualGameState;
		extern STATE auxGameState;
		extern bool onPause;

		void inputsMenu();
		void mainMenu();
		void ballSelec();
		void modeSelec();
		void controlSelec();
		void pause();
		void options();
		void showScores();
		void showWinner();
		void help();
		void exit();
		void credits();
		void alternateTitleColor();
	}
}
#endif // !MENU_H