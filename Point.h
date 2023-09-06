//
// Created by dragos on 28/10/22.
//
#pragma once
#ifndef KMEANS_POINT_H
#define KMEANS_POINT_H

#include<cfloat>
#include<fstream>
#include<cstring>
#include<sstream>
#include<vector>
#include<iostream>
#include<omp.h>
#include<immintrin.h>

#define DIM 3

struct Point{

    double coordinates[DIM];
    int cluster;

    Point(){
        to_zero(-1);
    }

    void to_zero(int i){
        for(double coordinate : coordinates){
            coordinate = 0;
        }
        cluster = i;
    }

    bool operator==(const Point& p) const {
        for (int i=0; i<DIM; i++)
            if (this->coordinates[i] != p.coordinates[i])
                return false;
        return true;
    }

    void operator+=(const Point& p){
        for (int i=0; i<DIM; i++)
            this->coordinates[i] += p.coordinates[i];
    }

    void operator/=(const int& cardinality){
        for (double & coordinate : coordinates)
            coordinate /= (double)cardinality;
    }

    void print(Point& p){
        for (double d: p.coordinates){
            std::cout<<d<<" ";
        }
        std::cout<<p.cluster;
        std::cout<<std::endl;
    }

};

/*
* This function computes the euclidean distance between two points
* @param p1: the first point
* @param p2: the second point
* @return the euclidean distance between the two points
*/
double euclidean_dist(const Point& p1, const Point& p2){
    double distance= 0;
    #pragma omp simd 
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


#endif //KMEANS_POINT_H
