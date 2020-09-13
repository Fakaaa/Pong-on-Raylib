#include "variables.h"

#include "Gameplay/Sfx/music.h"

namespace Pong{
	namespace Vars{

		int fontSize;
		int fontSize2;

		int maxSec;
		int maxMin;

		int num10;
		int num50;
		int num80;
		int num100;
		int num250;
		int num300;
		int num400;
		int num450;
		float divMul_1_5;
		int divMul_2;
		int divMul_3;
		int divMul_4;
		int divMul_6;
		int divMul_8;
		int maxFrames;
		int KeySelec;
		bool onControlSelect;

		int MENU_TITLE_X;
		int MENU_TITLE_Y;
		int MENU_X;
		int MENU_Y;
		int MENU_Y_2;
		int MENU_Y_3;
		int MENU_Y_4;
		int MENU_Y_5;

		int ONSELEC_X;
		int ONSELEC_X_2;
		int ONSELEC_Y;
		int ONSELEC_Y_2;

		int ONSELECT_MODE_X;
		int ONSELECT_MODE_Y;

		int PAUSE_X;
		int PAUSE_X_2;
		int PAUSE_X_4;
		int PAUSE_Y;
		int PAUSE_Y_2;
		int PAUSE_Y_3;
		int PAUSE_Y_4;

		int RESET_X;
		int RESET_Y;
		int RESET_Y_2;

		int WIN_X;
		int WIN_Y;
		int WIN_Y_2;

		int CONTROLS_X;
		int CONTROLS_Y;
		int CONTROLS_Y_2;
		int CONTROLS_Y_3;
		int CONTROLS_Y_4;
		int CONTROLS_Y_5;
		int CONTROLS_Y_6;

		int OPTIONS_X;
		int OPTIONS_Y;
		int OPTIONS_Y_2;
		int OPTIONS_Y_3;
		int OPTIONS_Y_4;
		int OPTIONS_Y_5;
		int OPTIONS_Y_6;

		int C_CONTROLS_X;
		int C_CONTROLS_Y1;
		int C_CONTROLS_Y2;
		int C_CONTROLS_Y3;
		int C_CONTROLS_Y4;
		int C_CONTROLS_Y5;
		int C_CONTROLS_Y6;

		int CREDITS_X_1;
		int CREDITS_X_2;
		int CREDITS_Y_1;
		int CREDITS_Y_2;
		int CREDITS_Y_3;
		int CREDITS_Y_4;
		int CREDITS_Y_5;
		int CREDITS_Y_6;

		int EXIT_X;
		int EXIT_Y;
		int EXIT_Y_2;

		int D_TIME_X;
		int D_TIME_X_2;

