#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    Node *left, *right;
    int key;
    Node(int val) {
        key = val;
        left = right = NULL;
    }
};

Node *root = NULL;

Node* insert(Node* node, int x) {
    if (node == NULL) {
        return new Node(x);
    } else if (node->key > x) {
        node->left = insert(node->left, x);
    } else if (node->key < x) {
        node->right = insert(node->right, x);
    }
    return node;
}

Node* search(Node* node, int x) {
    if (node == NULL || x == node->key) {
        return node;
    } else if (x < node->key) {
        return search(node->left, x);
    } else {
        return search(node->right, x);
    }
}

bool exists(Node* node, int x) {
    Node * ans = search(node, x);
    if (ans == NULL) {
        return false;
    } else {
        return true;
    }
}

Node * next(int x) {
    Node* cur = root, *suc = NULL;
    while (cur != NULL) {
        if (cur->key > x) {
            suc = cur;
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return suc;
}

Node * prev(int x) {
    Node* cur = root, *suc = NULL;
    while (cur != NULL) {
        if (cur->key < x) {
            suc = cur;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    return suc;
}

Node * minim(Node *node) {
    if (node->left == NULL) {
        return node;
    }
    return minim(node->left);
}

Node * deleteF(Node* node, int x) {
    if (node == NULL) {
        return node;
    }
    if (x < node->key) {
        node->left = deleteF(node->left, x);
    } else if (x > node->key) {
        node->right = deleteF(node->right, x);
    } else if (node->left != NULL && node->right != NULL) {
        node->key = (minim(node->right))->key;
        node->right = deleteF(node->right, node->key);
    } else {
        if (node->left != NULL) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    string s = "";
    int x = 0;
    while (true) {
        cin >> s;
        if (cin.eof()) {
            break;
        }
        cin >> x;
        if (s == "insert") {
            root = insert(root, x);
        } else if (s == "delete") {
            root = deleteF(root, x);
        } else if (s == "exists") {
            if (exists(root, x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (s == "next") {
            Node* ans = next(x);
            if (ans == NULL) {
                cout << "none\n";
            } else {
                cout << ans->key << "\n";
            }
        } else if (s == "prev") {
            Node* ans = prev(x);
            if (ans == NULL) {
                cout << "none\n";
            } else {
                cout << ans->key << "\n";
            }
        } else {
            break;
        }
    }
    return 0;
}
