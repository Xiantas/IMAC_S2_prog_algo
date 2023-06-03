#include "common_utils.cpp"

#include <algorithm>
#include <cstddef>

int binarySearch(Array& array, int toSearch)
{
    size_t begin(0), end(array.size());

    while (begin<end) {
        size_t mid = (begin+end)/2;

        if (array[mid] > toSearch) {
            end = mid;
        } else if (array[mid] < toSearch) {
            begin = mid+1;
        } else {
            return mid;
        }
    }
	return -1;
}

int main()
{
    Array array(10, 0);
    fillRandom(array);
    std::sort(array.begin(), array.end());

    size_t randomIndex = dis(generator)%array.size();

    printArray(array);
    std::cout
        << array[randomIndex]
        << " can be found at pos : "
        << binarySearch(array, array[randomIndex]) << "\n";

    return 0;
}
