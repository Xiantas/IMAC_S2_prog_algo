#include <utility>

#include <iostream>

using std::size_t;
using std::string;
#include "../lib/HuffmanNode.h"
#include "../lib/heap.h"

Heap::Heap(uint size) : Array(size, 0) {}

int Heap::leftChildIndex(int nodeIndex)
{
    return 2*nodeIndex+1;
}

int Heap::rightChildIndex(int nodeIndex)
{
    return 2*nodeIndex+2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
	int i = heapSize;

    (*this)[i] = value;

    while (i>0 && (*this)[i] > (*this)[(i-1)/2]) {
        std::swap((*this)[i], (*this)[(i-1)/2]);
        i = (i-1)/2;
    }
}

void Heap::heapify(int heapSize, int nodeIndex)
{
	int i_max = nodeIndex;
    int childIndex = this->leftChildIndex(nodeIndex);
    if (childIndex < heapSize && (*this)[i_max] < (*this)[childIndex]) {
        i_max = childIndex;
    }
    childIndex = this->rightChildIndex(nodeIndex);
    if (childIndex < heapSize && (*this)[i_max]< (*this)[childIndex]) {
        i_max = childIndex;
    }

    if (i_max != nodeIndex) {
        std::swap((*this)[i_max], (*this)[nodeIndex]);
        this->heapify(heapSize, i_max);
    }

}

void Heap::buildHeap(Array& numbers)
{
    for (unsigned i = 0; i < numbers.size(); ++i) {
        this->insertHeapNode(i, numbers[i]);
    }
}

void Heap::heapSort()
{
    for(int i = this->size(); i >= 0; --i) {
        std::swap((*this)[0], (*this)[i]);
        this->heapify(i, 0);
    }
}

void printHeap(Heap& heap, int heapSize) {
    std::cout << "[";
    for (int i = 0; i < heapSize; ++i) {
        std::cout << heap[i] << ", ";
    }
    std::cout << "]\n";
}

int main()
{
    Array array(15, 0);
    fillRandom(array);
    printArray(array);

    Heap heap(array.size());
    heap.buildHeap(array);
    printHeap(heap, array.size());

    heap.heapSort();
    printHeap(heap, array.size());

    return 0;
}
