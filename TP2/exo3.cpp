#include "common_utils.cpp"
#include <utility>

void bubbleSort(Array& toSort) {
    for (unsigned i = 0; i < toSort.size(); ++i) {
        bool sorted = true;
        //Ici on n'itère pas jusqu'au bout, car on sait
        //que les plus grosses valeurs sont déjà remontées
        for (unsigned j = 1; j < toSort.size() - i; ++j) {
            if (toSort[j] < toSort[j-1]) {
                std::swap(toSort[j], toSort[j-1]);
                sorted = false;
            }
        }
    }
}


int main()
{
    Array toSort(10, 0);
    fillRandom(toSort);
    printArray(toSort);

    bubbleSort(toSort);
    printArray(toSort);
    if (isSorted(toSort)) {
        std::cout << "C'est bien trié !\n";
    } else {
        std::cout << "C'est pas trié !\n";
    }

    return 0;
}
