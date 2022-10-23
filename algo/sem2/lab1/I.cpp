#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n;

struct Node {
    Node *left, *right;
    int sum, h, D, l, r;
    bool f;
    Node(int a, int b) {
        l = a; r = b;
        sum = h = D = 0;
        f = true;
        left = right = NULL;
    }
};

void push(Node *node) {
    if (node->r == node->l) {
        node->f = false;
        node->h = node->sum = node->D;
        return;
    }
    if (node->left == NULL) {
        node->left = new Node(node->l, (node->r + node->l) / 2);
        node->right = new Node((node->r + node->l) / 2 + 1, node->r);
    }
    node->left->h = node->left->sum = node->D * (node->left->r - node->left->l + 1);
    node->right->h = node->right->sum = node->D * (node->right->r - node->right->l + 1);
    node->left->f = node->right->f = true;
    node->left->D = node->right->D = node->D;
    node->f = false;
}

int find(Node *node, int h) {
    if (node->l == node->r) {
        if (node->h > h) {
            return node->l - 1;
        } else {
            return node->l;
        }
    }
    if (node->f) {
        push(node);
    }
    if (node->left->h > h) {
        return find(node->left, h);
    } else {
        return find(node->right, h - node->left->sum);
    }
}

void update(Node *node, int a, int b, int D) {
    int l = node->l;
    int r = node->r;
    if (l >= a && r <= b) {
        node->f = true;
        node->h = node->sum = D * (r - l + 1);
        node->D = D;
        return;
    }
    if (l > b || r < a) {
        return;
    }
    if (node->f) {
        push(node);
    }
    update(node->left, a, b, D);
    update(node->right, a, b, D);
    node->sum = node->left->sum + node->right->sum;
    node->h = max(node->left->h, node->left->sum + node->right->h);
    return;
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int k;
    cin >> k;
    n = 1;
    while (n < k) {
        n *= 2;
    }
    Node *root = new Node(1, n);
    while (true) {
        char c;
        cin >> c;
        if (c == 'Q') {
            int h;
            cin >> h;
            int ans = find(root, h);
            if (ans > k) {
                ans = k;
            }
            cout << ans << "\n";
        } else if (c == 'I') {
            int a, b, D;
            cin >> a >> b >> D;
            update(root, a, b, D);
        } else {
            break;
        }
    }
    return 0;
}
