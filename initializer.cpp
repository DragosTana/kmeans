//
// Created by dragos on 31/10/22.
//

#pragma once
#include "Point.h"
#include <random>

/*
* This function checks if a point is already in a vector of points
* @param points: the vector of points
* @param p: the point to be checked
* @return true if the point is in the vector, false otherwise
*/
bool contatins(std::vector<Point>& points, Point&  p){
    for(Point el: points){
        if(el == p){
            return true;
        }
    }
    return false;
}

/*
* This function randomly initializes the centroids
* @param points: the vector of points
* @param k: the number of clusters
* @return a vector of centroids
*/
std::vector<Point> random_initializer (const std::vector<Point>& points, const int& k){
    double tstart, tstop;
    tstart = omp_get_wtime();

    std::vector<Point> centroids;
    std::random_device rand_dev;       // Used to obtain a seed for the standard Mersenne Twister 19937 generator
    std::mt19937 gen(rand_dev());   // Standard mersenne_twister_engine seeded with rand_dev()
    std::uniform_int_distribution<> distrib(0, points.size());
    int i = 0;

    while(centroids.size()<k){
        Point new_centroid = points[distrib(gen)];
        if(!contatins(centroids, new_centroid)){
            new_centroid.cluster=i;
            i++;
            centroids.push_back(new_centroid);

        }
    }
    tstop = omp_get_wtime();
    printf("Random Initialization execution time: %f\n", tstop - tstart);

    return centroids;
}

/*
* This function initializes centroids by choosing the farthest points from each other
* @param points: the vector of points
* @param k: the number of clusters
* @return a vector of centroids
*/
std::vector<Point> kmeanpp_initializer (const std::vector<Point>& data, int& k) {
    double tstart, tstop;
    tstart = omp_get_wtime();

    std::random_device rd;       
    std::mt19937 gen(rd());   
    std::uniform_int_distribution<> distrib(0, data.size());

    std::vector<Point> centroids;
    Point starting_point = data[distrib(gen)];
    starting_point.cluster = 0;
    centroids.push_back(starting_point);

    for (int i=1; i<k; i++) {
        double max_dist = 0.;
        Point next_point;
        // find the farthest point from its closest centroid
        double partial_max_dist[omp_get_max_threads()];
        for (double& el:partial_max_dist)
            el = 0.;
        Point partial_next_point[omp_get_max_threads()];
#pragma omp parallel for num_threads(omp_get_max_threads()) default(none) shared(partial_max_dist, partial_next_point) firstprivate(centroids, data) schedule(static, 64)
        for (const Point& el:data) {
            double min_dist = DBL_MAX;
            for (const Point& c:centroids) {
                double d = el.compute_distance(c);
                if (d < min_dist)
                    min_dist = d;
            }
            if (min_dist > partial_max_dist[omp_get_thread_num()]){
                partial_max_dist[omp_get_thread_num()] = min_dist;
                partial_next_point[omp_get_thread_num()] = el;
            }
        }

        for (int j=0; j<omp_get_max_threads(); j++){
            if (partial_max_dist[j] > max_dist){
                max_dist = partial_max_dist[j];
                next_point = partial_next_point[j];
            }
        }
        next_point.cluster = i;
        centroids.push_back(next_point);
    }
    tstop = omp_get_wtime();
    printf("KMean++ Initialization execution time: %f\n", tstop - tstart);

    return centroids;
}






