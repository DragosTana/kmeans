//
// Created by dragos on 31/10/22.
//

#include "Point.h"
#include <time.h>
#include<immintrin.h>

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
        //std::cout<<"file is opened"<<std::endl;
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

/*
* This function returns the current time in nanoseconds
* @return the current time in nanoseconds
*/
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

/*
* This function computes the euclidean distance between two points using avx2 instructions
* @param p1: the first point
* @param p2: the second point
* @return the euclidean distance between the two points
*/
double simd_euclidean_dist(const Point& p1, const Point& p2){
    double distance = 0;
    __m256d p1_vec = _mm256_loadu_pd(p1.coordinates);
    __m256d p2_vec = _mm256_loadu_pd(p2.coordinates);
    __m256d diff = _mm256_sub_pd(p1_vec, p2_vec);
    __m256d square = _mm256_mul_pd(diff, diff);
    double* square_arr = (double*)&square;
    distance = square_arr[0] + square_arr[1] + square_arr[2] + square_arr[3];
    return distance;
}


