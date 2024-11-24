import pandas as pd
import matplotlib.pyplot as plt
randomArrays = pd.read_csv("D:/A3_Statistics/randomArrays_statistics.csv")
randomArraysHybrid = pd.read_csv("D:/A3_Statistics/randomArraysHybrid_statistics.csv")
x1, y1 = randomArrays['ArrayAmount'], randomArrays['Time(microseconds)']
x2, y2 = randomArraysHybrid['ArrayAmount'], randomArraysHybrid['Time(microseconds)']
plt.figure(figsize=(14, 8))
plt.plot(x1, y1, label="quickSort", color="blue", marker='o')
plt.plot(x2, y2, label="quickSort + heap + insertionSort", color="orange", marker='o')
plt.xlabel("Количество элементов в массиве")
plt.ylabel("Время сортировки")
plt.title("Рандомный массив")
plt.legend()
plt.grid()
plt.show()
