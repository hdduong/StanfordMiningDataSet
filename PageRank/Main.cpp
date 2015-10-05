#include <iostream>
#include <stdlib.h>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <map>
using namespace std;

// question 1
//const float beta = 0.7;
//const float PageRankTotal = 3.0; 

// question 2
//const double beta = 0.8;
//const double PageRankTotal = 3.0;

// question 3
//const double beta = 1.0; 
//const double PageRankTotal = 3.0; 



// programming assignment
const double beta = 0.8; //random teleporting probability of 0.2  means teleport is (1 - 0.2)
const double PageRankTotal = 1.0;


// example from book http://infolab.stanford.edu/~ullman/mmds/ch5.pdf 5.1.6
//const double beta = 0.8;
//const double PageRankTotal = 1.0;


// mOut contains src and list of des vectex
// mIn contains des and list of src vertex
// mVertexMap map continuous id 
void ReadFile(char* filename, map<long int, vector<long int> >& mIn, map<long int, vector<long int> >& mOut, map<long int, long int>& mIdNature, map<long int, long int>& mIdFile) {
	string line;
	ifstream myfile(filename);

	long int a, b;
	long int Id = 0;

	map<long int, vector<long int> >::iterator mInIterator;
	map<long int, vector<long int> >::iterator mOutIterator;
	
	set<long int> setV; // set order by Key
	set<long int>::iterator idSetIt;

	while (myfile >> a >> b)
	{
		setV.emplace(a);
		setV.emplace(b);

		mOutIterator = mOut.find(a);
		if (mOutIterator != mOut.end()) {
			mOutIterator->second.push_back(b);
		}
		else {
			vector<long int> vDes;
			vDes.push_back(b);

			mOut.emplace(a, vDes);
		}

		mInIterator = mIn.find(b);
		if (mInIterator != mIn.end()) {
			mInIterator->second.push_back(a);
		}
		else {
			vector<long int> vSrc;
			vSrc.push_back(a);

			mIn.emplace(b, vSrc);
		}
	}

	for (idSetIt = setV.begin(); idSetIt != setV.end(); idSetIt++) {
		mIdNature.emplace(Id, *idSetIt);
		mIdFile.emplace(*idSetIt, Id);
		Id++;
	}

}





