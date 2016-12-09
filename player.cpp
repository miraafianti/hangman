#include <iostream>
#include "player.h"
#include "computer.h"
#include "termcolor.h"
//#include "ctype.h"
using namespace std;

Player::Player(){
	char *progress = new char[20];
	char *history = new char[20];

	chance = 6;
	win = false;
	correct = true;
	score = 0;
	idxHistory = 0;
}

Player::~Player(){
	delete[] progress;
	delete[] history;
}

void Player::generateRandomWord(){
	File f;
	word = f.getWord();
}

void Player::setProgress(){
	lengthOfWord = word.length();

	for(int i=0; i<lengthOfWord; i++){
		progress[i] = '_';
	}
}

void Player::displayProgress(){
	for(int i=0; i<lengthOfWord; i++){
		cout << progress[i] << " ";
	}
}

void Player::addToHistory(char letter){
	history[idxHistory] = letter;
	idxHistory++;
}

void Player::drawSeparator(int type){
	cout << endl;
	switch(type){
		case 1:
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; 
			break;
		case 2:
			cout << termcolor::yellow << "====================================================================================" << termcolor::reset << endl;
			break;
	}	
}

void Player::getValidInput(){
	bool validInput = false;
	while(!validInput){
		cout << endl << endl << "Input your guess : ";
		cin >> guessLetter;
		guessLetter = tolower(guessLetter);

		if(isGuessed()){
			cout << termcolor::red <<  "You've already guessed that, choose other letter!" << termcolor::reset << endl;
		}
		else if((int(guessLetter < 97)) || (int(guessLetter > 122))){
			cout << termcolor::red <<  "Input is not valid. Please enter a letter!" << termcolor::reset << endl;
		}
		else{
			validInput = true;
			break;
		}
	}
}

void Player::startDoubleGame(){

	Computer *c = new Computer();

	cout << endl << termcolor::green << "In this game, the computer will guess the word from you." << termcolor::reset << endl;
	cout << "Now, input the word : " ;
	cin >> c->word;
	transform(c->word.begin(), c->word.end(), c->word.begin(), ::tolower);

	cout << endl << termcolor::yellow << "-----------------------------------> GAME BEGIN <---------------------------------" << termcolor::reset << endl;
	cout << endl;

	setProgress();
	c->setProgress();

	idxHistory = 0;
	c->idxHistory = 0;
	
	//game begin
	while((chance != 0) && (c->chance != 0) && (!win) && (!c->win)){
		
		cout << termcolor::cyan << "COMPUTER" << termcolor::reset << endl;
		cout << endl;
		c->displayProgress();

		//validity of computer's guess
		bool validInput = false;
		while(!validInput){
			c->guessLetter = c->generateRandomGuess();

			if(c->isGuessed()){
				c->guessLetter = c->generateRandomGuess();
			}
			else if((int(c->guessLetter < 97)) || (int(c->guessLetter > 122))){
				c->guessLetter = c->generateRandomGuess();
			}
			else{
				validInput = true;
				break;
			}
		}

		cout << endl << endl << "Computer guess : " << termcolor::cyan << c->guessLetter << termcolor::reset << endl;

		drawSeparator(1);		

		cout << termcolor::magenta << "YOU" << termcolor::reset << endl;
		cout << endl;
		displayProgress();
		getValidInput();

		drawSeparator(2);

		cout << endl;
		cout << termcolor::magenta << "YOU" << termcolor::reset << endl;

		if(!isExist(guessLetter)){
			cout << termcolor::red << "### Ouch! Bad Guess! ###" << termcolor::reset << endl;
			chance--;
		}
		else{
			if(isCorrect()){
				cout << termcolor::green << "~~~ Congratulation, You Guessed the Word Correctly! ~~~" << termcolor::reset << endl;					
				cout << "The correct word is : " << termcolor::yellow << progress << termcolor::reset << endl;
				win = true;
				break;
			}
			else{
				cout << termcolor::green << "*** Good job! Continue your guess! ***"<< termcolor::reset << endl;
			}
		}

		addToHistory(guessLetter);			
		cout << "--> you have " << termcolor::on_magenta << chance << " chance" << termcolor::reset << " left <--" << endl  << endl;
		drawHangman(chance, 2);
		cout << "Your progress :  " << endl;
		displayProgress();
		cout << endl;

		drawSeparator(1);

		//----------------computer part
		cout << termcolor::cyan << endl << "COMPUTER" << termcolor::reset << endl;

		if(!c->isExist(c->guessLetter)){
			cout << termcolor::red << "### Sorry, Computer! Wrong Guess! ###" << termcolor::reset << endl;
			c->chance--;
		}
		else{
			if(c->isCorrect()){
				cout << termcolor::yellow << "~~~ Computer Guessed the Word Correctly! ~~~" << termcolor::reset << endl;					
				cout << "The correct word is : " << termcolor::green << c->progress << termcolor::reset << endl;
				c->win = true;
				break;
			}
			else{
				cout << termcolor::green << "*** Well done, Computer! Continue your guess! ***" << termcolor::reset << endl;
			}
		}

		c->addToHistory(c->guessLetter);			
		cout << "--> Computer has " << termcolor::on_cyan << c->chance << " chance" << termcolor::reset << " left <--" << endl << endl;
		c->drawHangman(c->chance, 1);
		cout << "Computer's progress :  " << endl;
		c->displayProgress();

		cout << endl;

		drawSeparator(2);
	}

	if(chance == 0){
		cout << termcolor::red << "Oops, looks like you run out of chance to guess....." << termcolor::reset << endl;
		cout << "COMPUTER wins the game!" <<endl;
		cout << endl;
		cout << "The correct word for you is : " << termcolor::cyan << word << termcolor::reset <<endl;
	}
	else if(c->chance == 0){
		cout << termcolor::red << "Computer runs out of chance ....." << termcolor::reset << endl;
		cout << "YOU win the game!" <<endl;
		cout << endl;
		cout << "The correct word for you is : " << termcolor::cyan << word << termcolor::reset <<endl;
	}
	else if(c->win){
		cout << termcolor::cyan << "COMPUTER wins the game!" << termcolor::reset << endl;
		cout << endl;
		cout << "The correct word for you is : " << termcolor::cyan << word << termcolor::reset <<endl;
	}
	else if(win){
		cout << termcolor::magenta << "YOU win the game!" << termcolor::reset <<endl;
		cout << endl;
		cout << "The correct word for you is : " << termcolor::cyan << word << termcolor::reset <<endl;
	}
}

