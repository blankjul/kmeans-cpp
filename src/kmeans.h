#include <vector>
#include "distance.h"

using namespace std;
typedef std::vector< vector<double> > ndvector;	
typedef double (*funcDistance)(vector<double>, vector<double>);

class kmeans {
public:

	kmeans(ndvector, ndvector, funcDistance=euclidean, int=100,int=3,bool=true);
	~kmeans();

	ndvector learn();
    void print();

    int C;                               // total number of clusters
    int N;                               // total number of training instances
    int D;                               // dimension of one training instance
    int FUZZIFIER;                       // fuzzifier the determine the fuzzy "softness"
    bool HARD_CLUSTERING;                // really k-means or fuzzy version
    int MAX_ITERATION;                   // maximal iterations without convering

    ndvector M;                          // mean matrix with current centroids
    ndvector U;                          // partition matrix for the cluster
    ndvector v;                          // multi dimensional vector with the instances
    
private:
    void calcPartitionMatrix();
    ndvector calcMeanValues();
    funcDistance func;

};


