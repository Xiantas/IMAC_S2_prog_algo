#pragma once

#include<vector>
#include<random>

#include<iostream>

typedef std::vector<int> Array;

std::random_device rd{};
std::mt19937 generator{rd()};
std::uniform_int_distribution<int> dis{1, 1000};

void fillRandom(Array& array) {
    for (unsigned i = 0; i < array.size(); ++i) {
        array[i] = dis(generator);
    }
}

void fill(Array& array, int val) {
    for (unsigned i = 0; i < array.size(); ++i) {
        array[i] = val;
    }
}

bool isSorted(Array& array) {
    for (unsigned i = 0; i < array.size()-1; ++i) {
        if (array[i] > array[i+1]) {
            return false;
        }
    }

    return true;
}

void printArray(Array& array) {
    std::cout << "[";
    for (unsigned i = 0; i < array.size(); ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << "]\n";
}
