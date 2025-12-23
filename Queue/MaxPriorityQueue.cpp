#include <iostream>
#include <vector>
using namespace std;

// Returns index of parent
int parent(int i) { return (i - 1) / 2; }

// Returns index of left child
int leftChild(int i) { return 2 * i + 1; }

// Returns index of right child
int rightChild(int i) { return 2 * i + 2; }

// Shift up to maintain max-heap property
void shiftUp(int i, vector<int> &arr) {
    while (i > 0 && arr[parent(i)] < arr[i]) {
        swap(arr[parent(i)], arr[i]);
        i = parent(i);
    }
}

// Shift down to maintain max-heap property
void shiftDown(int i, vector<int> &arr, int size) {
    int maxIndex = i;
    int l = leftChild(i);
    if (l < size && arr[l] > arr[maxIndex]) maxIndex = l;
    int r = rightChild(i);
    if (r < size && arr[r] > arr[maxIndex]) maxIndex = r;

    if (i != maxIndex) {
        swap(arr[i], arr[maxIndex]);
        shiftDown(maxIndex, arr, size);
    }
}

// Insert a new element
void insert(int p, vector<int> &arr) {
    arr.push_back(p);
    shiftUp(arr.size() - 1, arr);
}

// Extract element with maximum priority
int pop(vector<int> &arr) {
    int size = arr.size();
    if (size == 0) return -1;
    int result = arr[0];
    arr[0] = arr[size - 1];
    arr.pop_back();
    shiftDown(0, arr, arr.size());
    return result;
}

// Get current maximum element
int getMax(vector<int> &arr) {
    if (arr.empty()) return -1;
    return arr[0];
}

// Print heap
void printHeap(vector<int> &arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> pq;

    insert(45, pq);
    insert(20, pq);
    insert(14, pq);
    insert(12, pq);
    insert(31, pq);
    insert(7, pq);
    insert(11, pq);
    insert(13, pq);
    insert(7, pq);

    cout << "Priority Queue after inserts: ";
    printHeap(pq);

    // Demonstrate getMax
    cout << "Current max element: " << getMax(pq) << endl;

    // Demonstrate extractMax
    pop(pq) ;
    cout << "Priority Queue after extracting max: ";
    printHeap(pq);


    return 0;
}