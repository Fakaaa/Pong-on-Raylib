#ifndef LOOP_H
#define LOOP_H

namespace Pong{
	namespace Loop{

		enum TIMER{
			Minutes,
			Seconds
		};

		enum GMODE{
			PJvsPJ = 1,
			PJvsIA,
			IAvsIA,
			NA
		};
		enum AIMODE{
			None,
			Easy,
			Hard,
			Impossible
		};

		const int GmodesAmount = 3;
		const int maxTime = 2;
		extern GMODE gameMode;
		extern AIMODE difficulty;
		extern float secondsCount;
		extern int timer[maxTime];

		extern bool defaultStart;

		void initializeAll();
		void drawAll();
		void drawTime();
		void physics();
		void update();
		void chooseGMode();
		void gameplay();
		void mainLoop();
		void gameTime(int time[maxTime], float &frames);
		void optionsMusic(float &volume);
		void deInitialize();
	}
}
#endif // !LOOP_H