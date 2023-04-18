#include <vector>
#include <iostream>

template<typename T>
int search(T value, std::vector<T> &data, int size)
{
    for (int i = 0; i < size; i++) {
        if (data[i] == value) {
            return i;
        }
    }

    return -1;
}

template<typename T>
int recursiveSearch(T value, std::vector<T> &data, int size) {
    if (size == 0) return -1;
    if (data[size-1] == value) return size-1;

    return recursiveSearch(value, data, size-1);
}

int main(int argc, char *argv[])
{
    std::vector<int> v = {78, 17, 9, 7, 6, 90, 98, 38, 1, 37, 4};
    std::cout << search(7, v, v.size()) << '\n';
    std::cout << recursiveSearch(7, v, v.size()) << '\n';
    return 0;
}
