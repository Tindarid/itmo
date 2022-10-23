#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Node {
    Node *left, *right;
    int key;
    int pr;
    Node(int x) {
        key = x;
        pr = rand() * rand();
        left = right = NULL;
    }
};

Node* root = NULL;

void split(Node* t, int k, Node* &t1, Node* &t2) {
    if (t == NULL) {
        t2 = t1 = NULL;
    } else if (k > t->key) {
        Node* temp = NULL;
        split(t->right, k, temp, t2);
        t->right = temp;
        t1 = t;
    } else {
        Node* temp = NULL;
        split(t->left, k, t1, temp);
        t->left = temp;
        t2 = t;
    }
}

Node* merge(Node* &t1, Node* &t2) {
    if (t2 == NULL) {
        return t1;
    } else if (t1 == NULL) {
        return t2;
    } else if (t1->pr > t2->pr) {
        t1->right = merge(t1->right, t2);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        return t2;
    }
}

void insert(Node* &t, Node* k) {
    if (t == NULL) {
        t = k;
    } else if (t->pr > k->pr) {
        if (t->key > k->key) {
            insert(t->left, k);
        } else {
            insert(t->right, k);
        }
    } else {
        split(t, k->key, k->left, k->right);
        t = k;
    }
}

void remove(Node* &t, int k) {
    if (t == NULL) {
        return;
    }
    if (t->key == k) {
        t = merge(t->left, t->right);
    } else if (k < t->key) {
        remove(t->left, k);
    } else {
        remove(t->right, k);
    }
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

Node* next(Node* cur, int x) {
    Node* suc = NULL;
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

Node* prev(Node* cur, int x) {
    Node* suc = NULL;
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

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    srand(time(0));
    string s = "";
    int x = 0;
    while (true) {
        cin >> s;
        if (cin.eof()) {
            break;
        }
        cin >> x;
        if (s == "insert") {
            Node* ans = search(root, x);
            if (ans == NULL) {
                insert(root, new Node(x));
            }
        } else if (s == "delete") {
            Node* ans = search(root, x);
            if (ans != NULL) {
                remove(root, x);
            }
        } else if (s == "exists") {
            Node* ans = search(root, x);
            if (ans != NULL) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (s == "next") {
            Node* ans = next(root, x);
            if (ans == NULL) {
                cout << "none\n";
            } else {
                cout << ans->key << "\n";
            }
        } else if (s == "prev") {
            Node* ans = prev(root, x);
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
