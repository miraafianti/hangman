#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "file.h"
#include "termcolor.h"

using namespace std;

File::File(){
	generateRandomIdx();
}

File::~File(){}

void File::writeToFile(string w){
	ofstream writer("dictionary.txt", ios::app);
	if (!writer){
		cout << "error opening file" << endl;
	}
	writer << w << endl;
	if(writer.good()){
		cout << termcolor::green <<  "text successfully added" << termcolor::reset << endl;
	}
	writer.close();
}

string File::getWord(){
	ifstream reader("dictionary.txt");
	string line;
	string choosenWord;

	int ptFile = 1;

	while(getline(reader, line)){
		if(ptFile == randomIdx){
			choosenWord = line;
			break;
		}
		ptFile++;
	}

	reader.close();

	return choosenWord;
}

void File::generateRandomIdx(){
	srand (time(NULL));

	int max = getNumberOfLines();
	int min = 1;
	randomIdx = rand()%(max-min + 1) + min;
}

int File::getNumberOfLines(){
	ifstream reader("dictionary.txt");
	string line;
	int numberOfLines = 0;

	while(getline(reader, line)){
		numberOfLines++;
	}

	reader.close();
	return numberOfLines;
}
