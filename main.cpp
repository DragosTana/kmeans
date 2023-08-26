
#include "kmeans.cpp"
#include "initializer.cpp"

// Compile with:
// g++ main.cpp -o kmean -fopenmp

int main(int argc, const char *argv[]) {
    
    std::string file_name = argv[1];
    int clusters = atoi(argv[2]);
    int threads = atoi(argv[3]);
    std::string algorithm = argv[4];
    int epochs = 100;
    double dtime;
    std::vector<Point> points = load_csv(file_name);
    

    if (algorithm == "rand"){
        dtime = omp_get_wtime();
        std::vector<Point> centroids = random_initializer(points, clusters);
        centroids = kmean_par (points, centroids, epochs, clusters, threads);
        dtime = omp_get_wtime() - dtime;
        std::cout<< dtime<<std::endl;
    }
    else if (algorithm == "pp"){
        dtime = omp_get_wtime();
        std::vector<Point> centroids = kmeanpp_initializer(points, clusters, threads);
        centroids = kmean_par (points, centroids, epochs, clusters, threads);
        dtime = omp_get_wtime() - dtime;
        std::cout<< dtime<<std::endl;
    }
    else{
        std::cout<<"Invalid algorithm"<<std::endl;
    }
    
    output_results(points);
}