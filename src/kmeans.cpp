#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>
#include <tclap/CmdLine.h>
#include "kmeans.h"
#include "reader.h"


using namespace std;

kmeans::kmeans(ndvector v_, ndvector centroids, funcDistance func_, int iMaxIteration, int fuzzifier, bool bHardClustering ) {
	func = func_;
    v = v_;
    M = centroids;
    FUZZIFIER = fuzzifier;
    HARD_CLUSTERING = bHardClustering;
    MAX_ITERATION = iMaxIteration;

	C = M.size();
	N = v.size();	
	D = v[0].size();
        
 
}

kmeans::~kmeans() {}



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


ndvector kmeans::learn() {

	int it = 0;

	while (it++ < MAX_ITERATION) {
		
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
    
    string sFileName;
    string sCentroidFile;

    try {  
        TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
        TCLAP::UnlabeledValueArg<string> cmdFile( "data","unlabeled test",true,"","csv file" );
        TCLAP::UnlabeledValueArg<string> cmdCentroids( "centroids","",false,"","csv file centroids" );
        cmd.add( cmdFile );
        cmd.add( cmdCentroids );
        cmd.parse(argc, argv);
        sFileName= cmdFile.getValue();
        sCentroidFile = cmdCentroids.getValue();

    } catch (TCLAP::ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
    }
    

    CSVReader r;
    
    ndvector v = r.read(sFileName);
    ndvector centroids = r.read(sCentroidFile);

    cout << v.size() << endl;
    cout << centroids.size() << endl;
    kmeans c =kmeans(v,centroids);
    c.learn();
    c.print();
    return EXIT_SUCCESS;

}


