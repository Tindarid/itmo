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

void insertL(LL pos, Node* k) {
    if (root == NULL) {
        root = k;
    } else {
        Node *t1 = NULL; Node *t2 = NULL;
        split(root, pos, t1, t2); 
        Node *t3 = merge(t1, k);
        root = merge(t3, t2);
    }
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

void search(Node* &node, LL x) {
    LL l = getSize(node->left);
    if (x < l) {
        search(node->left, x);
    } else if (x == l) {
        if (node->key == 0) {
            node = merge(node->left, node->right);
        }
    } else {
        search(node->right, x - l - 1);
    }
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    LL n, m;
    cin >> n >> m;
    for (LL i = 1; i <= n + m + 10; i++) {
        insertL(i, new Node(0));
    }
    for (LL i = 1; i <= n; i++) {
        LL a;
        cin >> a;
        search(root, a);
        insertL(a, new Node(i));
    }
    vector<LL> ans;
    getMas(root, ans);
    LL i;
    for (i = ans.size() - 1; i >= 0; i--) {
        if (ans[i] != 0) {
            break;
        }
    }
    cout << i << endl;
    for (LL j = 1; j <= i; j++) {
        cout << ans[j] << " ";
    }
    return 0;
}
