#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class Heap {
private:
    vector<int> heap;
    int parent(int i) const;
    void maxHeapify(int i);
public:
    Heap() = default;
    void insert(int key);
    int extractMax();
    int getMax() const;
    void deleteKey(int i);
    void increaseKey(int i, int newValue);
    void buildMaxHeap();
    void heapSort();
    void printHeap() const;
};


int main() {

}

int Heap::parent(int i) const {
    return (i - 1) / 2;
}

void Heap::maxHeapify(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int heapSize = static_cast<int>(heap.size());
    if (left < heapSize && heap[left] > heap[i]) {
        largest = left;
    }
    if (right < heapSize && heap[right] > heap[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(heap[i], heap[largest]);
        maxHeapify(largest);
    }
}

void Heap::insert(int key) {
    heap.push_back(key);
    int i = static_cast<int>(heap.size()) - 1;
    while (i != 0 && heap[i] > heap[parent(i)]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

int Heap::extractMax() {
    if (heap.empty()) {
        throw underflow_error("Heap Underflow\n");
    }
    int maxValue = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    maxHeapify(0);
    return maxValue;
}

int Heap::getMax() const {
    if (heap.empty()) {
        throw underflow_error("Heap Underflow");
    }
    return heap.front();
}

void Heap::deleteKey(int i) {
    if (i >= static_cast<int>(heap.size())) {
        throw out_of_range("Invalid Index");
    }
    heap[i] = heap.back();
    heap.pop_back();
    maxHeapify(i);
}

void Heap::increaseKey(int i, int newValue) {
    if (i >= static_cast<int>(heap.size()) || heap[i] >= newValue) {
        throw invalid_argument("Invalid Index or New Value is not greater");
    }
    heap[i] = newValue;
    while (i != 0 && heap[i] > heap[parent(i)]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void Heap::printHeap() const {
    for (int x : heap)
        cout << x << " ";
    cout << endl;
}

void Heap::heapSort() {
    int heapSize = static_cast<int>(heap.size());
    buildMaxHeap();
    for (int i = heapSize - 1; i > 0; i--) {
        swap(heap[i], heap[0]);
        heapSize--;
        maxHeapify(0);
    }
}

void Heap::buildMaxHeap() {
    int heap_size = static_cast<int>(heap.size());
    for (int i = (heap_size - 1) / 2; i >= 0; i--) {
        maxHeapify(i);
    }
}