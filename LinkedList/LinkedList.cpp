#include <iostream>
#include <stdexcept>
using namespace std;

class List {
private:
    struct Node {
        int data;
        Node *next;
    };
    Node *head, *tail;
        Node* Create_node(int key) {
        Node* newNode = new Node();
        newNode->data = key;
        newNode->next = nullptr;
        return newNode;
    }
public:
    List() : head(nullptr), tail(nullptr) {}
    ~List() {
        clear();
    }
    void clear() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
    }
    void Insert_front(int key) {
        Node* newNode = Create_node(key);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }
    void Insert_back(int key) {
        Node* newNode = Create_node(key);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    bool Insert_after_node(int key, int v) {
        if (!head) return false;               

        Node* temp = head;
        while (temp && temp->data != v) {      
            temp = temp->next;
        }
        if (!temp) return false;               

        Node* newNode = Create_node(key);      
        newNode->next = temp->next;
        temp->next = newNode;
        if (temp == tail) tail = newNode;     
        return true;
    }
    bool Update_node(int key, int v) {
        if (!head) return false;
        Node* temp = head;
        while (temp && temp->data != v) {
            temp = temp->next;
        }
        if (!temp) return false;
        temp->data = key;
        return true;
    }
    bool Insert_after_position(int key, int pos) {
        if (!head) return false;
        if (pos < 0) return false;

        Node* temp = head;
        int idx = 0;
        while (temp && idx < pos) {
            temp = temp->next;
            ++idx;
        }
        if (!temp) return false;              

        Node* newNode = Create_node(key);
        newNode->next = temp->next;
        temp->next = newNode;
        if (temp == tail) tail = newNode;     
        return true;
    }
    void Remove_head() {
        if (!head) return;
        Node* toDelete = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete toDelete;
    }
    void Remove_element(int key) {
        if (head == nullptr) {
            throw invalid_argument("Can't delete the Node");
            return;
        }
        if (head->data == key) {
            Node* toDelete = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete toDelete;
            return;
        } 
        Node *prev = head;
        Node *cur = head->next;
        while (cur != nullptr && cur->data != key) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr) {
            throw invalid_argument("Can't delete the Node");
            return;
        }
        prev->next = cur->next;
        if (cur = tail) {
            tail = prev;
        }
        delete cur;
    }
    void Remove_end() {
        if (head == nullptr) {
            return;
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node *temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }
};

int main() {
}