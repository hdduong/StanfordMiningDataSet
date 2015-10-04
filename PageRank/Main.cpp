#include <iostream>
#include <stdlib.h>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <hash_map>
using namespace std;

// question 1
//const float beta = 0.7;
//const float PageRankTotal = 3.0; 

// question 2
const float beta = 0.85;
const float PageRankTotal = 3.0;

// question 3
//const float beta = 1.0; 
//const float PageRankTotal = 3.0; 

struct Point{
	int start;
	int end;

	Point(int a, int b) : start(a), end(b) {}
};





void ReadFile(char* filename, vector<shared_ptr<Point> >& vPoint, int* numVertex, hash_map<int, int>& vD) {
	string line;
	ifstream myfile(filename);

	set<int> distinctV;
	std::set<int>::iterator it;

	int a, b;
	while (myfile >> a >> b)
	{
		shared_ptr<Point> newPoint(new Point(a, b));

		vPoint.push_back(newPoint);

		it = distinctV.find(a);
		if (it == distinctV.end())
			distinctV.emplace(a);

		it = distinctV.find(b);
		if (it == distinctV.end())
			distinctV.emplace(b);

		hash_map<int, int>::iterator hmIt = vD.find(a);
		if (hmIt != vD.end()) {
			hmIt->second += 1;
		}
		else {
			vD.emplace(a, 1);
		}
	}

	*numVertex = distinctV.size();
}




void printPointVector(vector<shared_ptr<Point> >& vPoint) {
	for (vector<shared_ptr<Point> >::iterator it = vPoint.begin(); it != vPoint.end(); it++) {
		cout << it->get()->start << " " << it->get()->end << endl;
	}
}


void printIntVector(vector<int>& vInt) {
	for (vector<int>::iterator it = vInt.begin(); it != vInt.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}


void printHashMap(hash_map<int, int>& vInt) {
	for (hash_map<int, int>::iterator it = vInt.begin(); it != vInt.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}

}



// copy content of src to des. Assume that src and des have the same size
// remove content of src
void copyMove(vector<float>& des, vector<float>& src) {
	while (!des.empty())
		des.pop_back();

	des.assign(src.begin(), src.end());

}




bool IsHaveInput(vector<shared_ptr<Point> >& vPoint, int vertex) {
	bool hasInput = false;

	for (vector<shared_ptr<Point> >::iterator itP = vPoint.begin(); itP != vPoint.end(); itP++) {
		if (itP->get()->end == vertex) {
			hasInput = true;
			break;
		}
	}

	return hasInput;
}


float DiffRank(vector<float>& currentR, vector<float>& nextR) {
	float sum = 0.0;

	for (int i = 0; i < nextR.size(); i++) {
		sum += abs(currentR.at(i) - nextR.at(i));
	}

	return sum;
}



void PageRankOneStep(vector<float>& currentR, vector<float>& nextR, hash_map<int, int>& vD, int numVertex, vector<shared_ptr<Point> >& vPoint) {


	vector<float> tempR;

	for (int j = 0; j < currentR.size(); j++) {

		float rpj = 0.0;

		if (!IsHaveInput(vPoint, j)) {
			// no in link; go to next vertex		
			tempR.emplace_back(0.0);
			continue;
		}

		// find j as destination
		for (vector<shared_ptr<Point> >::iterator itP = vPoint.begin(); itP != vPoint.end(); itP++) {
			// find i that point to j
			if (j == itP->get()->end) {
				int i = itP->get()->start;

				int di = vD.find(i)->second;

				rpj += (beta * currentR.at(i)) / di;
			}

		}

		tempR.emplace_back(rpj);

	}

	float S = 0.0;
	for (int j = 0; j < tempR.size(); j++) {
		S += tempR.at(j);
	}

	float leak = (PageRankTotal - S) / numVertex;

	/*
	if (nextR.size() < currentR.size())
	for (int j = 0; j < numVertex; j++) {
	nextR.emplace_back(0.0);
	}
	*/

	for (int j = 0; j < nextR.size(); j++) {
		nextR.at(j) = tempR.at(j) + leak;
	}

}


void PageRankLoop(vector<float>& currentR, vector<float>& nextR, hash_map<int, int>& vD, int numVertex, vector<shared_ptr<Point> >& vPoint) {

	vector<float> tmpR;



	while (1) {
		PageRankOneStep(currentR, nextR, vD, numVertex, vPoint);
		copyMove(tmpR, currentR);
		copyMove(currentR, nextR);
		if (DiffRank(tmpR, currentR) < 0.001) break;
	}
}





int main() {

	hash_map<int, int> vD;
	vector<shared_ptr<Point> > myPoint;
	int numVertex = 0;

	ReadFile("web-Google.txt", myPoint, &numVertex, vD);

	//printPointVector(myPoint);
	//cout << numVertex << endl;
	//printHashMap(vD);

	// first question sum of pageRank = 3
	vector<float> currentR;

	//question 1
	currentR.emplace_back(1.0);
	currentR.emplace_back(1.0);
	currentR.emplace_back(1.0);

	//question 2
	//currentR.emplace_back(0.2);
	//currentR.emplace_back(0.4);
	//currentR.emplace_back(0.4);


	vector<float> nextR;

	nextR.emplace_back(0.0);
	nextR.emplace_back(0.0);
	nextR.emplace_back(0.0);

	/*
	copyMove(nextR,currentR);

	printIntVector(nextR);
	*/

	//PageRankOneStep(currentR, nextR,vD, numVertex,myPoint);
	PageRankLoop(currentR, nextR, vD, numVertex, myPoint);

	cout << endl;

	return 0;
}