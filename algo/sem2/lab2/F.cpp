#include <iostream>
#include <fstream>
#define LL long long
using namespace std;

struct Node {
    Node *left, *right;
    int size;
    int key;
    int pr;
    Node(int x) {
        key = x;
        pr = rand() * rand();
        size = 1;
        left = right = NULL;
    }
};

Node* root = NULL;

int getSize(Node* t) {
    if (t != NULL) {
        return t->size;
    }
    return 0;
}

void upd(Node* t) {
    if (t != NULL) {
        t->size = 1 + getSize(t->left) + getSize(t->right);
    }
}

void split(Node* t, int k, Node* &t1, Node* &t2) {
    if (t == NULL) {
        t2 = t1 = NULL;
    } else if (k > t->key) {
        Node* temp = NULL;
        split(t->right, k, temp, t2);
        t->right = temp;
        upd(t);
        t1 = t;
    } else {
        Node* temp = NULL;
        split(t->left, k, t1, temp);
        t->left = temp;
        upd(t);
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
        upd(t1);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        upd(t2);
        return t2;
    }
}

void remove(Node* &t, LL k) {
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
    upd(t);
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
    upd(t);
}

LL getAns(Node* node, LL k) {
    if (node == NULL) {
        return -1;
    }
    LL l = getSize(node->left);
    if (l + 1 == k) {
        return node->key;
    } else if (l >= k) {
        return getAns(node->left, k);
    } else {
        return getAns(node->right, k - l - 1);
    }
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        LL a, b;
        cin >> a >> b;
        if (a == 1) {
            insert(root, new Node(b));
        } else if (a == 0) {
            cout << getAns(root, getSize(root) - b + 1) << "\n";
        } else {
            remove(root, b);
        }
    }
    return 0;
}