void Player::startSingleGame(){

	cout << endl << termcolor::green << "In this game, you have to guess random word related to Harry Potter" << termcolor::reset << endl;
	cout << endl << termcolor::on_red << "Guess the word! " << termcolor::reset << endl << endl;

	setProgress();		
	idxHistory = 0;

	//game begin
	while(chance != 0){

		cout << endl;
		displayProgress();	
		cout << endl;

		getValidInput();
			
		if(!isExist(guessLetter)){
			cout << termcolor::red << "### Ouch! Bad Guess! ###" << termcolor::reset << endl;
			chance--;
		}
		else{
			if(isCorrect()){
				cout << termcolor::green << "Congratulation, You Guessed the Word Correctly!" << termcolor::reset << endl;					
				cout << "The correct word is : " << termcolor::cyan << word << termcolor::reset <<endl;
				break;
			}
			else{
				cout << termcolor::green << "*** Good job! Continue your guess! ***"<< termcolor::reset << endl;
			}
		}

		addToHistory(guessLetter);			
		cout << "--> you have " << termcolor::on_magenta << chance << " chance" << termcolor::reset << " left <--" << endl  << endl;
		drawHangman(chance, 2);

		cout << termcolor::reset << "====================================================================================" << endl;

	}
	if(!correct){
		cout << termcolor::on_red << "Sorry, You LOSE!" << termcolor::reset << endl;
		cout << "The correct word is : " << termcolor::cyan << word << termcolor::reset <<endl;
	}
}

bool Player::isCorrect(){
	correct = true;
	for(int i=0; i<lengthOfWord; i++){
		if(progress[i] == '_'){
			correct = false;
			break;
		}
	}
	return correct;
}

bool Player::isGuessed(){
	//cout << history << endl;
	bool sameWord = false;
	for(int i=0; i<idxHistory; i++){
		//check if the word has been guessed before
		if(history[i] == guessLetter){
			sameWord = true;
			break;
		}
	}
	return sameWord;
}

bool Player::isExist(char letter){
	bool found = false;
	//check if the letter that user input is exist
	for(int i=0; i<lengthOfWord ; i++){
		if(word[i] == letter){
			progress[i] = letter;
			found = true;
		}
	}
	return found;
}

