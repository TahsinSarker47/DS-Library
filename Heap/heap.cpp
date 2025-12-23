#include <iostream>
#include <vector>
#include <utility>
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

int main() {
    vector<int> heap;
    int x;
    while ((cin >> x) && x != -1) {
        heap.push_back(x);
    }
    build_max_heap(heap);
    for (auto x : heap) cout << x << " ";
    cout << endl;
}