#include <iostream>
#include <string>
#include <utility>
#include "game.h"
#include "player.h"
#include "file.h"
#include "computer.h"
#include "termcolor.h"
using namespace std;

Game::Game(){
	//Player p;
}

Game::~Game(){}

void Game::greeting(){
	cout << endl;
	cout << endl;
	cout << "====================================================================================" << endl << endl;
	cout << termcolor::cyan << "      ___         ___         ___         ___         ___         ___         ___     "<<endl;
	cout << "     /\\__\\       /\\  \\       /\\__\\       /\\  \\       /\\__\\       /\\  \\       /\\__\\    "<<endl;
	cout << "    /:/  /      /::\\  \\     /::|  |     /::\\  \\     /::|  |     /::\\  \\     /::|  |   "<<endl;
	cout << "   /:/__/      /:/\\:\\  \\   /:|:|  |    /:/\\:\\  \\   /:|:|  |    /:/\\:\\  \\   /:|:|  |   "<<endl;
	cout << "  /::\\  \\ ___ /::\\~\\:\\  \\ /:/|:|  |__ /:/  \\:\\  \\ /:/|:|__|__ /::\\~\\:\\  \\ /:/|:|  |__ "<<endl;
	cout << " /:/\\:\\  /\\__/:/\\:\\ \\:\\__/:/ |:| /\\__/:/__/_\\:\\__/:/ |::::\\__/:/\\:\\ \\:\\__/:/ |:| /\\__\\ "<<endl;
	cout << " \\/__\\:\\/:/  \\/__\\:\\/:/  \\/__|:|/:/  \\:\\  /\\ \\/__\\/__/~~/:/  \\/__\\:\\/:/  \\/__|:|/:/  / "<<endl;
	cout << "      \\::/  /     \\::/  /    |:/:/  / \\:\\ \\:\\__\\       /:/  /     \\::/  /    |:/:/  /  "<<endl;
	cout << "      /:/  /      /:/  /     |::/  /   \\:\\/:/  /      /:/  /      /:/  /     |::/  /  "<<endl;
	cout << "     /:/  /      /:/  /      /:/  /     \\::/  /      /:/  /      /:/  /      /:/  /   "<<endl;
	cout << "     \\/__/       \\/__/       \\/__/       \\/__/       \\/__/       \\/__/       \\/__/  "<<endl;
	cout << endl;
	cout << endl;
	cout << termcolor::reset << "----------------------------------" << termcolor::on_cyan <<" Mira Afianti "<< termcolor::reset <<" ------------------------------------" << endl << endl;	
	showMenu();
}

void Game::showMenu(){
	cout << "Choose the menu : " << endl;
	cout << "1. Single Game" << endl;
	cout << "2. You vs Computer" << endl;
	cout << "3. Add More Word to Dictionary" << endl;

	bool valid = false;
	while(!valid){
		cout << endl;
		cout << "Your choice : " ;
		cin >> mode;

		if((mode == '1') || (mode == '2') || (mode == '3')){
			valid = true;
			break;
		}
		else{
			cout << termcolor::red << "not a valid input." << termcolor::reset << endl;	
		}
	}
	
	cout << endl;
	cout << "====================================================================================" << endl;


	this->chooseMode(mode);
}

void Game::chooseMode(char m){
	switch(m){
		case '1':			
			this->generateSinglePlayer();
			break;
		case '2':
			this->generateDoublePlayer();
			break;
		case '3':
			this->addNewWord();
			break;
	}
}

void Game::addNewWord(){
	char cont = 'y';

	while(cont == 'y'){
		string newWord;
		cout << endl;
		cout << termcolor::on_red<< "Add a word related to Harry Potter: " << termcolor::reset << endl;
		cin >> newWord;

		transform(newWord.begin(), newWord.end(), newWord.begin(), ::tolower);

		File f;
		f.writeToFile(newWord);

		cout << endl << "Want to add more word (y/n)? ";
		cout << endl << "To back to the main menu, press (b) ";
		cin >> cont;

		if((cont == 'b') || (cont == 'n')){
			break;
		}
	}

	if (cont == 'b'){
		cout << endl;
		this->showMenu();
	}
}

void Game::generateSinglePlayer(){	
	char cont = 'y';

	while(cont == 'y'){
		Player *p = new Player();

		p->generateRandomWord();
		p->startSingleGame();

		bool valid = false;

		while (!valid){
			cout << endl << "Want to play again (y/n)? " ;
			cout << endl << "To back to the main menu, press (b) ";

			cin >> cont;

			if((cont == 'y') || (cont == 'n') || (cont == 'b')){
				valid = true;
				break;
			}
			else{
				cout << termcolor::red << "not a valid input." << termcolor::reset << endl;
			}
		}

		if((cont == 'b') || (cont == 'n')){
			break;
		}

		delete p;
	}

	if (cont == 'b'){
		cout << endl;
		this->showMenu();
	}
}
void Game::generateDoublePlayer(){
	
	char cont = 'y';

	while(cont == 'y'){
		Player *p = new Player();

		p->generateRandomWord();
		p->startDoubleGame();

		bool valid = false;

		while (!valid){
			cout << endl << "Want to play again (y/n)? " ;
			cout << endl << "To back to the main menu, press (b) ";

			cin >> cont;

			if((cont == 'y') || (cont == 'n') || (cont == 'b')){
				valid = true;
				break;
			}
			else{
				cout << termcolor::red << "not a valid input." << termcolor::reset << endl;
			}
		}

		if((cont == 'b') || (cont == 'n')){
			break;
		}

		delete p;
	}

	if (cont == 'b'){
		cout << endl;
		this->showMenu();
	}
}
