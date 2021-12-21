#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main() {
    tree_t* tree = create_tree(10);
    tree_insert(tree, 15);
    tree_insert(tree, 1);
    tree_insert(tree, 4);
    tree_insert(tree, -1);
    tree_insert(tree, 12);
    print_tree(tree, 0);
    print_tree_nodes(tree);
}
