#ifndef VARIABLES_H
#define VARIABLES_H

namespace Pong{
	namespace Vars {

		extern int fontSize;
		extern int fontSize2;

		extern int maxSec;
		extern int maxMin;
		//MAGIC NUMBERS
		extern int num10;
		extern int num50;
		extern int num80;
		extern int num100;
		extern int num250;
		extern int num300;
		extern int num400;
		extern int num450;
		extern float divMul_1_5;
		extern int divMul_2;
		extern int divMul_3;
		extern int divMul_4;
		extern int divMul_6;
		extern int divMul_8;
		extern int maxFrames;
		extern bool onControlSelect;

		// VARIABLES POS PARA LOS DIBUJADOS
		extern int MENU_TITLE_X;
		extern int MENU_TITLE_Y;
		extern int MENU_X;
		extern int MENU_Y;
		extern int MENU_Y_2;
		extern int MENU_Y_3;
		extern int MENU_Y_4;
		extern int MENU_Y_5;

		extern int ONSELEC_X;
		extern int ONSELEC_X_2;
		extern int ONSELEC_Y;
		extern int ONSELEC_Y_2;

		extern int ONSELECT_MODE_X;
		extern int ONSELECT_MODE_Y;

		extern int PAUSE_X;
		extern int PAUSE_X_2;
		extern int PAUSE_X_4;
		extern int PAUSE_Y;
		extern int PAUSE_Y_2;
		extern int PAUSE_Y_3;
		extern int PAUSE_Y_4;

		extern int RESET_X;
		extern int RESET_Y;
		extern int RESET_Y_2;

		extern int WIN_X;
		extern int WIN_Y;
		extern int WIN_Y_2;

		extern int CONTROLS_X;
		extern int CONTROLS_Y;
		extern int CONTROLS_Y_2;
		extern int CONTROLS_Y_3;
		extern int CONTROLS_Y_4;
		extern int CONTROLS_Y_5;
		extern int CONTROLS_Y_6;

		extern int OPTIONS_X;
		extern int OPTIONS_Y;
		extern int OPTIONS_Y_2;
		extern int OPTIONS_Y_3;
		extern int OPTIONS_Y_4;
		extern int OPTIONS_Y_5;
		extern int OPTIONS_Y_6;

		extern int C_CONTROLS_X;
		extern int C_CONTROLS_Y1;
		extern int C_CONTROLS_Y2;
		extern int C_CONTROLS_Y3;
		extern int C_CONTROLS_Y4;
		extern int C_CONTROLS_Y5;
		extern int C_CONTROLS_Y6;

		extern int CREDITS_X_1;
		extern int CREDITS_X_2;
		extern int CREDITS_Y_1;
		extern int CREDITS_Y_2;
		extern int CREDITS_Y_3;
		extern int CREDITS_Y_4;
		extern int CREDITS_Y_5;
		extern int CREDITS_Y_6;

		extern int EXIT_X;
		extern int EXIT_Y;
		extern int EXIT_Y_2;

		extern int D_TIME_X;
		extern int D_TIME_X_2;

		void initVariables();
	}
}
#endif // !VARIABLES_H