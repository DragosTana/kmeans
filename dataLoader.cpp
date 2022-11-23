//
// Created by dragos on 31/10/22.
//


#include "Point.h"



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

void output_results (std::vector<Point>& points){
    std::fstream output;
    output.open("output.txt", std::ios::out);
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