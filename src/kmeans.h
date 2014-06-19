#include <vector>
#include "distance.h"

using namespace std;
typedef std::vector< vector<double> > ndvector;	
typedef double (*funcDistance)(vector<double>, vector<double>);

class kmeans {

    public:

        kmeans(ndvector,int,ndvector=ndvector());
        ~kmeans();

        ndvector learn();
        bool next();
        void print(bool=true,bool=true);


        int FUZZIFIER;                       // fuzzifier the determine the fuzzy "softness"
        int MAX_ITERATION;                   // maximal iterations without convering
        bool HARD_CLUSTERING;                // really k-means or fuzzy version
        funcDistance func;                   // distance function
        ndvector M;                          // mean matrix with current centroids

        int iIteration;

    private:

        int C;                               // total number of clusters
        int N;                               // total number of training instances
        int D;                               // dimension of one training instance

        ndvector U;                          // partition matrix for the cluster
        ndvector v;                          // multi dimensional vector with the instances

        ndvector randomCentroids(unsigned int);
        ndvector calcMeanValues();
        void calcPartitionMatrix();


};


