
import subprocess
import numpy as np
import matplotlib.pyplot as plt

def speedUp():
    threads_num = [1, 2, 4, 8, 16]
    points_num = [1000, 5000, 10000, 50000, 100000]
    output = []
    cluster_num = 10
    result = np.zeros((len(points_num), len(threads_num)))
    speedup = np.zeros((len(points_num), len(threads_num)))

    executable_path = "./kmean"

    for p in points_num:
        for t in threads_num:
            print("points number: {}, thread number: {}".format(p, t))

            for i in range(15):
                args = [executable_path, "{}_3_10.csv".format(p), str(cluster_num), str(t), "rand"]
                completed_process = subprocess.run(args, stdout=subprocess.PIPE, text=True)
                output.append(float(completed_process.stdout))

            result[points_num.index(p)][threads_num.index(t)] = np.mean(output)
            output.clear()
            

    for i in range(len(points_num)):
        for j in range(len(threads_num)):
            speedup[i][j] = result[i][0] / result[i][j]

    print(result)
    print(" ")
    print(speedup)        

    plt.figure(figsize=(10, 5))
    plt.title("Speedup vs. Thread Number")
    plt.xlabel("Thread Number")
    plt.ylabel("Speedup")
    plt.grid()
    plt.plot(threads_num, speedup[0], label="1000 points")
    plt.plot(threads_num, speedup[1], label="5000 points")
    plt.plot(threads_num, speedup[2], label="10000 points")
    plt.plot(threads_num, speedup[3], label="50000 points")
    plt.plot(threads_num, speedup[4], label="100000 points")
    plt.legend()
    plt.show()


def dimension():
    threads_num = [1, 2, 4, 8, 16]
    output = []
    result = np.zeros(len(threads_num))
    speedUp = np.zeros(len(threads_num))
    
    executable_path = "./kmean"
    for t in threads_num:
        print("Thread number: {}".format(t))
        for i in range():
            args = [executable_path, "10000_2_10.csv", "10", str(t), "rand"]
            completed_process = subprocess.run(args, stdout=subprocess.PIPE, text=True)
            output.append(float(completed_process.stdout))

        result[threads_num.index(t)] = np.mean(output)
        output.clear()
    
    speedUp = result[0] / result
    print(result)
    print(speedUp)
    
def plotVec():
    threads_num = [1, 2, 4, 8, 16]
    time_vec = [0.62581563,  0.34127071,  0.18926259,  0.11452716, 0.09723407]
    time_novec =[ 0.1912791,  0.11501059, 0.07204265, 0.03816464, 0.02194771]
    
    thread_time = {
        "vec": time_vec,
        "novec": time_novec
    }
    
    x = np.arange(len(threads_num))  # the label locations
    width = 0.25  # the width of the bars
    multiplier = 0

    fig, ax = plt.subplots(layout="constrained")
    
    for attribute, value in thread_time.items():
        offset = width * multiplier
        rects = ax.bar(x + offset, value, width, label=attribute)
        ax.bar_label(rects, padding=3)
        multiplier += 1
        
    ax.set_ylabel('Time (s)')
    ax.set_xlabel('Thread Number')
    ax.set_title('Time vs. Thread Number')
    ax.set_xticks(x)
    ax.set_xticklabels(threads_num)
    ax.legend()
    fig.tight_layout()
    plt.show()
    
def plotSUdim():
    time_2dim =[0.03764761, 0.03167096, 0.01471248, 0.00529584, 0.0040635 ]
    time_3dim =[0.04012027, 0.03403523, 0.0185484,  0.00707393, 0.00755371]
    time_5dim =[0.05212167, 0.04291835, 0.02391985, 0.00899584, 0.00447646]
    time_10dim =[0.02961141, 0.03151315, 0.01744771, 0.0094115,  0.00621785]
    time_25dim =[0.07685037, 0.06377813, 0.04506304, 0.02641553, 0.02230031]
    time_50dim =[0.19125379 , 0.1251287,  0.0783167, 0.05420067,  0.04181928]
    
    time_2dim = np.array(time_2dim)
    time_3dim = np.array(time_3dim)
    time_5dim = np.array(time_5dim)
    time_10dim = np.array(time_10dim)
    time_25dim = np.array(time_25dim)
    time_50dim = np.array(time_50dim)
    
    speedUp_2dim = time_2dim[0] / time_2dim
    speedUp_3dim = time_3dim[0] / time_3dim
    speedUp_5dim = time_5dim[0] / time_5dim
    speedUp_10dim = time_10dim[0] / time_10dim
    speedUp_25dim = time_25dim[0] / time_25dim
    speedUp_50dim = time_50dim[0] / time_50dim
    
    threads_num = [1, 2, 4, 8, 16]
    
    plt.figure(figsize=(10, 5))
    plt.plot(threads_num, speedUp_2dim, label="2 dimensions")
    plt.plot(threads_num, speedUp_3dim, label="3 dimensions")
    plt.plot(threads_num, speedUp_5dim, label="5 dimensions")
    plt.plot(threads_num, speedUp_10dim, label="10 dimensions")
    plt.plot(threads_num, speedUp_25dim, label="25 dimensions")
    plt.plot(threads_num, speedUp_50dim, label="50 dimensions")
    plt.legend()
    plt.title("Speedup vs. Thread Number")
    plt.xlabel("Thread Number")
    plt.ylabel("Speedup")
    plt.grid()
    plt.show()
    
    
if __name__ == "__main__":
    speedUp()
