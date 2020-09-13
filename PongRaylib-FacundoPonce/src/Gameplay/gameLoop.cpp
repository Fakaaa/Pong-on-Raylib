#include "loop.h"

#include <iostream>

#include "Gameplay/Screen/screen.h"
#include "Sfx/Music.h"
#include "variables.h"
#include "Ball/ball.h"
#include "Player/players.h"
#include "Menu/menu.h"

using namespace Pong;
using namespace Vars;
using namespace Players;
using namespace AudioGame;

namespace Pong{
	namespace Loop{

		GMODE gameMode;
		GMODE result;
		AIMODE difficulty;
		AIMODE difiResult;
		int selecterPos;
		int selecterPosAI;
		int firstMenu;
		float secondsCount;
		int timer[maxTime];
		bool onControlSelect;
		bool defaultStart = false;

		//----------------------------------------------------------------------------------------------------	
		void initializeAll(){
			//MAIN INITS
			if (Menu::actualGameState != Menu::RESTART && Menu::actualGameState != Menu::WIN){
				musicVolume = 0.2f;
				InitAudioDevice();
			}
			Vars::initVariables();
			if (Menu::actualGameState != Menu::RESTART && Menu::actualGameState != Menu::WIN){
				Screen::initializeScreen();
				Screen::loadBackground();
				gameMode = NA;
				difficulty = None;
			}
			SetTargetFPS(maxFrames);
			//TIME
			secondsCount = 0;
			Menu::onPause = false;
			timer[Minutes] = 0;
			timer[Seconds] = 0;
			//GAME MODE
			selecterPos = PJvsPJ;
			selecterPosAI = Easy;
			firstMenu = 1;
			//PJS
			Players::initializePjs();
			//GAME STATE
			if (Menu::actualGameState == Menu::RESTART)
				Menu::actualGameState = Menu::GAMEPLAY;
			else
				Menu::actualGameState = Menu::MENU;
		}
		//----------------------------------------------------------------------------------------------------	
		void drawAll(){
			//-------------------------------
			Screen::drawBackground();
			Screen::drawLine();
			//-------------------------------
			AudioGame::drawMusicOn();
			//-------------------------------
			Players::drawPowerUpIn();
			Players::drawPjs(pj1);
			Players::drawPjs(pj2);
			//-------------------------------
			Ball::drawBall();
			//-------------------------------
			drawTime();
			DrawFPS(0, 0);
		}
		//----------------------------------------------------------------------------------------------------	
		void drawTime(){
			DrawText(FormatText("Min %i", static_cast<int>(timer[Minutes])), D_TIME_X, 0, fontSize, WHITE);
			DrawText(FormatText("seg %i", static_cast<int>(timer[Seconds])), D_TIME_X_2, 0, fontSize, WHITE);
		}
		//----------------------------------------------------------------------------------------------------	
		void physics(){
			switch (gameMode){
			case Loop::PJvsPJ:
				Players::inputs();
				Players::usePowerUpPlayers();
				break;
			case Loop::PJvsIA:
				Players::inputs();
				ai_GameplayP2(pj2);
				Players::usePowerUpPlayers();
				break;
			case Loop::IAvsIA:
				Players::ai_GameplayP1(pj1);
				Players::ai_GameplayP2(pj2);
				Players::makePowerUp_For_IA();
				Players::usePowerUp_For_IA(pj1, pj2);
				break;
			default:
				break;
			}
			Ball::moveBall();
		}
		//----------------------------------------------------------------------------------------------------	
		void update(){
			if (!onControlSelect)
				Menu::inputsMenu();
			switch (Menu::actualGameState){
			case Menu::MENU:			Menu::mainMenu();
				break;
			case Menu::BALL_SELECT:		Menu::actualGameState = Menu::ON_SELECT;
				break;
			case Menu::ON_SELECT:		Menu::ballSelec();
				break;
			case Menu::MODE_SELECT:		Menu::modeSelec();	chooseGMode();
				break;
			case Menu::CONTROL_SELECT:	Menu::controlSelec();
				break;
			case Menu::PAUSE:			Menu::pause();
				break;
			case Menu::OPTIONS:			Menu::options();
				break;
			case Menu::PLAYER_SELECT:	Menu::previusGameState = Menu::PLAYER_SELECT;	Players::choosePaddle();
				break;
			case Menu::VOLUM_SELECT:	optionsMusic(musicVolume);
				break;
			case Menu::GAMEPLAY:		Menu::previusGameState = Menu::GAMEPLAY;	gameplay();
				break;
			case Menu::RESET:			Menu::showScores();
				break;
			case Menu::WIN:				Menu::showWinner();
				break;
			case Menu::RESTART:			initializeAll();
				break;
			case Menu::CONTROLS:		Menu::help();
				break;
			case Menu::EXIT:			Menu::exit();
				break;
			case Menu::CREDITS:			Menu::credits();
				break;
			default:
				Menu::mainMenu();
				break;
			}
		}
		//----------------------------------------------------------------------------------------------------	
		void chooseGMode(){

			if (firstMenu == 1){
				if (IsKeyPressed(KEY_RIGHT)){
					if (selecterPos <= IAvsIA)
						selecterPos++;
				}
				if (IsKeyPressed(KEY_LEFT)){
					if (selecterPos >= PJvsPJ)
						selecterPos--;
				}
				if (selecterPos > IAvsIA)
					selecterPos = PJvsPJ;
				if (selecterPos < PJvsPJ)
					selecterPos = IAvsIA;
			}
			else if (firstMenu == 2){
				if (IsKeyPressed(KEY_RIGHT)){
					if (selecterPosAI <= Impossible)
						selecterPosAI++;
				}
				if (IsKeyPressed(KEY_LEFT)){
					if (selecterPosAI >= Easy)
						selecterPosAI--;
				}
				if (selecterPosAI > Impossible)
					selecterPosAI = Easy;
				if (selecterPosAI < Easy)
					selecterPosAI = Impossible;
			}

			if (firstMenu == 1){
				switch (selecterPos){
				case Loop::PJvsPJ: DrawText("--- PJ vs PJ ---", ONSELECT_MODE_X, ONSELECT_MODE_Y, fontSize, RED);
					result = PJvsPJ;
					break;
				case Loop::PJvsIA: DrawText("--- PJ vs IA ---", ONSELECT_MODE_X, ONSELECT_MODE_Y, fontSize, YELLOW);
					result = PJvsIA;
					break;
				case Loop::IAvsIA: DrawText("--- IA vs IA ---", ONSELECT_MODE_X, ONSELECT_MODE_Y, fontSize, VIOLET);
					result = IAvsIA;
					break;
				default:
					break;
				}
			}
			else if (firstMenu == 2){
				switch (selecterPosAI){
				case Loop::Easy:  DrawText("--- PJ vs IA ---", ONSELECT_MODE_X, ONSELECT_MODE_Y, fontSize, YELLOW);
							DrawText("--- Easy mode ---", ONSELECT_MODE_X, ONSELECT_MODE_Y + num50, fontSize, GREEN);
					difiResult = Easy;
					break;
				case Loop::Hard:	DrawText("--- PJ vs IA ---", ONSELECT_MODE_X, ONSELECT_MODE_Y, fontSize, YELLOW);
							DrawText("--- Hard mode ---", ONSELECT_MODE_X, ONSELECT_MODE_Y + num50, fontSize, YELLOW);
					difiResult = Hard;
					break;
				case Loop::Impossible:  DrawText("--- PJ vs IA ---", ONSELECT_MODE_X, ONSELECT_MODE_Y, fontSize, YELLOW);
								  DrawText("--- Impossible ---", ONSELECT_MODE_X, ONSELECT_MODE_Y + num50, fontSize, VIOLET);
					difiResult = Impossible;
					break;
				}
			}

			if (firstMenu == 1){
				if (IsKeyPressed(KEY_Y)){
					if (selecterPos != 2 && firstMenu != 2)
						Menu::actualGameState = Menu::GAMEPLAY;
					else if (selecterPos == 2){
						firstMenu = 2;
					}
				}
				if (Menu::actualGameState == Menu::GAMEPLAY){
					gameMode = result;
					difficulty = difiResult;
				}
			}
			else if (firstMenu == 2){
				if (IsKeyPressed(KEY_Y)){
					Menu::actualGameState = Menu::GAMEPLAY; 
				}
				if (Menu::actualGameState == Menu::GAMEPLAY){
					gameMode = result; 
					difficulty = difiResult;
				}
			}
		}
		//----------------------------------------------------------------------------------------------------	
		void gameplay(){

			physics();

			AudioGame::playAudioGame();

			Players::setWinnerPj();

			gameTime(timer, secondsCount);
		}
		//----------------------------------------------------------------------------------------------------	
		void mainLoop(){
			initializeAll();
			while (!WindowShouldClose()){
				update();
				ClearBackground(BLANK);
				BeginDrawing();
				if (!Menu::onPause && Menu::actualGameState == Menu::GAMEPLAY) drawAll();
				EndDrawing();
			}
			deInitialize();
		}
		//----------------------------------------------------------------------------------------------------	
		void gameTime(int time[maxTime], float &seconds){
			if (Menu::actualGameState == Menu::GAMEPLAY)
				seconds += GetFrameTime();
			if (seconds >= 1){
				time[Seconds]++;
				if (time[Seconds] >= maxSec){
					time[Seconds] = 0;
					time[Minutes]++;
				}
				seconds = 0;
			}
		}
		//----------------------------------------------------------------------------------------------------	
		void optionsMusic(float &volume){


			if (IsKeyPressed(KEY_RIGHT)){
				if (volume >= 0.0f){
					volume += 0.1f;
				}
			}
			if (IsKeyPressed(KEY_LEFT)){
				if (volume <= 1.0f){
					volume -= 0.1f;
				}
			}
			if (volume > 1.0f)
				volume = 1.0f;
			if (volume < 0.0f)
				volume = 0.0f;

			DrawText(" -----Music Volume----- ", C_CONTROLS_X, C_CONTROLS_Y2 + num100, fontSize, GREEN);

			DrawText(FormatText("%f", volume), POSX_REC_VOLUME, POSY_REC_VOLUME, fontSize, YELLOW);
			SetMusicVolume(audioGame.songGameplay[audioGame.chooseGameplayMusic], volume);

			if (IsKeyPressed(KEY_Y)){
				Menu::actualGameState = Menu::OPTIONS;
			}

			DrawText("[LEFT] & [RIGTH]: Change value", C_CONTROLS_X, C_CONTROLS_Y4 + num250, fontSize, WHITE);
			DrawText("press [Y] to finish", C_CONTROLS_X, C_CONTROLS_Y6 + num100, fontSize, WHITE);
		}
		//----------------------------------------------------------------------------------------------------	
		void deInitialize(){
			Screen::unloadBackground();
			AudioGame::unloadAudioGame();
			CloseWindow();
		}
		//----------------------------------------------------------------------------------------------------	
	}
}