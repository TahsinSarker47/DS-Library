#include <iostream>
#include <stack>
using namespace std;

class myQueue {
private:
    stack<int> in;
    stack<int> out;
    int capacity;
    int count;
public:
    myQueue(int cap) : capacity(cap), count(0) {}
    ~myQueue() {}
    bool push(int x) {
        if (isFull()) return false;
        in.push(x);
        ++count;
        return true;
    }
    bool pop() {
        if (isEmpty())  return false;
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        out.pop();
        --count;
        return true;
    }
    int front() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }
    bool isFull() const { return count == capacity; }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

int main() {
    int n, q;
    cin >> n >> q;
    myQueue q(n);

}