#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;


void readSalmonella_enterica(string filename, string* text) {
	ifstream inputFile;
	inputFile.open(filename);

	string line;
	while (!inputFile.eof()) {
		getline(inputFile, line);
		text->append(line);
	}
}

void readFrequentWordMisMatch(string filename, string* text, int* k, int* d) {
	ifstream inputFile;
	inputFile.open(filename);

	getline(inputFile, *text);

	string strd, strk;

	inputFile >> strk >> strd;
	*k = stoi(strk);
	*d = stoi(strd);

	inputFile.close();

}


string numberToSymbol(int number) {
	string symbol = "";

	if (number == 0) {
		symbol = "A";
	}
	else if (number == 1) {
		symbol = "C";
	}
	else if (number == 2) {
		symbol = "G";
	}
	else if (number == 3) {
		symbol = "T";
	}

	return symbol;
}

string numberToPattern(long long int number, int k) {
	long long int quotient;
	int reminder;

	string pattern = "";
	if (number == 0) {
		while (k--) {
			pattern.append("A");
		}
	}

	while (number != 0) {
		quotient = number / 4;
		reminder = number - quotient * 4;

		pattern.append(numberToSymbol(reminder));

		number = quotient;
	}

	int currPatternLength = pattern.length();
	for (int i = 0; i < (k - currPatternLength); i++) {
		pattern.append("A");
	}

	std::reverse(pattern.begin(), pattern.end());

	return pattern;
}

int symbolToNumber(string* symbol) {
	int symbolValue = 0;

	if (symbol->compare("A") == 0) {
		symbolValue = 0;
	}
	else if (symbol->compare("C") == 0) {
		symbolValue = 1;
	}
	else if (symbol->compare("G") == 0) {
		symbolValue = 2;
	}
	else if (symbol->compare("T") == 0) {
		symbolValue = 3;
	}

	return symbolValue;
}

long long int patternToNumber(string * pattern) {
	if (pattern->length() == 0)
		return 0;

	if (pattern->length() == 1)
		return symbolToNumber(pattern);

	string lastSymbol = pattern->substr(pattern->length() - 1, 1);

	long long int patternValue = 0;
	patternValue = symbolToNumber(&lastSymbol);

	string prefix = pattern->substr(0, pattern->length() - 1);

	return (4 * patternToNumber(&prefix) + patternValue);

}


int getHammingDistance(string* text1, string* text2) {
	int count = 0;
	for (int i = 0; i < text1->length(); i++) {
		if (text1->at(i) != text2->at(i)) {
			count++;
		}
	}
	//cout << count << endl;
	return count;
}

string getSuffix(string *pattern) {
	return (pattern->substr(1, pattern->length() - 1));
}


long int getApproximatePatternCount(string* text, string* pattern, int d) {

	vector<long int> pos;

	for (int i = 0; i < (text->length() - pattern->length() + 1); i++) {
		string curPattern = text->substr(i, pattern->length());

		int hamDis = getHammingDistance(pattern, &curPattern);
		if (hamDis <= d)
			pos.emplace_back(i);
	}

	return pos.size();
}


