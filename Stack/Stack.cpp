#include <iostream>
using namespace std;

int *stack, n, top = -1, count = 0;
void push(int x) {
    if (top == n - 1) {
        cout << "Stack Overflow" << endl;
        return;
    }
    top++;
    stack[top] = x;
}

bool isEmpty() {
    return top == -1;
}

void pop(int stack[], int n, int top) {
    if (isEmpty()) {
        cout << "Underflow" << endl;
        return;
    }
    top--;
}

int topElement() {
    if (!isEmpty()) return stack[top];
    return -1;
}

int size() {
    return top + 1;
}



int main() {
    cin >> n;
    stack = new int[n];

    delete[] stack;
}