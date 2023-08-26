
import subprocess
import numpy as np
import matplotlib.pyplot as plt

threads_num = [1, 2, 4, 8, 16]
point_num = [1000, 5000, 10000, 50000, 100000]
output = []
result = np.zeros((len(point_num), len(threads_num)))
speedup = np.zeros((len(point_num), len(threads_num)))

executable_path = "./kmean"

for p in point_num:
    for t in threads_num:
        print("Point number: {}, Thread number: {}".format(p, t))
    
        for i in range(20):
            args = [executable_path, "{}_3_10.csv".format(p), "10", str(t), "rand"]
            completed_process = subprocess.run(args, stdout=subprocess.PIPE, text=True)
            output.append(float(completed_process.stdout))

        result[point_num.index(p)][threads_num.index(t)] = np.mean(output)
        output.clear()
        
for i in range(len(point_num)):
    for j in range(len(threads_num)):
        speedup[i][j] = result[i][0] / result[i][j]
        
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
    
    

        




