#ifndef MUSIC_H
#define MUSIC_H
#define MAXSONGS 4

#include "Gameplay/Screen/screen.h"

namespace Pong{
	namespace AudioGame{

		struct MUSIC{
			Music songMenu;
			Music songGameplay[MAXSONGS];
			int chooseGameplayMusic;
			float timePlayed;
			float musicLong;
		};

		extern float musicVolume;
		extern MUSIC audioGame;

		extern int POSX_REC_VOLUME;
		extern int POSY_REC_VOLUME;

		void initMusic();
		void drawMusicOn();
		void playAudioGame();
		void unloadAudioGame();
		void loadAudioGame();
	}
}
#endif // !MUSIC_H