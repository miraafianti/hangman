#include <iostream>
#include <string>
#include <time.h>
#include "game.h"
#include "player.h"
#include "file.h"
#include "computer.h"
using namespace std;

Computer::Computer():Player(){
	//cout << "child constructor called" <<endl;
}

Computer::~Computer(){
	delete randomPtr;
	//cout << "child destructor called" <<endl;
}

char Computer::generateRandomGuess(){
	srand (time(NULL));

	int max = 26;
	int min = 0;
	int idx = rand()%(max-min + 1) + min;

	return *(randomPtr + idx);
}
