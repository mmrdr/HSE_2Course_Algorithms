import pandas as pd
import matplotlib.pyplot as plt
semiSortedArrays = pd.read_csv("D:/A3_Statistics/semiSortedArrays_statistics.csv")
semiSortedArraysHybrid = pd.read_csv("D:/A3_Statistics/semiSortedArraysHybrid_statistics.csv")
x1, y1 = semiSortedArrays['ArrayAmount'], semiSortedArrays['Time(microseconds)']
x2, y2 = semiSortedArraysHybrid['ArrayAmount'], semiSortedArraysHybrid['Time(microseconds)']
plt.figure(figsize=(14, 8))
plt.plot(x1, y1, label="quickSort", color="blue", marker='o')
plt.plot(x2, y2, label="quickSort + heap + insertionSort", color="orange", marker='o')
plt.xlabel("Количество элементов в массиве")
plt.ylabel("Время сортировки")
plt.title("Почти отсортирован")
plt.legend()
plt.grid()
plt.show()
