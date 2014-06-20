#include <set>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include "kmeans.h"


using namespace std;

kmeans::kmeans(ndvector v_, int k, ndvector centroids) {
    func = euclidean;
    X = v_;
    C = k;
    N = X.size();	
    D = X[0].size();

    iIteration = 0;
    epsilon = 1e-5;
    iFuzzifier = 2;
    bHardClustering = false;
    iMaxIteration = numeric_limits<int>::max();

    M = (centroids.size() == 0) ? randomCentroids(C) : centroids;
}


kmeans::~kmeans() {}


ndvector kmeans::learn() {
    bool bContinue = true;
    while (bContinue) bContinue = next();
    return M;
}

bool kmeans::next() {
    calcPartitionMatrix();
    double dTargetValue_ = calcMeanValues();
    bool bContinue = iIteration++ < iMaxIteration \
                     and fabs(dTargetValue_ -  dTargetValue) >= epsilon;
    dTargetValue = dTargetValue_;
    return bContinue;
}

ndvector kmeans::randomCentroids(unsigned int k) {
    ndvector centroids = X;
    random_shuffle(centroids.begin(),centroids.end());
    return ndvector(centroids.begin(), centroids.begin() + C);
}

void kmeans::calcPartitionMatrix() {
    // calculate the complete partition matrix U
    U = ndvector(C,vector<double>(N));
    double exp = 2 / (1-iFuzzifier);
    for (int j = 0; j < N; j++) {	// for each point search for centroid
        vector<double> distances(C);
        double denom = 0.0;
        for (int i = 0; i < C; i++) {	// calculate the distance to each centroid
            double fuzzy_distance = pow(func(X[j], M[i]),exp);
            denom += fuzzy_distance;
            distances[i] = fuzzy_distance;
        }                        
        if (bHardClustering) {
            int ind = distance(distances.begin(),max_element(distances.begin(),distances.end()));
            U[ind][j] = 1;
        } else {
            for (int i = 0; i < C; i++) {
                double tmp = distances[i];
                U[i][j] = (!isinf(tmp)) ? distances[i] / denom : 1;
            }
        }
    }
}



double kmeans::calcMeanValues() {
    // calculate the new mean vector using U and X
    M = ndvector(C,vector<double>(D));
    double dTargetValue_ = 0.0;
    for (int i = 0; i < C; ++i) {
        double sum_w = 0.0;
        for (int j = 0; j < N; ++j) {
            double w = (U[i][j] != 0) ? pow(U[i][j],iFuzzifier) : 0;
            for(int k = 0; k < D; ++k) {
                M[i][k] += X[j][k] * w;    
                dTargetValue_ += fabs(X[j][k] - M[i][k]);
            }
            sum_w += w;
        }
        for(int k = 0; k < D; ++k) {
            M[i][k] /= sum_w;
        }
    }
    return dTargetValue_;
}


void kmeans::printPartitionMatrix() {

    if (U.size() != 0) {
        cout << "------------------  U  ----------------" << endl;
        for (int j = 0; j < N; j++) {	// for each point search for centroid
            for (int i = 0; i < C; i++) {
                cout << U[i][j]<< " " ;         
            }
            cout << endl;
        }
        cout << endl;
    }


}
void kmeans::printMeans() {

    cout << "------------------  M  ----------------" << endl;
    for (int i = 0; i < C; ++i) {
        for(int k = 0; k < D; ++k) {
            cout << M[i][k] << "  ";
        }
        cout << endl;
    }
}

