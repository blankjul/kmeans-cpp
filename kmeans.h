#include <vector>
#include "distance.h"

using namespace std;
typedef std::vector< vector<double> > ndvector;	
typedef double (*distance_func)(vector<double>, vector<double>);

class kmeans {
public:
	kmeans( distance_func=euclidean);
	~kmeans();
	ndvector learn(ndvector, ndvector, int);
private:
	int k;		// number of cluster
	int n;		// number of instances
	int d;		// dimension of the points
	bool is_converged;
	
 	distance_func func;
};
