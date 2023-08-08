# KMeans

This repository contains an implementation of KMeans algorithm for clusterization. The algorithm is parallelized using OpenMP directives. 

## How to use

To compile run <code>g++ main.cpp -o kmean -fopenmp</code>

To run use <code> ./kmean <dataset_file_name> <number_of_clusters> <thread_number> <algorithm_type> </code>

- <code><dataset_file_name></code> path of the dataset as a csv file
- <code><number_of_clusters></code> number of clusters
- <code><thread_number></code> number of thread to be used
- <code> <algorithm_type></code>  can be: _seq_ or _par_ for sequential and parallel version respectively

The dataset_gen.py module allows the user to create custom datasets and visualize the result of the kmeans algorithm. To use run <code> python3 dataset_gen.py</code> and follow the instructions.