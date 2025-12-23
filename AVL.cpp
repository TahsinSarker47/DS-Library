#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
    Node* parent;
    Node(int v = 0, int h = -1, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
        : data(v), height(h), left(l), right(r), parent(p) {}
};

class AVL {
private:
    Node* root;
    int nodes;
    static int childHeight(Node* x) { return x ? x->height : -1; }

    void preorder(Node *node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    void inorder(Node *node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    void postorder(Node *node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
    void levelorder(Node* root) {
        if (!root) return;
        queue<pair<Node*, int>> q;
        q.push({root, 1});
        int currentLevel = 1;
        cout << "Level 1: ";
        while (!q.empty()) {
            auto [node, level] = q.front();
            q.pop();
            if (level != currentLevel) {
                currentLevel = level;
                cout << "\nLevel " << currentLevel << ": ";
            }
            cout << node->data << "(";
            if (node->parent) {
                cout << node->parent->data;
            } else {
                cout << "null";
            }
            cout << ") ";
            if (node->left)
                q.push({node->left, level + 1});
            if (node->right)
                q.push({node->right, level + 1});
        }
        cout << endl;
    }
    Node* search(int key) {
        Node* temp = root;
        while (temp && temp->data != key) {
            if (temp->data < key) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        return temp;
    }
    void description(Node* node) const {
        cout << "Parent(";
        if (node->parent) cout << node->parent->data;
        else cout << "Null";
        cout << "), Left(";
        if (node->left) cout << node->left->data;
        else cout << "Null";
        cout << "), Right(";
        if(node->right) cout << node->right->data;
        else cout << "Null";
        cout << ")" << endl;
    }
    Node* subtreeMin(Node* node) {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }
    Node* subtreeMax(Node* node) {
        if (!node) return nullptr;
        while (node->right) node = node->right;
        return node;
    }
    Node* predecessor(Node* node) {
        if (!node) return nullptr;
        if (node->left)
            return subtreeMax(node->left);
        Node* cur = node;
        Node* p = node->parent;
        while (p && cur == p->left) {
            cur = p;
            p = p->parent;
        }
        return p;
    }
    Node* successor(Node* node) {
        if (!node) return nullptr;
        if (node->right)
            return subtreeMin(node->right);
        Node* cur = node;
        Node* p = node->parent;
        while (p && cur == p->right) {
            cur = p;
            p = p->parent;
        }
        return p;
    }
    int kthSmallestRecur(Node* node, int &cnt, int k) {
        if (node == nullptr) return -1;
        int left = kthSmallestRecur(node->left, cnt, k);
        if (left != -1) return left;
        cnt++;
        if (cnt == k) return node->data;
        int right = kthSmallestRecur(node->right, cnt, k);
        return right;
    }
    void inorderDesc(Node* root, Node* node, int& size) {
        if (!node) return;
        inorderDesc(root, node->left, size);
        if (node != root) {
            cout << node->data << " ";
            ++size;
        }
        inorderDesc(root, node->right, size);
    }
    void ancestors(Node* node) {
        if ((!node) || (!node->parent)) {
            cout << "Null" << endl;
            return;
        }
        node = node->parent;
        while (node) {
            cout << node->data << " ";
            node = node->parent;
        }
        cout << endl;
    }
    void descendents(Node* node) {
        int size = 0;
        inorderDesc(node, node, size);
        if (size == 0) {
            cout << "Null";
        }
        cout << endl;
    }
    int height(Node* node) const {
        if (!node) return -1;
        return node->height;
    }
    int diameter(Node* node) {
        if (!node) return 0;
        int left_h = height(node->left) + 1;
        int right_h = height(node->right) + 1;
        int cur_diameter = left_h + right_h + 1;
        int left_diameter = diameter(node->left);
        int right_diameter = diameter(node->right);
        return max(cur_diameter, max(left_diameter, right_diameter));
    }
    void leafNodes(Node* node) {
        if (!node) return;
        leafNodes(node->left);
        if (node->height == 0) cout << node->data << " ";
        leafNodes(node->right);
    }
    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    int balance_factor(Node *x) {
        if (!x) return 0;
        return height(x->left) - height(x->right);
    }
    void update_height(Node *x) {
        if (!x) return;
        x->height = max(height(x->left), height(x->right)) + 1;
    }
    void update_ancestor_heights(Node *z) {
        Node *temp = z;
        while (temp) {
            update_height(temp);
            temp = temp->parent;
        }
    }

    void right_rotate(Node *z) {
        if (!z || !z->left) return;
        Node *y = z->left;
        Node *yR = y->right;
        y->parent = z->parent;
        if (z->parent == nullptr) {
            root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->right = z;
        z->parent = y;
        z->left = yR;
        if (yR) yR->parent = z;
        update_height(z);
        update_height(y);
        update_ancestor_heights(y->parent);
    }
    void left_rotate(Node *z) {
        if (!z || !z->right) return;
        Node *y = z->right;
        Node *yL = y->left;
        y->parent = z->parent;
        if (z->parent == nullptr) {
            root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->left = z;
        z->parent = y;
        z->right = yL;
        if (yL) yL->parent = z;
        update_height(z);
        update_height(y);
        update_ancestor_heights(y->parent);
    }
    void balance_node(Node* z, int bfact) {
        if (!z) return;
        // Left heavy
        if (bfact > 1) {
            // LL case (left child's bf >= 0)
            if (balance_factor(z->left) >= 0) {
                right_rotate(z);
            }
            // LR case
            else {
                left_rotate(z->left);
                right_rotate(z);
            }
        }
        // Right heavy
        else if (bfact < -1) {
            // RR case (right child's bf <= 0)
            if (balance_factor(z->right) <= 0) {
                left_rotate(z);
            }
            // RL case
            else {
                right_rotate(z->right);
                left_rotate(z);
            }
        }
    }
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v) v->parent = u->parent;
    }

public:
    AVL() : root(nullptr), nodes(0) {}
    ~AVL() {
        destroy(root);
        root = nullptr;
        nodes = 0;
    }
    void Insert(int data) {
        ++nodes;
        Node* newNode = new Node(data, 0);
        if (!root) {
            root = newNode;
            return;
        }
        Node* temp = root;
        Node* parent = nullptr;
        while (temp) {
            parent = temp;
            if (newNode->data < temp->data){
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        newNode->parent = parent;
        if (newNode->data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        update_ancestor_heights(newNode);
        Node* t = newNode;
        while (t) {
            int bfact = balance_factor(t);
            if (bfact > 1 || bfact < -1) {
                balance_node(t, bfact);
                break; // one rebalance is enough
            } else {
                t = t->parent;
            }
        }
    }
    void Tree_search(int key) {
        Node* node = search(key);
        if (!node) {
            cout << "Not Found" << endl;
            return;
        }
        cout << "Present" << endl;
        description(node);
    }
    void Height(int val) {
        Node* node = search(val);
        cout << (node ? node->height : -1) << endl;
    }
    Node* Tree_maximum() {
        return subtreeMax(root);
    }
    Node* Tree_minimum() {
        return subtreeMin(root);
    }
    void Before_after(int key) {
        Node* node = search(key);
        Node* pred = predecessor(node);
        Node* succ = successor(node);
        if (pred) cout << pred->data;
        else cout << "null";
        cout << " ";
        if (succ) cout << succ->data;
        else cout << "null";
        cout << endl;
    }
    void Max_min(int val) {
        Node* node = search(val);
        Node* maxNode = subtreeMax(node);
        Node* minNode = subtreeMin(node);
        if (maxNode) cout << maxNode->data;
        else cout << "null";
        cout << " ";
        if (minNode) cout << minNode->data;
        else cout << "null";
        cout << endl;
    }
    int LCA(int u, int v) {
        Node* n1 = search(u);
        Node* n2 = search(v);
        if (!n1 || !n2) return -1;
        Node* temp = root;
        while (temp) {
            if (temp->data < n1->data && temp->data < n2->data) {
                temp = temp->right;
            } else if (temp->data > n1->data && temp->data > n2->data) {
                temp = temp->left;
            } else {
                break;
            }
        }
        return temp->data;
    }
    void Path(int u, int v) {
        Node* x = search(u);
        Node* y = search(v);
        if (!x || !y) return;
        Node* lca = root;
        while (lca) {
            if (lca->data < x->data && lca->data < y->data) {
                lca = lca->right;
            } else if (lca->data > x->data && lca->data > y->data) {
                lca = lca->left;
            } else {
                break;
            }
        }
        vector<int> path1, path2;
        for (Node* ptr = x; ptr != lca; ptr = ptr->parent) {
            path1.push_back(ptr->data);
        }
        path1.push_back(lca->data);
        for (Node* ptr = y; ptr != lca; ptr = ptr->parent) {
            path2.push_back(ptr->data);
        }
        for (int e : path1) cout << e << " ";
        for (int i = path2.size() - 1; i >= 0; i--) cout << path2[i] << " ";
        cout << endl;
        cout << path1.size() + path2.size() << endl;
    }
    int Diameter() {
        return diameter(root);
    }
    int kthSmallest(int k) {
        int cnt = 0;
        return kthSmallestRecur(root, cnt, k);
    }
    void PreorderTraversal() {
        preorder(root);
        cout << endl;
    }
    void InorderTraversal() {
        inorder(root);
        cout << endl;
    }
    void PostorderTraversal() {
        postorder(root);
        cout << endl;
    }
    void LevelorderTraversal() {
        levelorder(root);
    }
    void PrintAncetorsAndDescendants(int x) {
        Node* node = search(x);
        if (!node) {
            cout << "Not Found" << endl;
            return;
        }
        ancestors(node);
        descendents(node);
    }
    int nodeCount() const { return nodes; }
    void PrintLeafNodes() {
        leafNodes(root);
    }
    void Tree_delete(int key) {
        Node *z = search(key);
        if (!z) return;
        Node* node = nullptr;
        if (z->left == nullptr){
            node = z->parent;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            node = z->parent;
            transplant(z, z->left);
        }
        else {
            Node *y = subtreeMin(z->right);
            if (y->parent != z) {
                node = y->parent;
                transplant(y, y->right);
                y->right = z->right;
                z->right->parent = y;
            } else {
                node = y;
            }
            transplant(z, y);
            y->left = z->left;
            z->left->parent = y;
        }
        delete z;
        nodes--;
        Node* cur = node;
        while (cur) {
            update_height(cur);
            int bf = balance_factor(cur);
            if (bf > 1 || bf < -1) {
                balance_node(cur, bf);
            }
            cur = cur->parent;
        }
    }
};

int main() {
    AVL tree;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        tree.Insert(x);
    }
    return 0;
}
