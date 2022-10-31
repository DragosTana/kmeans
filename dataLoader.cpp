//
// Created by dragos on 31/10/22.
//


#include "Point.h"
#include<fstream>
#include<string.h>
#include<sstream>
#include<vector>
#include<iostream>


std::vector<Point> load_csv (std::string file_name){

    std::vector<Point> points;
    std::ifstream file;
    file.open(file_name, std::ios::in);
    std::string line, word;

    if(file.is_open()){
        std::cout<<"file is opened"<<std::endl;
        while(getline(file, line)){
            std::stringstream str(line);
            Point point;
            int i = 0;
            while(getline(str, word, ',')){
                if(i == 0){
                    point.x = std::stod(word);
                    i++;
                }
                else point.y = std::stod(word);
            }
            points.push_back(point);
        }
    }
    else std::cout<<"ERROR: couldn't open file"<<std::endl;

    return points;
}
