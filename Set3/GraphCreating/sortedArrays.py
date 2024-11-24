import pandas as pd
import matplotlib.pyplot as plt
sortedArrays = pd.read_csv("D:/A3_Statistics/sortedArrays_statistics.csv")
sortedArraysHybrid = pd.read_csv("D:/A3_Statistics/sortedArraysHybrid_statistics.csv")
x1, y1 = sortedArrays['ArrayAmount'], sortedArrays['Time(microseconds)']
x2, y2 = sortedArraysHybrid['ArrayAmount'], sortedArraysHybrid['Time(microseconds)']
plt.figure(figsize=(14, 8))
plt.plot(x1, y1, label="quickSort", color="blue", marker='o')
plt.plot(x2, y2, label="quickSort + heap + insertionSort", color="orange", marker='o')
plt.xlabel("Количество элементов в массиве")
plt.ylabel("Время сортировки")
plt.title("Отсортирован в обратном порядке")
plt.legend()
plt.grid()
plt.show()



