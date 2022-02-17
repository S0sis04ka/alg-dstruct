#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* left;
    struct node* right;
    struct node* parent;
    int key;
} node;

typedef struct split_return {
    node* tree1;
    node* tree2;
} split_t;

node* p(node* v) {
    return v->parent;
}

node* g(node* v) {
    return p(p(v));
}

void print(node* t, int n) {
    int i;
    if (t != NULL) {
        print(t->right, n + 1);
        for (i = 0; i < n; i++) putchar(' ');
        printf("%d\n", t->key);
        print(t->left, n + 1);
    }
    return;
}

void update_parent(node* v) {
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

void turn(node* v) {
    if (g(v) != NULL) {
        if (p(v) == g(v)->left) {
            g(v)->left = v;
        }
        else {
            g(v)->right = v;
        }
    }
    if (v == p(v)->left) {
        p(v)->left = v->right;
        v->right = p(v);
    }
    else {
        p(v)->right = v->left;
        v->left = p(v);
    }
    node* gp  = g(v);
    update_parent(v);
    update_parent(p(v));
    v->parent = gp;
}

node* splay(node* v) {
    if (p(v) == NULL) {
        return v;
    }
    if (g(v) == NULL) {
        turn(v);
        return splay(v);
    }
    else {
        if ((v == p(v)->left && p(v) == g(v)->left) || (v == p(v)->right && p(v) == g(v)->right)) {
            turn(p(v));
            turn(v);
        }
        else {
            turn(v);
            turn(v);
        }
        return splay(v);
    }
}

node* find(node* v, int key) {
    if (v == NULL) return NULL;

    if (v->key == key) {
        return splay(v);
    }
    if (key > v->key && v->right != NULL) {
        return find(v->right, key);
    }
    if (key < v->key && v->left != NULL) {
        return find(v->left, key);
    }
    return splay(v);
}

split_t* split(node* tree, int key) {
    tree = find(tree, key);
    split_t* retval = (split_t*)malloc(sizeof(split_t));

    if (tree == NULL) {
        retval->tree1 = NULL;
        retval->tree2 = NULL;
        return retval;
    }
    if (tree->key == key) {
        retval->tree1 = tree->left;
        if (retval->tree1 != NULL) {
            retval->tree1->parent = NULL;
        }
        retval->tree2 = tree->right;
        if (retval->tree2 != NULL) {
            retval->tree2->parent = NULL;
        }
    }
    if (tree->key > key) {
        retval->tree1 = tree->left;
        if (retval->tree1 != NULL) {
            retval->tree1->parent = NULL;
        }
        retval->tree2 = tree;
        retval->tree2->left = NULL;
    }

    if (tree->key < key) {
        retval->tree1 = tree;
        retval->tree2 = tree->right;
        retval->tree1->right = NULL;
        if (retval->tree2 != NULL) {
            retval->tree2->parent = NULL;
        }
    }
    return retval;
}

node* add(node* tree, int key) {
    split_t* splited = split(tree, key);
    node* new_node = (node*)malloc(sizeof(node));
    new_node->key = key;
    new_node->left = splited->tree1;
    new_node->right = splited->tree2;
    new_node->parent = NULL;
    update_parent(new_node);
    return new_node;
}

node* merge(node* tree1, node* tree2) {
    if (tree1 == NULL) {
        return tree2;
    }
    if (tree2 == NULL) {
        return tree1;
    }
    tree1 = find(tree1, tree2->key);
    tree1->right = tree2;
    tree2->parent = tree1;
    return tree1;
}

node* tree_remove(node* tree, int key) {
    split_t* splited = split(tree, key);
    tree = merge(splited->tree1, splited->tree2);
    return tree;
}

int main() {
    char cmd;
    int key;
    node* tree = NULL;

    while (fscanf(stdin, "%c %d", &cmd, &key) > 0) {
        if (cmd == 'a') {
            tree = add(tree, key);
//            print(tree, 0);
        }
        if (cmd == 'r') {
            tree = tree_remove(tree, key);
//            print(tree, 0);
        }
        if (cmd == 'f') {
            tree = find(tree, key);
//            print(tree, 0);
            if (tree != NULL) {
                if (tree->key == key) {
                    printf("yes\n");
                }
                else {
                    printf("no\n");
                }
            }
            else {
                printf("no\n");
            }
        }
    }

    return 0;
}