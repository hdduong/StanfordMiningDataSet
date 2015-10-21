#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <list>

using namespace std;


void readFile(string fileName, string* text, string* pattern) {
	string stringRead;
	ifstream infile;

	infile.open(fileName);

	//getline(infile, *pattern);

	// 2nd line is paterrn
	getline(infile, *text);

	infile.close();
}

list<int> matchPattern(string* text, string* pattern) {
	list<int> pos;

	int patternLength = pattern->length();

	for (int i = 0; i < text->length(); i++) {
		string subText = text->substr(i, patternLength);
		if (subText.compare(*pattern) == 0)
			pos.emplace_back(i);
	}

	return pos;
}


void main() {
	//string src = "AAAACCCGGT";
	string text = "GATATATGCATATACTT";
	string pattern = "ATAT";

	readFile("Vibrio_cholerae.txt",&text,&pattern);
	pattern = "CTTGATCAT";

	ofstream myfile;

	myfile.open("output.txt");
	
	list<int> pos = matchPattern(&text, &pattern);
	for (list<int>::iterator it = pos.begin(); it != pos.end(); it++) {
		myfile << *it << " ";
	}
	
	myfile.close();
}


