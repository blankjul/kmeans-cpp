#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include "kmeans.h"



using namespace std;

kmeans::kmeans(ndvector v, ndvector centroids, distance_func func) {
	this->func = func;
    this->v = v;
    this->M = centroids;

	C = M.size();
	N = v.size();	
	D = v[0].size();
      
    fuzzifier = 3;
    HARD_CLUSTERING = true;
 
}

kmeans::~kmeans() {}



void kmeans::calcPartitionMatrix() {
    // calculate the complete partition matrix U
    U = ndvector(C,vector<double>(N));
    double exp = 2 / (1-fuzzifier);
    for (int j = 0; j < N; j++) {	// for each point search for centroid
    	vector<double> distances(C);
        double denom = 0.0;
    	for (int i = 0; i < C; i++) {	// calculate the distance to each centroid
            double fuzzy_distance = pow(func(v[j], M[i]),exp);
            denom += fuzzy_distance;
            distances[i] = fuzzy_distance;
    	}                        
        if (HARD_CLUSTERING) {
        int index = distance(distances.begin(),max_element(distances.begin(),distances.end()));


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
            double w = (U[i][j] != 0) ? pow(U[i][j],fuzzifier) : 0;
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


ndvector kmeans::learn() {
    int max_it = 5;
	int it = 0;

	while (it++ < max_it) {
		
        calcPartitionMatrix();
        M = calcMeanValues();

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


int main(int argc, char **argv){

    double array[] = {{1,5},{6,2},{8,1},{3,5},{2,4},{2,6},{6,1},{6,8},{7,3},{7,6},{8,3},{8,7}};
	ndvector v = vector<double>(&array[0],&array[0] + sizeof(array) / sizeof(double));
    //ndvector v = {{1},{3},{4},{5},{8},{10},{11},{12}};
	ndvector centroids;
    centroids = {{1,5},{6,2},{8,1}};
    //ndvector centroids = {{1},{5}};
	kmeans tmp(v, centroids);
	
	centroids = tmp.learn();       

    tmp.print();
}


