#include "common_utils.cpp"

//Le tri est fait en place, la rapidité du tri rapide
//venant justement du fait qu'il soit en place
void recursiveQuickSort(Array& toSort, unsigned lower, unsigned upper)
{
    if (upper - lower < 2) return;

    int pivot = toSort[lower];
    unsigned posPivot = lower;

    for (unsigned i = lower+1; i < upper; ++i) {
        if (toSort[i] < pivot) {
            toSort[posPivot] = toSort[i];
            ++posPivot;
            toSort[i] = toSort[posPivot];
            toSort[posPivot] = pivot;
        }
    }

    recursiveQuickSort(toSort, lower, posPivot);
    recursiveQuickSort(toSort, posPivot+1, upper);
}

void quickSort(Array& toSort){
	recursiveQuickSort(toSort, 0, toSort.size());
}


int main()
{
    Array toSort(30, 0);
    fillRandom(toSort);
    printArray(toSort);

    quickSort(toSort);
    printArray(toSort);
    if (isSorted(toSort)) {
        std::cout << "C'est bien trié !\n";
    } else {
        std::cout << "C'est pas trié !\n";
    }

    return 0;
}
