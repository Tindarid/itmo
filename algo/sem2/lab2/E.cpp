#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#define MOD 1000000000
#define LL long long
using namespace std;

struct Node {
    Node *left, *right;
    LL key;
    LL pr;
    LL sum;
    Node(LL x) {
        key = x;
        pr = rand() * rand();
        left = right = NULL;
        sum = x;
    }
};

Node* root = NULL;

LL getSum(Node* t) {
    if (t != NULL) {
        return t->sum;
    }
    return 0;
}

void updSum(Node* t) {
    if (t != NULL) {
        t->sum = t->key + getSum(t->left) + getSum(t->right);
    } else {
        t->sum = 0;
    }
}

void split(Node* t, LL k, Node* &t1, Node* &t2) {
    if (t == NULL) {
        t2 = t1 = NULL;
    } else if (k > t->key) {
        Node* temp = NULL;
        split(t->right, k, temp, t2);
        t->right = temp;
        updSum(t);
        t1 = t;
    } else {
        Node* temp = NULL;
        split(t->left, k, t1, temp);
        t->left = temp;
        updSum(t);
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
        updSum(t1);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        updSum(t2);
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
    updSum(t);
}

Node* search(Node* node, LL x) {
    if (node == NULL || x == node->key) {
        return node;
    } else if (x < node->key) {
        return search(node->left, x);
    } else {
        return search(node->right, x);
    }
}

LL getAns(LL l, LL r) {
    Node* t1 = NULL; Node* t2 = NULL; Node* t3 = NULL; Node* t4 = NULL;
    split(root, l, t1, t2);
    split(t2, r + 1, t3, t4);
    LL ans = getSum(t3);
    t2 = merge(t3, t4);
    root = merge(t1, t2);
    return ans;
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    srand(time(0));
    LL n;
    bool flag = false;
    LL y = 0;
    cin >> n;
    for (LL i = 0; i < n; i++) {
        char c;
        LL a = 0, b = 0;
        cin >> c;
        if (c == '+') {
            cin >> a;
            if (flag) {
                a = (a + y) % MOD;
            }
            if (search(root, a) == NULL) {
                insert(root, new Node(a));
            }
            flag = false;
        } else if (c == '?') {
            cin >> a >> b;
            y = getAns(a, b);
            cout << y << "\n";
            flag = true;
        }
    }
    return 0;
}
