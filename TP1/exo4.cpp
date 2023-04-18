#include <vector>
#include <iostream>

void allEvens(std::vector<int>& evens, std::vector<int>& array, int evensSize, int arraySize)
{
    for (int i = 0; i < arraySize; i++) {
        if (array[i] % 2 == 0) {
            evens.push_back(array[i]);
            evensSize++;
        }
    }
}

void recursiveAllEvens(std::vector<int>& evens, std::vector<int>& array, int evensSize, int arraySize) {
    if (arraySize <= 0) return;

    if (array[arraySize-1]) {
        evens.push_back(array[arraySize-1]);
        evensSize++;
    }

    return recursiveAllEvens(evens, array, evensSize, arraySize);
}

void printVectorInt(std::vector<int> &vec) {
    std::cout << '{';
    for (unsigned long i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << "}\n";
}

int main(int argc, char *argv[])
{
    std::vector<int> v = {19, 9, 8, 43, 34, 8, 2, 7, 8, 9, 1, 37};
    std::vector<int> evens;
    
    allEvens(evens, v, 0, v.size());
    printVectorInt(evens);

    evens.clear();

    recursiveAllEvens(evens, v, 0, v.size());
    printVectorInt(evens);

    return 0;
}




