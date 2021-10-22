#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  Chip:	Apple M1
  Total Number of Cores:	8 (4 performance and 4 efficiency)
  RAM:	8 GB
  SSD: 256 GB

  Stress_test results:
  Time: 44.825529 sec on graph with 80000 vertex
  Memory: 23,8 Gb
 */

int n;
int** tree;
int* was;
int* queue;
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

void stress_test() {
    unsigned long start = clock();
    int num_v = 80000;
    free(tree);
    tree = (int**)malloc(sizeof(int*) * num_v); //32000
    queue = (int*) malloc(sizeof(int) * num_v);
    was = (int*) malloc(sizeof(int) * num_v); //640000 byte
    for (int i = 0; i < num_v; i++) {
        tree[i] = (int*) malloc(sizeof(int) * num_v);
        for (int j = 0; j < num_v; j++) {
            tree[i][j] = rand() % 2;
        }
    }
    dfs(0);
    double time = (double)(clock() - start)/CLOCKS_PER_SEC;
    printf("%f\n", time);
}

int main() {
    fscanf(stdin, "%d", &n);

    tree = (int**)malloc(sizeof(int*) * n);
    if (tree == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        tree[i] = (int*)malloc(sizeof(int) * n);
        was = (int*)malloc(sizeof(int) * n);
        queue = (int*)malloc(sizeof(int) * n);
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

//    stress_test();

    return 0;
}
