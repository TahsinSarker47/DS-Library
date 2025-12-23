#include <iostream>
using namespace std;

class CircularQueue {
private:
    int *arr;
    int capacity;
    int front;
    int rear;
    int count;
public:
    CircularQueue(int cap) : capacity(cap), front(0), rear(0), count(0) {
        arr = new int[capacity];
    }
    ~CircularQueue() {
        delete[] arr;
    }
    bool enqueue(int item) {
        if (isFull()) {
            cout << "Overflow\n";
            return false;
        }
        arr[rear] = item;
        rear = (rear + 1) % capacity;
        count++;
        return true;
    }
    bool dequeue() {
        if (isEmpty()) {
            cout << "Underflow\n";
            return false;
        }
        front = (front + 1) % capacity;
        count--;
        return true;
    }
    int getFront() const {
        if (count == 0) {
            return -1;
        }
        return arr[front];
    }
    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
    void printArray() {
        for (int i = front, cnt = 0; cnt < capacity; cnt++, i = (i+1) % capacity) {
            cout << arr[i] << " ";
        }
        cout << "\b\n";
    }
};



int main() {
        
}