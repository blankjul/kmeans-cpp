#include <vector>
#include "distance.h"

using namespace std;
typedef std::vector< vector<double> > ndvector;	
typedef double (*funcDistance)(vector<double>, vector<double>);

class kmeans {

    public:

        /**
         *  \param v data vector with all the data points
         *  \param k number of cluster that should be found
         *  \param centroids given centroids that should be used at the beginning
         */
        kmeans(ndvector v,int k,ndvector centroids =ndvector());

        /**
         * Destructor
         */
        ~kmeans();


        /**
         * Search for the best k-Cluster. That means minimize all distances
         * from the cluster to each of the points.
         *
         * \retval ndvector multidimensional vector with the cluster centers.
         */
        ndvector learn();
        
        /**
         * This function does only process one iteration. That could be useful
         * to visualize the current data set included the means or to have an
         * interactive output.
         *
         * \retval true if MAX_ITERATION is reached or it has converged.
         * \retval false MAX_ITERATION not reached and not converged.
         *
         */ 
        bool next();

        void printPartitionMatrix();
        void printMeans();


        int iFuzzifier;                      //!< fuzzifier the determine the fuzzy "softness"
        int iMaxIteration;                   //!< maximal iterations without converging
        bool bHardClustering;                //!< really k-means or fuzzy version
        funcDistance func;                   //!< distance function
        double dTargetValue;                 //!< current target value of the performance function
        double epsilon;                      //!< epsilon that determines the convergence

        int iIteration;                      //!< counter for the current iteration

    private:

        int C;                               //!< total number of clusters
        int N;                               //!< total number of training instances
        int D;                               //!< dimension of one training instance

        ndvector U;                          //!< partition matrix for the cluster
        ndvector X;                          //!< multi dimensional vector with the instances
        ndvector M;                          //!< mean matrix with current centroids

        /**
         * Search for random centroids if there are not given.
         * 
         * \param k number of the cluster
         * \retval ndvector with the centroids
         */
        ndvector randomCentroids(unsigned int k);
        
        
        double calcMeanValues();


        void calcPartitionMatrix();
        


};


