#ifndef FILE_H
#define FILE_H

#include <string>

using namespace std;

class File{
	public:
		File();
		~File();

		int randomIdx;

		string getWord();
		void generateRandomIdx();
		int getNumberOfLines();
		void writeToFile(string w);
};

#endif