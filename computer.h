#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
using namespace std;

class Computer : public Player{
public:
	Computer();
	~Computer();

	char Alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char *randomPtr = Alphabet;

	char generateRandomGuess();
};

#endif