void Player::drawHangman(int stat, int player){
	switch (player){
		case 1:
			switch(stat){
				case 6:
					cout << termcolor::cyan << "   ++-----------+" << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ==============" << termcolor::reset << endl; 
					cout << endl;
					break;
				case 5:
					cout << termcolor::cyan << "   ++-----------+" << endl;
					cout << "   ||           |" << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ||            " << endl;
					cout << "   ==============" << termcolor::reset << endl; 
					cout << endl;
					break;
				case 4:
					cout << termcolor::cyan << "   ++-----------+" << endl;
					cout << "   ||           | " << endl;
					cout << "   ||           o " << endl;
					cout << "   ||           | " << endl;
					cout << "   ||             " << endl;
					cout << "   ||             " << endl;
					cout << "   ||             " << endl;
					cout << "   ============== " << termcolor::reset << endl; 
					cout << endl;
					break;
				case 3:
					cout << termcolor::cyan << "   ++-----------+" << endl;
					cout << "   ||           | " << endl;
					cout << "   ||           o " << endl;
					cout << "   ||          /| " << endl;
					cout << "   ||             " << endl;
					cout << "   ||             " << endl;
					cout << "   ||             " << endl;
					cout << "   ============== " << termcolor::reset << endl; 
					cout << endl;
					break;
				case 2:
					cout << termcolor::cyan << "   ++-----------+" << endl;
					cout << "   ||           | " << endl;
					cout << "   ||           o " << endl;
					cout << "   ||          /|\\" <<endl;
					cout << "   ||             " << endl;
					cout << "   ||             " << endl;
					cout << "   ||             " << endl;
					cout << "   ============== " << termcolor::reset << endl; 
					cout << endl;
					break;
				case 1:
					cout << termcolor::cyan << "   ++-----------+" << endl;
					cout << "   ||           | " << endl;
					cout << "   ||           o " << endl;
					cout << "   ||          /|\\" <<endl;
					cout << "   ||            \\ " << endl;
					cout << "   ||             " << endl;
					cout << "   ||             " << endl;
					cout << "   ============== " << termcolor::reset << endl; 
					cout << endl;
					break;
				case 0:
					cout << termcolor::cyan << "   ++-----------+" << endl;
					cout << "   ||           | " << endl;
					cout << "   ||           o " << endl;
					cout << "   ||          /|\\" <<endl;
					cout << "   ||          / \\ " << endl;
					cout << "   ||             " << endl;
					cout << "   ||             " << endl;
					cout << "   ============== " << termcolor::reset << endl; 
					cout << endl;
					break;
			}
			break;
		//--------------------------------------------------------	
		case 2:
			switch(stat){
				case 6:
					cout << "   +-----------++" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "   ==============" << endl; 
					cout << endl;
					break;
				case 5:
					cout << "   +-----------++" << endl;
					cout << "   |           ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "   ==============" << endl; 
					cout << endl;
					break;
				case 4:
					cout << "   +-----------++" << endl;
					cout << "   |           ||" << endl;
					cout << "   o           ||" << endl;
					cout << "   |           ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "   ==============" << endl; 
					cout << endl;
					break;
				case 3:
					cout << "   +-----------++" << endl;
					cout << "   |           ||" << endl;
					cout << "   o           ||" << endl;
					cout << "  /|           ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "   ==============" << endl; 
					cout << endl;
					break;
				case 2:
					cout << "   +-----------++" << endl;
					cout << "   |           ||" << endl;
					cout << "   o           ||" << endl;
					cout << "  /|\\          ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "   ==============" << endl; 
					cout << endl;
					break;
				case 1:
					cout << "   +-----------++" << endl;
					cout << "   |           ||" << endl;
					cout << "   o           ||" << endl;
					cout << "  /|\\          ||" << endl;
					cout << "    \\          ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "   ==============" << endl; 
					cout << endl;
					break;
				case 0:
					cout << "   +-----------++" << endl;
					cout << "   |           ||" << endl;
					cout << "   o           ||" << endl;
					cout << "  /|\\          ||" << endl;
					cout << "  / \\          ||" << endl;
					cout << "               ||" << endl;
					cout << "               ||" << endl;
					cout << "   ==============" << endl; 
					cout << endl;
					break;
			}
		break;
	}
}
