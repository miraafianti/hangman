#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "file.h"
using namespace std;

class Player{
	public:
		Player();
		~Player();
		string word;

		char *progress = new char[20];
		char *history = new char[20];

		char guessLetter;

		int lengthOfWord;
		int idxHistory;
		int chance;
		int score;

		bool correct;
		bool win;

		void generateRandomWord();
		void startSingleGame();
		void startDoubleGame();

	private:
		//void resetPlayer();
		void displayProgress();
		void setProgress();	
		void addToHistory(char letter);

		void drawHangman(int stat, int player);
		void drawSeparator(int type);
		void getValidInput();

		bool isCorrect();
		bool isGuessed();
		bool isExist(char letter);
};

#endif