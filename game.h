#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game{
	public:
		Game();
		~Game();	
		char mode;
		Player *p = new Player;

		void greeting();

	private:
		void generateSinglePlayer();
		void generateDoublePlayer();
		void chooseMode(char m);
		void showMenu();
		void addNewWord();
};

#endif