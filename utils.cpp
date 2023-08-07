//
// Created by dragos on 31/10/22.
//

#include "Point.h"
#include <time.h>

/*
* This function loads the data from a csv file
* @param file_name: the name of the file to be loaded
* @return a vector of points
*/
std::vector<Point> load_csv (const std::string& file_name){

    std::vector<Point> points;
    std::ifstream file;
    file.open(file_name, std::ios::in);
    std::string line, word;

    if(file.is_open()){
        std::cout<<"file is opened"<<std::endl;
        while(getline(file, line)){
            std::stringstream str(line);
            Point p;
            int i = 0;
            while(getline(str, word, ',')){
                    p.coordinates[i] = std::stod(word);
                    i++;
            }
            p.cluster = -1;
            points.push_back(p);
        }
    }
    else std::cout<<"ERROR: couldn't open file"<<std::endl;

    return points;
}

/*
* This function outputs the results to a csv file
* @param points: the vector of points to be written
* @return void
*/
void output_results (std::vector<Point>& points){
    std::fstream output;
    output.open("output.csv", std::ios::out);
    if(output.is_open()){
        for(Point p: points){
            for (int i = 0; i < DIM; i++){
                output<<p.coordinates[i]<<",";
            }
            output<<p.cluster;
            output<<std::endl;
        }
    }
}


uint64_t nanos(){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000 + ts.tv_nsec;
}

/*
* This function computes the euclidean distance between two points
* @param p1: the first point
* @param p2: the second point
* @return the euclidean distance between the two points
*/
double euclidean_dist(const Point& p1, const Point& p2){
    double distance= 0;
    for (int i=0; i<DIM; i++)
        distance += (p1.coordinates[i] - p2.coordinates[i]) * (p1.coordinates[i] - p2.coordinates[i]);
    return distance;
}