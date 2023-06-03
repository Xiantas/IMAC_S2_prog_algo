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

void printArray(Array& array) {
    std::cout << "[";
    for (unsigned i = 0; i < array.size(); ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << "]\n";
}
