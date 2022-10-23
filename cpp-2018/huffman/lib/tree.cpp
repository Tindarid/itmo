#include "tree.h"
#include <set>

tree::tree(std::vector<size_t> t) {
    this->buildTree(t);
    this->dfs(root, 0, 0);
}

uint64_t tree::getCode(char c) {
    return code[(unsigned char)c];
}

size_t tree::getCodeLength(char c) {
    return codeLength[(unsigned char)c];
}

void tree::buildTree(std::vector<size_t> t) {
    std::set<node*, nodeComp> tr;
    for (size_t i = 0; i < t.size(); ++i) {
        if (t[i] != 0) {
            tr.insert(new node((char)i, t[i], nullptr, nullptr, true));
        } else {
            codeLength[i] = 0;
        }
    }
    if (tr.size() == 0) {
        curnode = root = nullptr;
        return;
    }
    while (tr.size() != 1) {
        node* a = *(tr.begin());
        tr.erase(tr.begin());
        node* b = *(tr.begin());
        tr.erase(tr.begin());
        tr.insert(new node(0, a->count + b->count, b, a, false));
    }
    root = *(tr.begin());
    tr.erase(tr.begin());
    curnode = root;
}

void tree::dfs(node* v, uint64_t temp, size_t curDepth) {
    if (v == nullptr) {
        return;
    }
    if (v->flag) {
        code[(unsigned char)v->symbol] = temp;
        if (curDepth == 0) {
            codeLength[(unsigned char)v->symbol] = 1;
        } else {
            codeLength[(unsigned char)v->symbol] = curDepth;
        }
        return;
    }
    if (v->right != nullptr) {
        dfs(v->right, (temp << 1), curDepth + 1);
    }
    if (v->left != nullptr) {
        dfs(v->left, (temp << 1) + 1ULL, curDepth + 1);
    }
}

bool tree::down(char temp) {
    if (curnode->left == NULL) {
        return (curnode == root ? true : false);
    }
    if (temp == 1) {
        curnode = curnode->left;
        return true;
    } else {
        curnode = curnode->right;
        return true;
    }
}

bool tree::isTerm() {
    if (curnode->flag) {
        return true;
    }
    return false;
}

void tree::reset() {
    curnode = root;
}

char tree::getSymbol() {
    return curnode->symbol;
}

tree::~tree() {
    if (root != nullptr) {
        delete root;
    }
    root = nullptr;
}
