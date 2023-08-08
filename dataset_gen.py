from sklearn.datasets import make_blobs
import numpy as np
import matplotlib.pyplot as plt
import sys

def plot_data(X):
    if X.shape[1] > 4:
        print("More than 3 dimensions, can't plot")
        return
    if X.shape[1] == 4:
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.scatter(X[:,0], X[:,1], X[:,2], c=X[:,3])
        plt.show()
        return
    if X.shape[1] == 3:
        fig, ax = plt.subplots()
        ax.scatter(X[:,0], X[:,1], c=X[:,2])
        plt.show()
        
def main():
    print("choose mode: ")
    print("1. generate data and output to file")
    print("2. read data from file and plot")
    print(" ")
    
    mode = int(input())
    if mode == 1:
        num_samples = int(input("Enter number of samples: "))
        dimensions = int(input("Enter number of dimensions: "))
        num_clusters = int(input("Enter number of clusters: "))
        X, _ = make_blobs(n_samples=num_samples, n_features=dimensions, centers=num_clusters, center_box=(-10.0, 10.0), cluster_std=2, shuffle=True)
        file_name = ("{num_samples}_{dimensions}_{num_clusters}.csv".format(num_samples=num_samples, dimensions=dimensions, num_clusters=num_clusters))  
        print("Saving to file: ", file_name, " ...")
        np.savetxt(file_name, X, delimiter=",")    
    
    if mode == 2:
        #filename = input("Enter filename: ")
        X = np.loadtxt("output.csv", delimiter=",")
        plot_data(X)
        
main()
   
