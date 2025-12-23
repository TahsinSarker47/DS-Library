#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

int findHeight(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    int left_h = findHeight(node->left);
    int right_h = findHeight(node->right);
    return max(left_h, right_h) + 1;
}

void level_order(Node *node) {
    queue<Node*> Q;
    Q.push(node);
    while (!Q.empty()) {
        Node* current = Q.front();
        Q.pop();
        cout << current->data << " ";
        if (current->left != nullptr)
            Q.push(current->left);
        if (current->right != nullptr)
            Q.push(current->right);
    }
}

void preorderTraversal(Node *node) {
    if (node == nullptr) {
        return;
    }
    cout << node->data << " ";
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void inorderTraversal(Node *node) {
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->left);
    cout << node->data << " ";
    inorderTraversal(node->right);
}

void postorderTraversal(Node *node) {
    if (node == nullptr) {
        return;
    }
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    cout << node->data << " ";
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(12);
    root->right = new Node(9);
    root->left->left = new Node(5);
    root->left->right = new Node(6);

    cout << "Inorder traversal ";
    inorderTraversal(root);

    cout << "\nPreorder traversal ";
    preorderTraversal(root);

    cout << "\nPostorder traversal ";
    postorderTraversal(root);
}