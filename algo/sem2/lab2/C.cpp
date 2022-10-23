#include <cstdio>
#define LL int
#define SIZE 300005
using namespace std;

LL p[SIZE], l[SIZE], r[SIZE];

struct Node {
    Node *left, *right;
    LL key;
    LL pr;
    LL ind;
    Node(LL x, LL y, LL i) {
        key = x;
        pr = y;
        ind = i;
        left = right = NULL;
    }
};

Node* root = NULL;

void split(Node* t, LL k, Node* &t1, Node* &t2) {
    if (t == NULL) {
        t2 = t1 = NULL;
    } else if (k > t->key) {
        Node* temp;
        split(t->right, k, temp, t2);
        t->right = temp;
        t1 = t;
    } else {
        Node* temp;
        split(t->left, k, t1, temp);
        t->left = temp;
        t2 = t;
    }
}

void insert(Node* &t, Node* k) {
    if (t == NULL) {
        t = k;
    } else if (t->pr < k->pr) {
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

void dfs(Node* from, Node* to) {
    int temp = to->ind - 1;
    if (from != NULL) {
        p[temp] = from->ind;
    }
    if (to->left != NULL) {
        l[temp] = to->left->ind;
        dfs(to, to->left);
    }
    if (to->right != NULL) {
        r[temp] = to->right->ind;
        dfs(to, to->right);
    }
}

int main() {
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    LL n;
    scanf("%d", &n);
    LL a, b;
    for (LL i = 1; i <= n; ++i) {
        scanf("%d%d", &a, &b);
        insert(root, new Node(a, b, i));
    }
    dfs(NULL, root);
    printf("YES\n");
    for (LL i = 0; i < n; ++i) {
        printf("%d %d %d\n", p[i], l[i], r[i]);
    }
}