void printIntVector(vector<int>& vInt) {
	for (vector<int>::iterator it = vInt.begin(); it != vInt.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}


void printHashMap(map<int, int>& vInt) {
	for (map<int, int>::iterator it = vInt.begin(); it != vInt.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}

}



// copy content of src to des. Assume that src and des have the same size
// remove content of src
void copyMove(vector<double>& des, vector<double>& src) {
	while (!des.empty())
		des.pop_back();

	des.assign(src.begin(), src.end());

}



// check if vertex has in-deg
bool IsHaveInput(map<long int, vector<long int> >& mIn, long int vertex) {
	bool hasInput = false;

	map<long int, vector<long int> >::iterator it = mIn.find(vertex);
	if (it != mIn.end())
		hasInput = true;

	return hasInput;
}


double DiffRank(vector<double>& currentR, vector<double>& nextR) {
	double sum = 0.0;

	for (int i = 0; i < nextR.size(); i++) {
		sum += abs(currentR.at(i) - nextR.at(i));
	}

	return sum;
}



void PageRankOneStep(vector<double>& currentR, vector<double>& nextR, map<long int, vector<long int> >& mIn, map<long int, vector<long int> >& mOut, long int numVertex, map<long int, long int>& mIdNature, map<long int, long int>& mIdFile) {


	vector<double> tempR;
	for (int i = 0; i < numVertex; i++) {
		tempR.emplace_back(double(0.0));
	}

	//for (int j = 0; j < currentR.size(); j++) {
	for (map<long int, long int>::iterator itJ = mIdFile.begin(); itJ != mIdFile.end(); itJ++) {
		
		long int j = itJ->first;
		long int jNature = itJ->second;

		double rpj = 0.0;

		if (!IsHaveInput(mIn, j)) {
			
			// no in link; go to next vertex		
			tempR.at(jNature) = 0.0;
			continue;
		}

		
		vector<long int> listI = mIn.find(j)->second; // list of vertex i that has j as destination
		
		for (vector<long int>::iterator itI = listI.begin(); itI != listI.end(); itI++) {
			
			long int di = mOut.find(*itI)->second.size();
			long int diNature = mIdFile.find(*itI)->second;

			rpj += (beta * currentR.at(diNature)) / di;
			

		}
		tempR.at(jNature) = rpj;
	}

	double S = 0.0;
	for (int j = 0; j < tempR.size(); j++) {
		S += tempR.at(j);
	}

	double leak = (PageRankTotal - S) / numVertex;

	for (int j = 0; j < nextR.size(); j++) {
		nextR.at(j) = tempR.at(j) + leak;
	}

}


void PageRankLoop(vector<double>& currentR, vector<double>& nextR, map<long int, vector<long int> >& mIn, map<long int, vector<long int> >& mOut, long int numVertex, map<long int, long int>& mIdNature, map<long int, long int>& mIdFile) {

	vector<double> tmpR;
	long int loopCount = 0;
	while (1) {
		cout << "start at loop: " << loopCount << endl;

		PageRankOneStep(currentR, nextR, mIn, mOut, numVertex, mIdNature,mIdFile);
		copyMove(tmpR, currentR);
		copyMove(currentR, nextR);
		if (DiffRank(tmpR, currentR) < 0.0000001) break;

		loopCount++;
	}
}


void initStepVector(vector<double>& currentR, vector<double>& nextR, long int numVertex) {
	for (int i = 0; i < numVertex; i++) {
		currentR.emplace_back(double((double)1.0 / numVertex) );
		nextR.emplace_back(double(0.0));
	}

}


int main() {

	map<long int, vector<long int> > mIn;
	map<long int, vector<long int> > mOut;
	map<long int, long int> mIdNature;
	map<long int, long int> mIdFile;

	long int numVertex = 875713;
	//long int numVertex = 4;
	//long int numVertex = 25000;

	vector<double> currentR;
	vector<double> nextR;

	initStepVector(currentR, nextR, numVertex);

	ReadFile("web-Google.txt", mIn, mOut, mIdNature, mIdFile);
	//ReadFile("input2.txt", mIn, mOut, mIdNature, mIdFile); // book page 5.1.6 http://infolab.stanford.edu/~ullman/mmds/ch5.pdf
	//ReadFile("web-Google-small.txt", mIn, mOut, mIdNature, mIdFile); // test case: https://class.coursera.org/mmds-003/forum/thread?thread_id=160
	cout << "Done with reading File" << endl;

	//PageRankOneStep(currentR, nextR, mIn, mOut, numVertex);
	
	PageRankLoop(currentR, nextR, mIn, mOut, numVertex, mIdNature, mIdFile);

	//cout << "mIdFile[99]: " << mIdFile.find(99)->second << "value: " << nextR.at(mIdFile.find(99)->second) << endl; 
	cout << "mIdFile[0]: " << mIdFile.find(0)->second << "value: " << nextR.at(mIdFile.find(0)->second) << endl;
	cout << "mIdFile[99]: " << mIdFile.find(0)->second << "value: " << nextR.at(mIdFile.find(99)->second) << endl;
	cout << "mIdFile[11342]: " << mIdFile.find(0)->second << "value: " << nextR.at(mIdFile.find(11342)->second) << endl;
	cout << "mIdFile[824020]: " << mIdFile.find(0)->second << "value: " << nextR.at(mIdFile.find(824020)->second) << endl;
	cout << "mIdFile[903066]: " << mIdFile.find(0)->second << "value: " << nextR.at(mIdFile.find(903066)->second) << endl;

	//cout << 

	return 0;
}