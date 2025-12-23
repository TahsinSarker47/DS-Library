#include <iostream>
using namespace std;

void circular_enqueue(int queue[], int item, int &rear, int maxQ, int &count) {
    if (count == maxQ) {
        // overflow
        return;
    }
    queue[rear] = item;
    rear = (rear + 1) % maxQ;
    count++;
}

void circular_dequeue(int queue[], int &front, int rear, int &count, int maxQ) {
    if (count == 0) {
        // underflow
        return;
    }
    front = (front + 1) % maxQ;
    count--;
}

int Size(int queue[], int count) {
    return count;
}



int main() {
    int *queue, front = 0, rear = 0, count = 0, maxQ;
    cin >> maxQ;
    queue = new int[maxQ];
    delete[] queue;
}