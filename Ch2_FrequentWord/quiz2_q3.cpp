#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

void readFile(string fileName, string* text) {
	ifstream inputFile;
	inputFile.open(fileName);

	getline(inputFile, *text);

	inputFile.close();

}
void countSkew(string* text, vector<int>& skew) {

	int lastSkew = 0;
	skew.emplace_back(lastSkew); // 1st element always 0


	for (int i = 0; i < text->length(); i++) {
		string nucleo = text->substr(i, 1);

		if (nucleo.compare("C") == 0) {
			lastSkew = lastSkew - 1;
			skew.emplace_back(lastSkew);
		}
		else if (nucleo.compare("G") == 0) {
			lastSkew = lastSkew + 1;
			skew.emplace_back(lastSkew);
		}
		else {
			skew.emplace_back(lastSkew);
		}
	}

	// print
	//ofstream myfile;
	//myfile.open ("output.txt");

	//for (list<int>::iterator it  = skew.begin(); it!= skew.end(); it++) {
	//	cout << *it << " ";
	//	myfile<< *it << " ";
	//}
	//myfile.close();
}


void listMaxSkew(vector<int>& skew, vector<int>& maxSkew, int* maxValue) {


	for (int i = 0; i < skew.size(); i++) {
		if (skew.at(i) > *maxValue) {
			maxSkew.clear();
			maxSkew.emplace_back(i);

			*maxValue = skew.at(i);

		}
		else if (skew.at(i) == *maxValue) {
			maxSkew.emplace_back(i);
		}
	}


	// print
	//ofstream myfile;
	//myfile.open("output.txt");

	//for (vector<int>::iterator it = skew.begin(); it != skew.end(); it++) {
	//	//cout << *it << " ";
	//	myfile << *it << " ";
	//}
	//myfile << endl;

	//for (vector<int>::iterator it = minSkew.begin(); it != minSkew.end(); it++) {
	//	//cout << *it << " ";
	//	myfile << *it << " ";
	//}
	//myfile << endl;

	//myfile.close();

}



//void main() {
//	//string text = "CATGGGCATCGGCCATACGCC";
//	//string text = "GAGCCACCGCGATA";
//	//string text = "TAAAGACTGCCGAGAGGCCAACACGAGTGCTAGAACGAGGGGCGTAAACGCGGGTCCGAT";
//	//string text = "ACCG";
//	//string text = "ACCC";
//	//string text = "CCGGGT";
//	//string text = "CCGGCCGG";
//
//	string text = "GCATACACTTCCCAGTAGGTACTG";
//
//	vector<int> skew;
//	vector<int> maxSkew;
//
//	int maxValue = INT_MIN;
//
//	//readFile("minimum_skew_data.txt",&text);
//	//readFile("dataset_7_6.txt",&text);
//	
//	countSkew(&text,skew);
//	listMaxSkew(skew, maxSkew, &maxValue);
//	for (int i : maxSkew) {
//		cout << i << " ";
//	}
//	cout << endl;
//	//cout << endl;
//}