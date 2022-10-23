#ifndef TREE_H
#define TREE_H
#include <vector>
#include <stdint.h>

class tree {
    public:
        tree(std::vector<size_t>);
        tree();
        ~tree();
        uint64_t getCode(char);
        size_t getCodeLength(char);
        bool down(char);
        bool isTerm();
        void reset();
        char getSymbol();
    private:
        void buildTree(std::vector<size_t>);
        uint64_t code[256];
        size_t codeLength[256];

    struct node {
        node* left;
        node* right;
        size_t count;
        char symbol;
        bool flag;
        node(char symb, size_t c, node* l, node* r, bool f) {
            count = c;
            symbol = symb;
            left = l;
            right = r;
            flag = f;
        }
        ~node() {
            if (left != nullptr) {
                delete left;
            }
            if (right != nullptr) {
                delete right;
            }
            left = nullptr;
            right = nullptr;
        }
    };

    node* root;
    node* curnode;
    void dfs(node*, uint64_t, size_t);

    struct nodeComp {
        bool operator() (node* a, node* b) {
            return a->count <= b->count;
        }
    };
};

#endif
