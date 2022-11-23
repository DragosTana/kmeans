//
// Created by dragos on 31/10/22.
//

#include "initializer.cpp"

std::vector<Point> kmean (std::vector<Point>& points, std::vector<Point>& centroids, int& epochs, int& k  ){
    std::vector<Point> new_centroids = std::vector<Point>(k);
    int cluster_cardinality[k];

    for(int i = 0; i < epochs; i++){
        std::cout<<"Iteration "<< i <<": "<<i*100/epochs<<"%"<<std::endl;
        //std::cout << "Press Enter to continue ...";
        //std::cin.get();
        //set new centroids to zero and cardinality to zero
        for(int i = 0; i < k; i++){
            new_centroids[i].to_zero(-1);
            cluster_cardinality[i] = 0;
        }
        //begin iterating through points
        for (Point& p: points){
            double distance = DBL_MAX;
            for(int i = 0; i < centroids.size(); i++){
                if (p.compute_distance(centroids[i]) < distance) {
                    distance = p.compute_distance(centroids[i]);
                    p.cluster = i;
                }
            }
            //std::cout<<p.cluster<<std::endl;
            new_centroids[p.cluster] += p;
            cluster_cardinality[p.cluster]++;
        }
        for(int i = 0; i < k; i++){
            new_centroids[i] /= cluster_cardinality[i];
        }
        centroids = new_centroids;

    }
    return centroids;
}