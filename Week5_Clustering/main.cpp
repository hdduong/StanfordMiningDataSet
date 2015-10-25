#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

struct Point {
public:
	double x;
	double y;

	Point(double _x, double _y) {
		x = _x;
		y = _y;
	}

	double getDistance(Point &aPoint) {
		return sqrt( pow(x-aPoint.x,2) + pow(y-aPoint.y,2) );
	}
};

// each yellowPoint, find nearest greenPoint
void getNearestPoint(vector<Point>& greenPoint, vector<Point>& yellowPoint) {
	
	vector<double> nearestValue;
	vector<double> nearestVertex;

	for (int i = 0; i < yellowPoint.size(); i++) {
		nearestValue.emplace_back(INT_MAX);
	}
	
	for (int i = 0; i < yellowPoint.size(); i++) {
		nearestVertex.emplace_back(-1);
	}
	
	for (int i = 0; i < yellowPoint.size(); i++) {
		double minDis = nearestValue.at(i);

		for (int j = 0; j < greenPoint.size(); j++) {
			if (yellowPoint.at(i).getDistance(greenPoint.at(j)) < minDis) {
				minDis = yellowPoint.at(i).getDistance(greenPoint.at(j));

				nearestValue.at(i) = minDis;
				nearestVertex.at(i) = j;
			}

		}
	}

	vector<Point> newVCentroid;

	for (int j = 0; j < greenPoint.size(); j++) {
		double sumX = greenPoint.at(j).x;
		double sumY = greenPoint.at(j).y;
		int numElement = 1;

		for (int i = 0; i < nearestVertex.size(); i++) {
			
			if (nearestVertex.at(i) == j) {
				numElement++;

				sumX += yellowPoint.at(i).x;
				sumY += yellowPoint.at(i).y;
			}

		}
		
		if (numElement > 1) {
			Point newCentroid(sumX / numElement, sumY / numElement);
			newVCentroid.emplace_back(newCentroid);

			cout << "X: " << sumX / numElement << ", Y:" << sumY / numElement << endl;
		}
	}
	
	for (int i = 0; i < nearestVertex.size(); i++) {
		cout << nearestVertex.at(i) << " ";
	}
	cout << endl;
	// have list of new centroid until here
	vector<double> nearestNewValue;
	vector<double> nearestNewVertex;

	for (int i = 0; i < yellowPoint.size(); i++) {
		nearestNewValue.emplace_back(INT_MAX);
	}

	for (int i = 0; i < yellowPoint.size(); i++) {
		nearestNewVertex.emplace_back(-1);
	}

	for (int i = 0; i < yellowPoint.size(); i++) {
		double minDis = nearestNewValue.at(i);

		for (int j = 0; j < newVCentroid.size(); j++) {
			if (yellowPoint.at(i).getDistance(newVCentroid.at(j)) < minDis) {
				minDis = yellowPoint.at(i).getDistance(newVCentroid.at(j));

				nearestNewValue.at(i) = minDis;
				nearestNewVertex.at(i) = j;
			}

		}
	}
	for (int i = 0; i < nearestNewVertex.size(); i++) {
		cout << nearestNewVertex.at(i) << " ";
	}

}


double getMinDistancePointToRect(Point& aPoint, vector<Point>& rect) {
	double minDis = INT_MAX;
	
	for (int i = 0; i < rect.size(); i++) {
		double distance = aPoint.getDistance(rect.at(i));
		if (distance < minDis)
			minDis = distance;
	}

	return minDis;
}

double getMaxDistancePointToRect(Point& aPoint, vector<Point>& rect) {
	double maxDis = INT_MIN;


	for (int i = 0; i < rect.size(); i++) {
		double distance = aPoint.getDistance(rect.at(i));
		if (distance > maxDis)
			maxDis = distance;
	}
	return maxDis;
}


void getKMean(Point& pointY, Point& pointG, vector<Point>& rectY, vector<Point>& rectG) {
	if (
		(getMaxDistancePointToRect(pointG, rectG) < getMinDistancePointToRect(pointY, rectG)) &&
		(getMinDistancePointToRect(pointG, rectY) > getMaxDistancePointToRect(pointY, rectY))
		) {
		cout << "TRUE" << endl;
	}
	else {
		cout << "FALSE" << endl;
	}
}


