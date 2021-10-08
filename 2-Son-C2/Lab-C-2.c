#include <stdio.h>
#include <stdlib.h>

#define MAXN (int)1e7 + 1

int n;
int** tree;
int was[MAXN];
int queue[MAXN];
int count = 0;

void dfs(int node) {
    was[node] = 1;
    queue[count] = node;

    for (int i = 0; i < n; i++) {
        if (tree[node][i] == 1 && was[i] != 1) {
            count++;
            dfs(i);
        }
    }
};

int main() {
    fscanf(stdin, "%d", &n);

    tree = (int**)malloc(sizeof(int*) * n);
    if (tree == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        tree[i] = (int*)malloc(sizeof(int) * n);
        if (tree[i] == NULL) {
            return 1;
        }
    }

    int x, y;
    while (fscanf(stdin, "%d %d", &x, &y) != EOF) {
        tree[x][y] = 1;
        tree[y][x] = 1;
    }

    dfs(0);

    for (int i = 0; i < n; i++) {
        fprintf(stdout, "%d ", queue[i]);
    }

    return 0;
}
