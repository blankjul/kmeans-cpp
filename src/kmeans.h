#include <vector>
#include "distance.h"

using namespace std;
typedef std::vector< vector<double> > ndvector;	
typedef double (*distance_func)(vector<double>, vector<double>);

class kmeans {
public:

	kmeans(ndvector, ndvector, distance_func=euclidean);
	~kmeans();

	ndvector learn();
    void print();

    int C;                               // total number of clusters
    int N;                               // total number of training instances
    int D;                               // dimension of one training instance
    int fuzzifier;                       // fuzzifier the determine the fuzzy "softness"
    bool HARD_CLUSTERING;                // really k-means or fuzzy version

    ndvector M;     // mean matrix with current centroids
    ndvector U;     // partition matrix for the cluster
    ndvector v;     // multi dimensional vector with the instances
    
private:
    void calcPartitionMatrix();
    ndvector calcMeanValues();
 	distance_func func;

};
