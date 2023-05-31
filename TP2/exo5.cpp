#include "common_utils.cpp"

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin) {
	// stop statement = condition + return (return stop the function even if it does not return anything)
    if (origin.size() < 2) return;

	// initialisation
	Array first(origin.size()/2, 0);
	Array second(origin.size()-first.size(), 0);

	// split
    for (unsigned i = 0; i < first.size(); ++i) {
        first[i] = origin[i];
    }
    for (unsigned i = 0; i < second.size(); ++i) {
        second[i] = origin[i+first.size()];
    }

	// recursiv splitAndMerge of lowerArray and greaterArray

    splitAndMerge(first);
    splitAndMerge(second);


	// merge
    merge(first, second, origin);
}

void merge(Array& first, Array& second, Array& result) {
    unsigned iF(0), iS(0);
    for (unsigned i = 0; i < result.size(); ++i) {
        result[i] =
            iF < first.size() && (iS >= second.size() || first[iF] <= second[iS]) ?
            first[iF++] :
            second[iS++];
    }
}

void mergeSort(Array& toSort) {
    splitAndMerge(toSort);
}

int main() {
    Array toSort(10, 0);
    fillRandom(toSort);
    printArray(toSort);

    mergeSort(toSort);
    printArray(toSort);
    if (isSorted(toSort)) {
        std::cout << "C'est bien trié !\n";
    } else {
        std::cout << "C'est pas trié !\n";
    }

    return 0;
}
