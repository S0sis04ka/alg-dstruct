#ifndef INC_2_SON_C2_TREE_H
#define INC_2_SON_C2_TREE_H

typedef struct tree {
    int data;
    struct tree* left;
    struct tree* right;
} tree_t;

tree_t* create_tree(int data);
tree_t* tree_insert(tree_t* root, int data);
void print_tree(tree_t* root, int n);
void print_tree_nodes(tree_t* root);

#endif //INC_2_SON_C2_TREE_H
