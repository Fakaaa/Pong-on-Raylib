#include "Music.h"

#include "Gameplay/variables.h"
#include "Gameplay/loop.h"

using namespace Pong;
using namespace Loop;
using namespace Vars;

namespace Pong{
	namespace AudioGame{

		//CONST
		const char* Song1 = "Doom Eternal OST - The Only Thing They Fear is You";
		const char* Song2 = "KROWW - HYSTERIA";
		const char* Song3 = "SYN - Steel";
		const char* Song4 = "Evilwave & Antima - Tinnitus";

		MUSIC audioGame;
		float musicVolume;
		int MUSIC_X_GAMEPLAY;
		int MUSIC_Y_GAMEPLAY;

		int POSX_REC_VOLUME;
		int POSY_REC_VOLUME;

		void initMusic(){
			MUSIC_X_GAMEPLAY = static_cast<int>(num50);
			MUSIC_Y_GAMEPLAY = static_cast<int>(screenHeigth - num50);
			POSX_REC_VOLUME = static_cast<int>(screenWidth / divMul_3);
			POSY_REC_VOLUME = static_cast<int>(screenHeigth / divMul_2);

			audioGame.chooseGameplayMusic = GetRandomValue(0, 3);
			UnloadMusicStream(audioGame.songGameplay[audioGame.chooseGameplayMusic]);
			loadAudioGame();
		}
		//----------------------------------------------------------------------------------------------------	
		void loadAudioGame(){
			audioGame.songGameplay[audioGame.chooseGameplayMusic].loopCount = 1;
			audioGame.timePlayed = 0;
			switch (audioGame.chooseGameplayMusic){
			case 0: audioGame.songGameplay[audioGame.chooseGameplayMusic] = LoadMusicStream("res/audio/EPICSONG.mp3");
				break;
			case 1: audioGame.songGameplay[audioGame.chooseGameplayMusic] = LoadMusicStream("res/audio/EPICSONG2.mp3");
				break;
			case 2: audioGame.songGameplay[audioGame.chooseGameplayMusic] = LoadMusicStream("res/audio/EPICSONG3.mp3");
				break;
			case 3: audioGame.songGameplay[audioGame.chooseGameplayMusic] = LoadMusicStream("res/audio/EPICSONG4.mp3");
				break;
			default:
				break;
			}
			audioGame.musicLong = GetMusicTimeLength(audioGame.songGameplay[audioGame.chooseGameplayMusic]);
			PlayMusicStream(audioGame.songGameplay[audioGame.chooseGameplayMusic]);
			SetMusicVolume(audioGame.songGameplay[audioGame.chooseGameplayMusic], musicVolume);
		}
		//----------------------------------------------------------------------------------------------------	
		void unloadAudioGame(){
			UnloadMusicStream(audioGame.songGameplay[0]);
			UnloadMusicStream(audioGame.songGameplay[1]);
			UnloadMusicStream(audioGame.songGameplay[2]);
			UnloadMusicStream(audioGame.songGameplay[3]);
			CloseAudioDevice();
		}
		//----------------------------------------------------------------------------------------------------	
		void drawMusicOn(){
			if (MUSIC_X_GAMEPLAY >= screenWidth){
				switch (audioGame.chooseGameplayMusic){
				case 0: MUSIC_X_GAMEPLAY = -static_cast<int>(num450*divMul_2);
					break;
				case 1: MUSIC_X_GAMEPLAY = -num250;
					break;
				case 2: MUSIC_X_GAMEPLAY = -num300;
					break;
				case 3: MUSIC_X_GAMEPLAY = -num450;
					break;
				default:
					break;
				}
			}
			else
				MUSIC_X_GAMEPLAY++;
			switch (audioGame.chooseGameplayMusic){
			case 0: DrawText(Song1, MUSIC_X_GAMEPLAY, MUSIC_Y_GAMEPLAY, fontSize2, MUSIC_GAMEPLAY);
				break;
			case 1: DrawText(Song2, MUSIC_X_GAMEPLAY, MUSIC_Y_GAMEPLAY, fontSize2, MUSIC_GAMEPLAY);
				break;
			case 2: DrawText(Song3, MUSIC_X_GAMEPLAY, MUSIC_Y_GAMEPLAY, fontSize2, MUSIC_GAMEPLAY);
				break;
			case 3: DrawText(Song4, MUSIC_X_GAMEPLAY, MUSIC_Y_GAMEPLAY, fontSize2, MUSIC_GAMEPLAY);
				break;
			default:
				break;
			}
		}
		//----------------------------------------------------------------------------------------------------	
		void playAudioGame(){
			audioGame.timePlayed = GetMusicTimePlayed(audioGame.songGameplay[audioGame.chooseGameplayMusic]);
			if (audioGame.timePlayed >= audioGame.musicLong - num10){
				UnloadMusicStream(audioGame.songGameplay[audioGame.chooseGameplayMusic]);
				audioGame.chooseGameplayMusic = GetRandomValue(0, 3);
				loadAudioGame();
			}
			UpdateMusicStream(audioGame.songGameplay[audioGame.chooseGameplayMusic]);
		}
	}
}