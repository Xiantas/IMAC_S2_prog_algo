#include "common_utils.cpp"

//Le tri par insertion est fait en place
void insertionSort(Array& toSort){
    for (unsigned i = 1; i < toSort.size(); ++i) {
        unsigned j=0;
        int value = toSort[i];
        for (; toSort[j] < value; ++j) {}
        for (unsigned k = i; k > j; --k) {
            toSort[k] = toSort[k-1];
        }
        toSort[j] = value;
    }
}

int main()
{
    Array toSort(10, 0);
    fillRandom(toSort);
    printArray(toSort);

    insertionSort(toSort);
    printArray(toSort);
    if (isSorted(toSort)) {
        std::cout << "C'est bien trié !\n";
    } else {
        std::cout << "C'est pas trié !\n";
    }

    return 0;
}
