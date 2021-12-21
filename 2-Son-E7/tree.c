#include "tree.h"
#include "stdio.h"
#include "stdlib.h"

tree_t* create_tree(int data) {
    tree_t* root = (tree_t*) malloc(sizeof(tree_t));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

tree_t* tree_insert(tree_t* root, int data) {
    if (!root) {
        root = (tree_t*) malloc(sizeof(tree_t));
        root->data = data;
        root->left = NULL;
        root->right = NULL;
    }

    else {
        if (data < root->data) {
            root->left = tree_insert(root->left, data);
        }
        if (data >= root->data) {
            root->right = tree_insert(root->right, data);
        }
    }

    return root;
}

void print_tree(tree_t* root, int n) {
    if (root != NULL) {
        print_tree(root->right,  n+1);
        for (int i = 0; i < n; i++) printf("   ");
        printf("%d\n", root->data);
        print_tree(root->left, n+1);
    }
}

void print_tree_nodes(tree_t* root) {
    if (root->left != NULL || root->right != NULL) {
        printf("%d (", root->data);
        if (root->left != NULL) print_tree_nodes(root->left);
        printf(") (");
        if (root->right != NULL) print_tree_nodes(root->right);
        printf(") ");
    }
    else printf("%d", root->data);
}