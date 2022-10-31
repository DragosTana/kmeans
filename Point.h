//
// Created by dragos on 28/10/22.
//

#ifndef KMEANS_POINT_H
#define KMEANS_POINT_H

#include<float.h>


struct Point{

    double x, y;
    int cluster;
    double minDist;

    Point() :
        x(0.0),
        y(0.0),
        cluster(-1),
        minDist(__DBL_MAX__)
    {}

    Point(double x, double y) :
        x(x),
        y(y),
        cluster(-1),
        minDist(__DBL_MAX__)
    {}

    double distance(Point p){
        return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
    }
};

#endif //KMEANS_POINT_H
