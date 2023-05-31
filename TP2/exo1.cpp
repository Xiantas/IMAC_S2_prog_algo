#include "common_utils.cpp"
#include <utility>

void selectionSort(Array& toSort){
	for (unsigned i = 0; i < toSort.size(); ++i) {
        int minIndex = i;
        for (unsigned j = i+1; j < toSort.size(); ++j) {
            if (toSort[j] < toSort[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(toSort[minIndex], toSort[i]);
    }
}

int main()
{
    Array toSort(10, 0);
    fillRandom(toSort);
    printArray(toSort);

    selectionSort(toSort);
    printArray(toSort);
    if (isSorted(toSort)) {
        std::cout << "C'est bien trié !\n";
    } else {
        std::cout << "C'est pas trié !\n";
    }

    return 0;
}
