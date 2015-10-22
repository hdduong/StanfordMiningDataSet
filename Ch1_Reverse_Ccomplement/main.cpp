#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

void readFile2(string fileName, string* text) {
	string stringRead;
	ifstream infile;

	infile.open(fileName);
	//while(!infile.eof()) // To get you all the lines.
	//{
	// Saves the line in STRING.
	//cout<<stringRead << endl; // Prints our STRING.
	//getline(infile,stringRead);
	// 1st line is text
	getline(infile, *text);

	// 2nd line is paterrn

	// }

	infile.close();
}

void reverseComplement(string *src, string *des) {
	for (string::iterator it = src->begin(); it != src->end(); it++) {
		if (*it == 'A') {
			des->append("T");
		}
		else if (*it == 'C') {
			des->append("G");
		}
		else if (*it == 'G') {
			des->append("C");
		}
		else if (*it == 'T') {
			des->append("A");
		}
	}
	std::reverse(des->begin(), des->end());
}

void main() {
	//string src = "AAAACCCGGT";
	//string src = "ACACAC";
	//string des = "";

	// quiz 1 - 4
	string src = "GCTAGCT";
	string des = "";

	//readFile2("dataset_3_2.txt", &src);
	reverseComplement(&src, &des);

	ofstream myfile;

	myfile.open("output.txt");
	myfile << des << endl;
	myfile.close();
}