vector<string> getNeighbor(string* pattern, int d) {
	vector<string> neighborHood;

	if (d == 0)
	{
		neighborHood.emplace_back(*pattern);
		return neighborHood;
	}

	if (pattern->length() == 1) {
		neighborHood.emplace_back("A");
		neighborHood.emplace_back("C");
		neighborHood.emplace_back("G");
		neighborHood.emplace_back("T");
		return neighborHood;
	}

	vector<string> suffixNeighbor = getNeighbor(&getSuffix(pattern), d);
	for (vector<string>::iterator it = suffixNeighbor.begin(); it != suffixNeighbor.end(); it++) {
		if (getHammingDistance(&getSuffix(pattern), &*it) < d) {
			neighborHood.emplace_back("A" + *it);
			neighborHood.emplace_back("C" + *it);
			neighborHood.emplace_back("G" + *it);
			neighborHood.emplace_back("T" + *it);
		}
		else {
			neighborHood.emplace_back(pattern->substr(0, 1) + *it);
		}
	}


	return neighborHood;
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


vector<string> getFrequentWordsWithMismatch(string* text, int k, int d) {
	vector<string> frequentPattern;
	vector<long long int> close; // neighbor 
	vector<long long int> frequencyArray;
	long long int maxCount = INT_MIN;


	for (long long int i = 0; i < pow(4, k); i++) {
		close.emplace_back(0);
		frequencyArray.emplace_back(0);
	}

	cout << "Finish init close & frequencyArray" << endl;

	for (long long int i = 0; i < (text->length() - k + 1); i++) {
		string pattern = text->substr(i, k);
		vector<string> neighbor = getNeighbor(&pattern, d);

		for (vector<string>::iterator itNeighbor = neighbor.begin(); itNeighbor != neighbor.end(); itNeighbor++) {
			long long int index = patternToNumber(&*itNeighbor);
			close.at(index) = 1;
		}
	}

	cout << "Done get neighbors" << endl;

	for (long long int i = 0; i < pow(4, k); i++) {
		if (i % 10000 == 0)   cout << "getApproximatePatternCount at " << i << endl;
		if (close.at(i) == 1) {
			string pattern = numberToPattern(i, k);
			frequencyArray.at(i) = getApproximatePatternCount(text, &pattern, d);

			string reversePattern;
			reverseComplement(&pattern, &reversePattern);

			frequencyArray.at(i) += getApproximatePatternCount(text, &reversePattern, d);

			if (maxCount < frequencyArray.at(i))
				maxCount = frequencyArray.at(i);
		}
	}

	cout << "Done finding. Preparing output..." << endl;

	for (long int i = 0; i < pow(4, k); i++) {
		if (frequencyArray.at(i) == maxCount) {
			string pattern = numberToPattern(i, k);

			string reversePattern;
			reverseComplement(&pattern, &reversePattern);

			if (find(frequentPattern.begin(), frequentPattern.end(), pattern) == frequentPattern.end())
				frequentPattern.emplace_back(pattern);

			if (find(frequentPattern.begin(), frequentPattern.end(), reversePattern) == frequentPattern.end())
				frequentPattern.emplace_back(reversePattern);
		}
	}


	return frequentPattern;
}


int main() {

	//string text = "ACGTTGCATGTCGCATGATGCATGAGAGCT";
	//int k = 4;
	//int d = 1;

	//string text = "AAAAAAAAAA";
	//int k = 2;
	//int d = 1;

	//string text = "AGTCAGTC";
	//int k = 4;
	//int d = 2;

	//string text = "AATTAATTGGTAGGTAGGTA";
	//int k = 4;
	//int d = 0;

	//string text = "ATA";
	//int k = 3;
	//int d = 1;


	//string text = "AAT";
	//int k = 3;
	//int d = 0;

	//string text = "TAGCG";
	//int k = 2;
	//int d = 1;

	//string text = "ACGTTGCATGTCGCATGATGCATGAGAGCT";
	//int k = 4;
	//int d = 1;


	//string text = "AAAAAAAAAA";
	//int k = 2;
	//int d = 1;

	//string text = "AGTCAGTC";
	//int k = 4;
	//int d = 2;

	//string text = "AATTAATTGGTAGGTAGGTA";
	//int k = 4;
	//int d = 0;

	//string text = "ATA";
	//int k = 3;
	//int d = 1;

	//string text = "AAT";
	//int k = 3;
	//int d = 0;

	//string text = "TAGCG";
	//int k = 2;
	//int d = 1;

	//string text = "";
	//int k = 9;
	//int d = 1;

	////readFrequentWordMisMatch("dataset_9_8.txt",&text,&k,&d);
	//readSalmonella_enterica("Salmonella_enterica.txt", &text);
	////cout << text << endl;
	//cout << "Finish reading gnome..." << endl;

	//vector<string> frequentPattern = getFrequentWordsWithMismatch(&text, k, d);

	//ofstream outputFile;
	//outputFile.open("output.txt");

	//for (vector<string>::iterator it = frequentPattern.begin(); it != frequentPattern.end(); it++) {
	//	outputFile << *it << " ";
	//	cout << *it << " ";
	//}
	//cout << endl;
	//outputFile << endl;

	// quiz
	/*
	string text1 = "TGACCCGTTATGCTCGAGTTCGGTCAGAGCGTCATTGCGAGTAGTCGTTTGCTTTCTCAAACTCC";
	string text2 = "GAGCGATTAAGCGTGACAGCCCCAGGGAACCCACAAAACGTGATCGCAGTCCATCCGATCATACA";

	int hammingDistance = getHammingDistance(&text1, &text2);
	cout << hammingDistance << endl;
	*/

	//string text = "CATGCCATTCGCATTGTCCCAGTGA";
	//string pattern = "CCC";
	//int d = 2;
	//int count = getApproximatePatternCount(&text, &pattern, d);
	//cout << count << endl;

	string pattern = "ACGT";
	int d = 3;
	vector<string> neighbors = getNeighbor(&pattern,d);
	cout << neighbors.size() << endl;

	return 0;
}
