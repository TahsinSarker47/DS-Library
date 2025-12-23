#include <iostream>
using namespace std;

// 0 based indexing
void enqueue(int queue[], int item, int &rear, int maxQ) {
    if (rear == maxQ - 1) {
        cout << "Overflow" << endl;
        return;
    }
    queue[rear] = item;
    rear++;
}

void dequeue(int queue[], int &front, int rear) {
    if (front == rear) {
        // Underflow
        return;
    }
    front++;
}

int getFront(int queue[], int front) {
    return queue[front];
}

int size(int front, int rear) {
    return (rear - front);
}

bool isEmpty(int front, int rear) {
    return front == rear;
}

int main() {
    int *queue, front = 0, rear = 0, maxQ;
    cin >> maxQ;
    queue = new int[maxQ];

    delete[] queue;
}