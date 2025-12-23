#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Node(int v = 0, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : data(v), left(l), right(r), parent(p) {}
};

class BST {
    private:
    Node* root;
    void preorderTraversal(Node *node) {
        if (node == nullptr) return;
        cout << node->data << "(";
        if (node->parent != nullptr) cout << node->parent->data << ") ";
        else cout << "null) ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
    void inorderTraversal(Node *node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->data << "(";
        if (node->parent != nullptr) cout << node->parent->data << ") ";
        else cout << "null) ";
        inorderTraversal(node->right);
    }
    void postorderTraversal(Node *node) {
        if (node == nullptr) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << "(";
        if (node->parent != nullptr) cout << node->parent->data << ") ";
        else cout << "null) ";
    }
public:
    BST() : root(nullptr) {}
    void Insert(int data) {
        Node* newNode = new Node(data);
        Node* temp = root;
        Node* target = root;
        if (root == nullptr) {
            root = newNode;
        }
        while (temp != nullptr) {
            target = temp;
            if (newNode->data < temp->data){
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        newNode->parent = target;
        if (newNode->data < target->data) {
            target->left = newNode;
        } else {
            target->right = newNode;
        }
    }
    Node* Tree_search(int key) {
        Node* temp = root;
        while (temp != nullptr && temp->data != key) {
            if (temp->data < key) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        return temp;
    }
    Node* Tree_maximum() {
        Node* temp = root;
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp;
    }

};

int main() {

}