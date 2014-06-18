#include <set>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include "kmeans.h"


using namespace std;

kmeans::kmeans(ndvector v_, int k) {
	func = euclidean;
    v = v_;
	C = k;
	N = v.size();	
	D = v[0].size();
        

    FUZZIFIER = 3;
    HARD_CLUSTERING = false;
    MAX_ITERATION = 10;
    
 
}


kmeans::~kmeans() {}


ndvector kmeans::learn() {

	int it = 0;

    if (M.size() == 0) M = randomCentroids(C);
	while (it++ < MAX_ITERATION) {
		
        calcPartitionMatrix();
        M = calcMeanValues();

	}
	
	return M;
}

ndvector kmeans::randomCentroids(int k) {
    ndvector centroids;
    set<int> indices;
    while (indices.size() < k) {
        srand(time(NULL));
        int range = v.size() + 1;
        int num = rand() % range;
        indices.insert(num);
    }
    for (set<int>::iterator it = indices.begin(); it != indices.end(); ++it) {
        centroids.push_back(v[*it]);
        cout << *it << " ";
    }       
    return centroids;
}

void kmeans::calcPartitionMatrix() {
    // calculate the complete partition matrix U
    U = ndvector(C,vector<double>(N));
    double exp = 2 / (1-FUZZIFIER);
    for (int j = 0; j < N; j++) {	// for each point search for centroid
    	vector<double> distances(C);
        double denom = 0.0;
    	for (int i = 0; i < C; i++) {	// calculate the distance to each centroid
            double fuzzy_distance = pow(func(v[j], M[i]),exp);
            denom += fuzzy_distance;
            distances[i] = fuzzy_distance;
    	}                        
        if (HARD_CLUSTERING) {
            int ind = distance(distances.begin(),max_element(distances.begin(),distances.end()));
            U[ind][j] = 1;
        } else { for (int i = 0; i < C; i++) {
                double tmp = distances[i];
                U[i][j] = (!isinf(tmp)) ? distances[i] / denom : 1;
            }
        }
    }
}



ndvector kmeans::calcMeanValues() {
    // calculate the new mean vector using U and X
    ndvector M = ndvector(C,vector<double>(D));
    for (int i = 0; i < C; ++i) {
        double sum_w = 0.0;
        for (int j = 0; j < N; ++j) {
            double w = (U[i][j] != 0) ? pow(U[i][j],FUZZIFIER) : 0;
            for(int k = 0; k < D; ++k) {
                M[i][k] += v[j][k] * w;    
            }
            sum_w += w;
        }
        for(int k = 0; k < D; ++k) {
           M[i][k] /= sum_w;
        }
    }
    return M;
}

void kmeans::print() {
    cout << "------------------  U  ----------------" << endl;
    for (int j = 0; j < N; j++) {	// for each point search for centroid
       	for (int i = 0; i < C; i++) {
              cout << U[i][j]<< " " ;         
        }
        cout << endl;
    }
    cout << endl;

    cout << "------------------  M  ----------------" << endl;
    for (int i = 0; i < C; ++i) {
         for(int k = 0; k < D; ++k) {
               cout << M[i][k] << "  ";
         }
         cout << endl;
    }
}