void CureAlgorithm(vector<Point>& representPoint, vector<Point>& freePoint) {

	while (freePoint.size() > 0) {
		int removingPointIndex = -1;
		double maxDis = INT_MIN;
		double minDisEachFree = INT_MAX;

		for (int i = 0; i < freePoint.size(); i++) {
			minDisEachFree = INT_MAX;
			
			for (int j = 0; j < representPoint.size(); j++) {
				
				double freeToRepre = freePoint.at(i).getDistance(representPoint.at(j));

				if (freeToRepre < minDisEachFree) {
					minDisEachFree = freeToRepre;
				}
			}
			
			if (maxDis < minDisEachFree) {
				maxDis = minDisEachFree;
				removingPointIndex = i;
			}
		}

		

		Point addingPoint(freePoint.at(removingPointIndex).x, freePoint.at(removingPointIndex).y);
		representPoint.emplace_back(addingPoint);

		freePoint.erase(freePoint.begin() + removingPointIndex);
		
	}

}
int main() {
	
	//vector<Point> greenPoint;
	//Point greenPoint1(25,125);
	//Point greenPoint2(29, 97);
	//Point greenPoint3(35, 63);
	//Point greenPoint4(42, 57);
	//Point greenPoint5(23, 40);
	//Point greenPoint6(33, 22);
	//Point greenPoint7(44, 105);
	//Point greenPoint8(55, 63);
	//Point greenPoint9(55, 20);
	//Point greenPoint10(64, 37);
	//greenPoint.emplace_back(greenPoint1);
	//greenPoint.emplace_back(greenPoint2);
	//greenPoint.emplace_back(greenPoint3);
	//greenPoint.emplace_back(greenPoint4);
	//greenPoint.emplace_back(greenPoint5);
	//greenPoint.emplace_back(greenPoint6);
	//greenPoint.emplace_back(greenPoint7);
	//greenPoint.emplace_back(greenPoint8);
	//greenPoint.emplace_back(greenPoint9);
	//greenPoint.emplace_back(greenPoint10);

	//vector<Point> yellowPoint;
	//Point yellowPoint1(28,145);
	//Point yellowPoint2(50, 130);
	//Point yellowPoint3(65, 140);
	//Point yellowPoint4(38, 115);
	//Point yellowPoint5(55, 118);
	//Point yellowPoint6(43, 83);
	//Point yellowPoint7(50, 90);
	//Point yellowPoint8(63, 88);
	//Point yellowPoint9(50, 60);
	//Point yellowPoint10(50, 30);
	//yellowPoint.emplace_back(yellowPoint1);
	//yellowPoint.emplace_back(yellowPoint2);
	//yellowPoint.emplace_back(yellowPoint3);
	//yellowPoint.emplace_back(yellowPoint4);
	//yellowPoint.emplace_back(yellowPoint5);
	//yellowPoint.emplace_back(yellowPoint6);
	//yellowPoint.emplace_back(yellowPoint7);
	//yellowPoint.emplace_back(yellowPoint8);
	//yellowPoint.emplace_back(yellowPoint9);
	//yellowPoint.emplace_back(yellowPoint10);
	//
	//getNearestPoint(greenPoint, yellowPoint);


	//Point yelllowPoint(5, 10);
	//Point greenPoint(20, 5);

	
	//Point yellowUL(6, 15);
	//Point yellowBL(6, 7);
	//Point yellowUR(13, 15);
	//Point yellowBR(13, 7);
	//Point greenUL(16, 16);
	//Point greenBL(16, 5);
	//Point greenUR(18, 16);
	//Point greenBR(18, 5);
	
	//Point yellowUL(3, 15);
	//Point yellowBL(3, 7);
	//Point yellowUR(13, 15);
	//Point yellowBR(13, 7);
	//Point greenUL(14, 10);
	//Point greenBL(14, 6);
	//Point greenUR(23, 10);
	//Point greenBR(23, 6);

	//Point yellowUL(3, 15);
	//Point yellowBL(3, 7);
	//Point yellowUR(13, 15);
	//Point yellowBR(13, 7);
	//Point greenUL(11, 5);
	//Point greenBL(11, 2);
	//Point greenUR(17, 5);
	//Point greenBR(17, 2);

	//Point yellowUL(6, 7);
	//Point yellowBL(6, 4);
	//Point yellowUR(11, 7);
	//Point yellowBR(11, 4);
	//Point greenUL(14, 10);
	//Point greenBL(14, 6);
	//Point greenUR(23, 10);
	//Point greenBR(23, 6);




	//vector<Point> yelllowRect;
	//yelllowRect.emplace_back(yellowUL);
	//yelllowRect.emplace_back(yellowBL);
	//yelllowRect.emplace_back(yellowUR);
	//yelllowRect.emplace_back(yellowBR);

	//vector<Point> greenRect;
	//greenRect.emplace_back(greenUL);
	//greenRect.emplace_back(greenBL);
	//greenRect.emplace_back(greenUR);
	//greenRect.emplace_back(greenBR);

	//getKMean(yelllowPoint, greenPoint, yelllowRect, greenRect );

	vector<Point> representPoint;
	Point x(0,0);
	Point y(10, 10);
	representPoint.emplace_back(x);
	representPoint.emplace_back(y);

	vector<Point> freePoint;
	Point a(1, 6);
	Point b(3, 7);
	Point c(4, 3);
	Point d(7, 7);
	Point e(8, 2);
	Point f(9, 5);
	freePoint.emplace_back(a);
	freePoint.emplace_back(b);
	freePoint.emplace_back(c);
	freePoint.emplace_back(d);
	freePoint.emplace_back(e);
	freePoint.emplace_back(f);

	CureAlgorithm(representPoint, freePoint);
	cout << endl;
	return 0;
}