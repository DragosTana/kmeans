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

    double compute_distance(const Point& p) const {
        double total_d = 0;
        for (int i=0; i<DIM; i++)
            total_d += (this->coordinates[i] - p.coordinates[i]) * (this->coordinates[i] - p.coordinates[i]);
        return total_d;
    }

};

#endif //KMEANS_POINT_H
