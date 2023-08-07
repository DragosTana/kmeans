//
// Created by dragos on 31/10/22.
//

#include "initializer.cpp"
#include "utils.cpp"
#include <omp.h>

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

std::vector<Point> kMeansClustering( std::vector<Point>& data, std::vector<Point>& centroids, int& epochs, int& k, int& threads){
    double tstart, tstop;
    int count = 0;
    int clusters_size[k];

    // tmp variables
    std::vector<Point> new_centroids = std::vector<Point>(k);
    int partial_clusters_size[omp_get_max_threads()][k];
    std::vector<Point> partial_new_centroids[omp_get_max_threads()];
    double partial_rel_diff[k];

    for (int i=0; i<omp_get_max_threads(); i++)
    {
        partial_new_centroids[i] = std::vector<Point>(k);
        for (int j=0; j<k; j++)
        {
            partial_clusters_size[i][j] = 0;
            partial_new_centroids[i][j].to_zero(j);
        }
    }

    int try_num = 1;
    for(int i = 0; i < epochs; i++){

        // assign each point to the cluster of the closest centroid, prepare the sum, increment clusters size.
#pragma omp parallel for num_threads(omp_get_max_threads()) default(none) shared(centroids, partial_new_centroids, partial_clusters_size, data) schedule(static, 64)
            for(auto & p : data)
            {
                double best_distance = DBL_MAX;
                for (auto &c: centroids) {
                    double dist = c.compute_distance(p);
                    if (dist < best_distance) {
                        best_distance = dist;
                        p.cluster = c.cluster;
                    }
                }
                partial_new_centroids[omp_get_thread_num()][p.cluster] += p;
                partial_clusters_size[omp_get_thread_num()][p.cluster]++;
            }

#pragma omp parallel for num_threads(k) default(none) shared(new_centroids, partial_new_centroids, partial_clusters_size, partial_rel_diff) firstprivate(centroids, clusters_size, k) schedule(static, 64)
        for (int i=0; i < k; i++)
        {
            new_centroids[i].to_zero(i);
            clusters_size[i] = 0;
            for (int j = 0; j < omp_get_max_threads(); j++)
            {
                // merge partial results
                new_centroids[i] += partial_new_centroids[j][i];
                clusters_size[i] += partial_clusters_size[j][i];
                // clean tmp vars
                partial_new_centroids[j][i].to_zero(i);
                partial_clusters_size[j][i] = 0;
            }
            new_centroids[i] /= clusters_size[i];  // updates directly a shared var because each thread writes in a predetermined different location (since schedule static 1 and different thread -> different i -> different locations)
        }

        centroids = new_centroids;
        count++;
    }

    return centroids;
}

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