		void initVariables(){
			onControlSelect = false;
			maxFrames = 80;
			maxSec = 60;
			maxMin = 60;
			num10 = 10;
			num50 = 50;
			num80 = 80;
			num100 = 100;
			num250 = 250;
			num300 = 300;
			num400 = 400;
			num450 = 450;
			divMul_1_5 = 1.5f;
			divMul_2 = 2;
			divMul_3 = 3;
			divMul_4 = 4;
			divMul_6 = 6;
			divMul_8 = 8;
			fontSize = num50;
			fontSize2 = (num10 * divMul_3);
			AudioGame::audioGame.chooseGameplayMusic = 0;
			KeySelec = 0;
			//----------------------------------------------------------------------------------------------------	
			D_TIME_X = screenWidth / divMul_2 - (num250 - num100);
			D_TIME_X_2 = screenWidth / divMul_2 + (num10*divMul_3);
			//----------------------------------------------------------------------------------------------------	
			MENU_TITLE_X = static_cast<int>(screenWidth / divMul_2 - num400);
			MENU_X = static_cast<int>(screenWidth / divMul_2 - (num300 + (num10*divMul_2)));
			MENU_TITLE_Y = static_cast<int>(num10*divMul_3);
			MENU_Y = static_cast<int>(screenHeigth / divMul_2);
			MENU_Y_2 = static_cast<int>(screenHeigth - num400);
			MENU_Y_3 = static_cast<int>(screenHeigth / divMul_1_5);
			MENU_Y_4 = static_cast<int>(screenHeigth - num100);
			MENU_Y_5 = static_cast<int>(screenHeigth - num250);
			//----------------------------------------------------------------------------------------------------	
			ONSELEC_X = static_cast<int>(screenWidth / divMul_2 - (num400 + (num10*divMul_8)));
			ONSELEC_X_2 = static_cast<int>(screenWidth / divMul_2 - (num250 - num10));
			ONSELEC_Y = static_cast<int>(screenHeigth / divMul_2 + (num100*divMul_2));
			ONSELEC_Y_2 = static_cast<int>(screenHeigth / divMul_1_5);
			//----------------------------------------------------------------------------------------------------	
			ONSELECT_MODE_X = screenWidth / divMul_3 + num50;
			ONSELECT_MODE_Y = screenHeigth / divMul_2;
			//----------------------------------------------------------------------------------------------------	
			PAUSE_X = static_cast<int>(screenWidth / divMul_2 - num100);
			PAUSE_X_2 = static_cast<int>(screenWidth / divMul_2 - num300);
			PAUSE_X_4 = static_cast<int>(screenWidth / divMul_2 - (num300 + (num10*divMul_2)));
			PAUSE_Y = static_cast<int>(num300);
			PAUSE_Y_2 = static_cast<int>(num300 * divMul_2);
			PAUSE_Y_3 = static_cast<int>(num450 + (num100 - num10));
			PAUSE_Y_4 = static_cast<int>((screenHeigth / divMul_1_5 - (num100 + num50)) - (fontSize + num10));
			//----------------------------------------------------------------------------------------------------	
			RESET_X = static_cast<int>((screenWidth / divMul_2) - num250);
			RESET_Y = static_cast<int>(num400 + (num10*divMul_3));
			RESET_Y_2 = static_cast<int>(num450 + (num10*divMul_2));
			//----------------------------------------------------------------------------------------------------	
			WIN_X = static_cast<int>(screenWidth / divMul_2 - num250);
			WIN_Y = static_cast<int>(num100 + (num10*divMul_3));
			WIN_Y_2 = static_cast<int>(num300 + (num10*divMul_3));
			//----------------------------------------------------------------------------------------------------	
			CONTROLS_X = static_cast<int>(screenWidth / divMul_2 - (num300 + num10));
			CONTROLS_Y = static_cast<int>(num300);
			CONTROLS_Y_2 = static_cast<int>(num300 + num50);
			CONTROLS_Y_3 = static_cast<int>((screenHeigth / divMul_2 + num10) - (fontSize + num10));
			CONTROLS_Y_4 = static_cast<int>((screenHeigth / divMul_2 + (num50 + num10)) - (fontSize + num10));
			CONTROLS_Y_5 = static_cast<int>((screenHeigth / divMul_1_5 + (num100 + (num10 * divMul_3))) - (fontSize + num10));
			CONTROLS_Y_6 = static_cast<int>((screenHeigth / divMul_4));
			//----------------------------------------------------------------------------------------------------	
			C_CONTROLS_X = static_cast<int>(screenWidth / divMul_2 - (num400 + (num10*divMul_8)));
			C_CONTROLS_Y1 = static_cast<int>(screenHeigth / divMul_6);
			C_CONTROLS_Y2 = static_cast<int>(C_CONTROLS_Y1 + num50);
			C_CONTROLS_Y3 = static_cast<int>(C_CONTROLS_Y1 + num100);
			C_CONTROLS_Y4 = static_cast<int>(C_CONTROLS_Y1 + num250);
			C_CONTROLS_Y5 = static_cast<int>(C_CONTROLS_Y1 + num300);
			C_CONTROLS_Y6 = static_cast<int>(C_CONTROLS_Y1 + num450);
			//----------------------------------------------------------------------------------------------------	
			OPTIONS_X = static_cast<int>(screenWidth / divMul_2 - (num300 + (num10*divMul_2)));
			OPTIONS_Y = static_cast<int>(screenHeigth / divMul_2);
			OPTIONS_Y_2 = static_cast<int>(screenHeigth - num400);
			OPTIONS_Y_3 = static_cast<int>(screenHeigth - num300);
			OPTIONS_Y_5 = static_cast<int>(screenHeigth - num250);
			//----------------------------------------------------------------------------------------------------	
			CREDITS_X_1 = static_cast<int>(screenWidth / divMul_8);
			CREDITS_X_2 = static_cast<int>(screenWidth / divMul_3);
			CREDITS_Y_1 = static_cast<int>(screenHeigth / divMul_6);
			CREDITS_Y_2 = static_cast<int>(screenHeigth / divMul_4);
			CREDITS_Y_3 = static_cast<int>(screenHeigth / divMul_3);
			CREDITS_Y_4 = static_cast<int>((screenHeigth / divMul_2) - num80);
			CREDITS_Y_5 = static_cast<int>(screenHeigth - num50);
			CREDITS_Y_6 = static_cast<int>(screenHeigth - num250);
			//----------------------------------------------------------------------------------------------------	
			EXIT_X = static_cast<int>(screenWidth / divMul_2 - (num300 + (num10 * divMul_2)));
			EXIT_Y = static_cast<int>(screenHeigth / divMul_2);
			EXIT_Y_2 = static_cast<int>(screenHeigth / divMul_1_5);
			//----------------------------------------------------------------------------------------------------	
			AudioGame::initMusic();
		}
	}
}