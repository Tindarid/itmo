#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define LL long long

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
    } else {
        t->size = 0;
    }
}

void split(Node* t, int k, Node* &t1, Node* &t2) {
    if (t == NULL) {
        t2 = t1 = NULL;
        return;
    }
    int l = getSize(t->left);
    if (l >= k) {
        Node* temp = NULL;
        split(t->left, k, t1, temp);
        t->left = temp;
        upd(t);
        t2 = t;
    } else {
        Node* temp = NULL;
        split(t->right, k - l - 1, temp, t2);
        t->right = temp;
        upd(t);
        t1 = t;
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

void getMas(Node* node, vector<LL> &ans) {
    if (node == NULL) {
        return;
    }
    if (node->left != NULL) {
        getMas(node->left, ans);
    }
    ans.push_back(node->key);
    if (node->right != NULL) {
        getMas(node->right, ans);
    }
}

void update(LL l, LL r) {
    Node* t1 = NULL; Node* t2 = NULL; Node* t3 = NULL; Node* t4 = NULL;
    split(root, l - 1, t1, t2);
    split(t2, r - l + 1, t3, t4);
    t2 = merge(t3, t1);
    root = merge(t2, t4);
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    LL n, m;
    cin >> n >> m;
    for (LL i = 1; i <= n; i++) {
        insert(root, new Node(i));
    }
    for (LL i = 0; i < m; i++) {
        LL a, b;
        cin >> a >> b;
        update(a, b);
    }
    vector<LL> ans;
    getMas(root, ans);
    for (LL i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
