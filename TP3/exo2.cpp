#include <cstddef>
#include <algorithm>

#include "common_utils.cpp"

using std::size_t;
/**

 * @param array array of int to process
 * @param toSearch value to find
 * @param indexMin first index of the value to find
 * @param indexMax last index of the value to find
 */
void binarySearchAll(Array& array, int toSearch, int& indexMin, int& indexMax)
{
	// do not use increments, use two different binary search loop
    indexMin = indexMax = -1;

    size_t begin(0), end(array.size()), mid(array.size()/2);
    while (array[mid] != toSearch || (mid > 0 && array[mid-1] >= toSearch)) {
        if (array[mid] < toSearch) {
            begin = mid+1;
        } else {
            end = mid;
        }

        if (begin>end) return;
        mid = (begin+end)/2;
    }
    indexMin = mid;

    begin = indexMin;
    end = array.size();
    mid = (begin+end)/2;
    while (array[mid] != toSearch || (mid < array.size()-1 && array[mid+1] <= toSearch)) {
        if (array[mid] > toSearch) {
            end = mid;
        } else {
            begin = mid+1;
        }
        //ici on sait que l'on va trouver puisque l'on a trouvé pour la valeur inférieure
        mid = (begin+end)/2;
    }
    indexMax = mid;
}

int main()
{
    Array array(20, 0);
    fillRandom(array);
    std::sort(array.begin(), array.end());

    size_t randomIndex = dis(generator)%(array.size()/2);
    size_t randomLength = dis(generator)%(array.size()/2-1);

    for (unsigned i = randomIndex; i < randomIndex+randomLength; ++i) {
        array[i] = array[randomIndex];
    }

    int minI, maxI;
    printArray(array);

    binarySearchAll(array, array[randomIndex], minI, maxI);

    std::cout
        << array[randomIndex]
        << " can be found from : "
        << minI << " to " << maxI << "\n";

    return 0;
}
