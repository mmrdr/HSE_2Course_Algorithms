#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <cmath>
#include "A3/A3i.cpp"
using namespace std;

class ArrayGenerator {
public:
    ArrayGenerator() {
        randomArrays.resize(ARRAY_AMOUNT);
        sortedArrays.resize(ARRAY_AMOUNT);
        semiSortedArrays.resize(ARRAY_AMOUNT);
        fillArrays();
    }

    vector<int> generateRandomArray(int arraySize) {
        random_device rand_dev;
        mt19937 generator(rand_dev());
        uniform_int_distribution<> distr(1, 6000);

        vector<int> array(arraySize);
        for (int i = 0; i < arraySize; ++i) {
            array[i] = distr(generator);
        }
        return array;
    }

    vector<int> generateSortedArray(int arraySize) {
        vector<int> array(arraySize);
        array = generateRandomArray(arraySize);
        sort(array.begin(), array.end(), greater<int>());
        return array;
    }

    vector<int> generateSemiSortedArray(int arraySize) {
        random_device rand_dev;
        mt19937 generator(rand_dev());
        uniform_int_distribution<> distr(1, 6000);

        vector<int> array(arraySize);
        array = generateRandomArray(arraySize);
        sort(array.begin(), array.end());
        for (int i = 0; i < 20; ++i) {
            swap(array[distr(generator) % arraySize], array[distr(generator)% arraySize]);
        }
        return array;
    }

    void fillArrays() {
        int ind = 0;
        for (int size = 500; size <= 10000; size += 100) {
            randomArrays[ind] = generateRandomArray(size);
            sortedArrays[ind] = generateSortedArray(size);
            semiSortedArrays[ind] = generateSemiSortedArray(size);
            ++ind;
        }
    }

    vector<vector<int>> getRandomArrays() {
        return randomArrays;
    }

    vector<vector<int>> getSortedArrays() {
        return sortedArrays;
    }

    vector<vector<int>> getSemiSortedArrays() {
        return semiSortedArrays;
    }

private:
    const int ARRAY_AMOUNT = 96;
    vector<vector<int>> randomArrays;
    vector<vector<int>> sortedArrays;
    vector<vector<int>> semiSortedArrays;
};

class SortTester {
public:
    long long Test(vector<int> array) {
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(array, 0, static_cast<int>(array.size()) - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }
    long long TestHybrid(vector<int> array, int limit) {
        auto start = std::chrono::high_resolution_clock::now();
        quickSortHybrid(array, 0, static_cast<int>(array.size()) - 1, limit);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }
};

void createFile(vector<vector<int>>& array, const string& path, SortTester tester, const string& mode) {
    ofstream outputFile(path);
    outputFile << "ArrayAmount,Time(microseconds)\n";
    for (const auto & el : array) {
        long long t = 0;
        int cnt = 10;
        int limit = 2 * log2(el.size());
        for (int i = 0; i < 10; ++i) {
            if (mode == "quickSort") {
                t += tester.Test(el);
            } else if (mode == "quickSortHybrid") {
                t += tester.TestHybrid(el, limit);
            }
        }
        long long avgTime = t / cnt;
        outputFile << el.size() << "," << avgTime << "\n";
    }
    outputFile.close();
}


int main() {
    string dirPath = "D:/A3_Statistics";
    if (!filesystem::exists(dirPath)) {
        filesystem::create_directory(dirPath);
    }
    string filePathToRandom = dirPath + "/randomArrays_statistics.csv";
    string filePathToRandomHybrid = dirPath + "/randomArraysHybrid_statistics.csv";

    string filePathToSorted = dirPath + "/sortedArrays_statistics.csv";
    string filePathToSortedHybrid= dirPath + "/sortedArraysHybrid_statistics.csv";

    string filePathToSemiSorted = dirPath + "/semiSortedArrays_statistics.csv";
    string filePathToSemiSortedHybrid = dirPath + "/semiSortedArraysHybrid_statistics.csv";



    ArrayGenerator arrayGenerator = ArrayGenerator();

    auto randomArrays = arrayGenerator.getRandomArrays();
    auto sortedArrays = arrayGenerator.getSortedArrays();
    auto semiSortedArrays = arrayGenerator.getSemiSortedArrays();

    SortTester tester = SortTester();

    createFile(randomArrays, filePathToRandom, tester, "quickSort");
    createFile(randomArrays, filePathToRandomHybrid, tester, "quickSortHybrid");
    createFile(sortedArrays, filePathToSorted, tester, "quickSort");
    createFile(sortedArrays, filePathToSortedHybrid, tester, "quickSortHybrid");
    createFile(semiSortedArrays, filePathToSemiSorted, tester, "quickSort");
    createFile(semiSortedArrays, filePathToSemiSortedHybrid, tester, "quickSortHybrid");
}
