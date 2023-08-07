//
// Created by dragos on 31/10/22.
//

#include "initializer.cpp"
#include "utils.cpp"
#include <omp.h>

/*
* This function implemts the kmeans algorithm
* @param points: the vector of points to be clustered
* @param centroids: the vector of centroids
* @param epochs: the number of epochs
* @param k: the number of clusters
* @return a vector of centroids
*/
std::vector<Point> kmean_seq (std::vector<Point>& points, std::vector<Point>& centroids, int& epochs, int& k, int& threads) {
    std::vector<Point> new_centroids = std::vector<Point>(k);
    int cluster_cardinality[k];

    for(int i = 0; i < epochs; i++){

        for(int j = 0; j < k; j++){
            new_centroids[j].to_zero(-1);
            cluster_cardinality[j] = 0;
        }
        //begin iterating through points
        for (Point& p: points){
            double distance = DBL_MAX;
            for(int i = 0; i < k; i++){
                if (euclidean_dist(p, centroids[i]) < distance) {
                    distance = euclidean_dist(p, centroids[i]);
                    p.cluster = i;
                }
            }
            //std::cout<<p.cluster<<std::endl;
            new_centroids[p.cluster] += p;      // this should not be shared
            cluster_cardinality[p.cluster]++;
        }

        for(int i = 0; i < k; i++){
            new_centroids[i] /= cluster_cardinality[i];
        }
        centroids = new_centroids;

    }
    return centroids;
}

/*
* This function implemts a parallel version of the kmeans algorithm
* @param points: the vector of points to be clustered
* @param centroids: the vector of centroids
* @param epochs: the number of epochs
* @param k: the number of clusters
* @return a vector of centroids
*/
std::vector<Point> kmean_par (std::vector<Point>& points, std::vector<Point>& centroids, int& epochs, int& k, int& threads) {
    std::vector<Point> new_centroids = std::vector<Point>(k);
    int cluster_cardinality[k];
    std::vector<Point> tmp_new_centroids = std::vector<Point>(k);
    int tmp_cluster_cardinality[k];
    //std::cout<< centroids.size()<<std::endl;
    //std::cout<<std::endl;

    for (int i = 0; i < epochs; i++) {

        #pragma omp parallel firstprivate(tmp_new_centroids, tmp_cluster_cardinality) num_threads(threads) 
        {

        #pragma omp for schedule(static, 64)
        for(int j = 0; j < k; j++){
            new_centroids[j].to_zero(-1);
            cluster_cardinality[j] = 0;
        }

        #pragma omp for
        for (Point& p: points){
            double distance = DBL_MAX;
            for(int i = 0; i < k; i++){
                
                if (euclidean_dist(p, centroids[i]) < distance) {
                    distance = euclidean_dist(p, centroids[i]);
                    p.cluster = i;
                }
            }
            tmp_new_centroids[p.cluster] += p;      
            tmp_cluster_cardinality[p.cluster]++;
        }

        #pragma omp critical
        {
            for(int i = 0; i < k; i++){
                new_centroids[i] += tmp_new_centroids[i];
                cluster_cardinality[i] += tmp_cluster_cardinality[i];
            }
        }
        }
    }
    
    for(int i = 0; i < k; i++){
        new_centroids[i] /= cluster_cardinality[i];
    }
    return new_centroids;
}