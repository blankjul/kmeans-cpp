#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include "kmeans.h"


kmeans::kmeans(distance_func func) {
	this->func = func;
}
kmeans::~kmeans() {}

ndvector kmeans::learn(ndvector v, ndvector centroids, int max_it) {

	int k = centroids.size(); // number of clusters 
	int n = v.size();	  // number of point
	int d = v[0].size();	  // dimension            
	bool is_converged = false;				
	int it = 0;   // iterator to count calcuation of centroids

	while (it++ < max_it and is_converged == false) {
	        // counts how many points belongs to this cluster
		std::vector<int> cluster_counter(k);
		// vector for mean calculation
		ndvector means(k, std::vector<double>(d));

		for (int i = 0; i < n; i++) {	// for each point search for centroid
			
			int min_index = -1;		// index of the nearest centroid
			double min_distance = std::numeric_limits<double>::infinity();
			for (int j = 0; j < k; j++) {	// calculate the distance to each centroid
				double distance = func(v[i], centroids[j]);
				if (distance < min_distance) {
					min_index = j;
					min_distance = distance;	
				}
			}
			
			++cluster_counter[min_index];	// increment the counter by one
			for(int l = 0; l < d; l++) {	// data for calculating the mean later
				means[min_index][l] += v[i][l];
			}

		}
		
		// compute new centroid vectors
		is_converged = true;
		for (int j = 0; j < k; j++) {		// iterate over all cluster
			for(int l = 0; l < d; l++) {	// iterate over all dimensions
				
				double mean = means[j][l] / cluster_counter[j];
				if (is_converged and mean != centroids[j][l]) is_converged = false;
				centroids[j][l] = mean;
			}
		}

	
	}
	
	return centroids;
}



int main(int argc, char **argv){

	ndvector v = {{1,5},{6,2},{8,1},{3,5},{2,4},{2,6},{6,1},{6,8},{7,3},{7,6},{8,3},{8,7}};

	const int d = 2;
	const int k = 3;
	ndvector centroids(k, std::vector<double>(d));
	centroids = {{1,5},{6,2},{8,1}};

	kmeans tmp;
	
	centroids = tmp.learn(v, centroids, 100);       
	
	for (unsigned int j = 0; j < centroids.size(); j++) {		// iterate over all cluster
		for(int l = 0; l < d; l++) {			// iterate over all dimensions
			std::cout << centroids[j][l] << " ";
		}
		std::cout << std::endl;
		
	}


}


