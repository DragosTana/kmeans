
#include "kmeans.cpp"
#include "initializer.cpp"

int main(int argc, const char *argv[]){
    
    std::string file_name = argv[1];
    int clusters = atoi(argv[2]);
    int threads = atoi(argv[3]);
    std::string algorithm = argv[4];
    int epochs = 1000;
    double dtime;
    std::vector<Point> points = load_csv(file_name);
    
    for (int i = 0; i < 1; i++){
        dtime = omp_get_wtime();
        std::vector<Point> centroids = kmeanpp_initializer(points, clusters);
        centroids = kmean_par (points, centroids, epochs, clusters, threads);
        dtime = omp_get_wtime() - dtime;
        std::cout<<"Time elapsed: "<<dtime<<std::endl;
    }
    output_results(points);
}