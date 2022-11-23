
#include "kmeans.cpp"
#include "dataLoader.cpp"

int main(int argc, const char *argv[]){

    std::string file_name = argv[1];
    int clusters = atoi(argv[2]);
    int epochs = 10;
    std::vector<Point> points = load_csv(file_name);

    std::cout<<" "<<std::endl;
    std::vector<Point> centroids = random_initializer(points, 5);

    centroids = kmean (points, centroids, epochs, clusters);

    std::cout<<" "<<std::endl;

    output_results(points);


}