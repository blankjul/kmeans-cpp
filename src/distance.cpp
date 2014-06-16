#include<cmath>
#include "distance.h"

double euclidean(Point v1, Point v2) {
	double sum = 0;
	for (unsigned int i = 0; i < v1.size(); i++) {
		sum += (v1[i] - v2[i]) * (v1[i] - v2[i]);
	}
	return sqrt(sum);
}
 
