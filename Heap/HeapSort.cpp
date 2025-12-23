#include <iostream>
#include <vector>
using namespace std;

void max_heapify(vector<int>& heap, int idx) {
    int heap_size = static_cast<int>(heap.size());
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int largest = idx;
    if (left < heap_size && heap[left] > heap[idx])
        largest = left;
    if (right < heap_size && heap[right] > heap[largest])
        largest = right;
    if (largest != idx) {
        swap(heap[largest], heap[idx]);
        max_heapify(heap, largest);
    }
}

void build_max_heap(vector<int>& heap) {
    int heap_size = static_cast<int>(heap.size());
    for (int i = (heap_size - 1) / 2; i >= 0; i--) {
        max_heapify(heap, i);
    }
}

// wrong
void heapSort(vector<int>& heap) {
    int heapSize = static_cast<int>(heap.size());
    build_max_heap(heap);
    for (int i = heapSize - 1; i > 0; i--) {
        swap(heap[i], heap[0]);
        heapSize--;
        max_heapify(heap, 0);
    }
}

int main() {

}