#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"

/*
  Chip:	Apple M1
  Total Number of Cores:	8 (4 performance and 4 efficiency)
  RAM:	8 GB
  SSD: 256 GB
  Stress_test results:
  Time: 77.433325 sec on graph with 1000 vertex
  Memory: 4 MB
 */

void stress_test() {
    unsigned long start = clock();
    int num_v = 1000;

    int** graph = (int**)malloc(sizeof(int*) * num_v);
    int* colors = (int*) malloc(sizeof(int) * num_v);
    for (int i = 0; i < num_v; i++) {
        graph[i] = (int*) malloc(sizeof(int) * num_v);
    }

    for (int i = 0; i < num_v; i++) {
        for (int j = 0; j < num_v; j++) {
            int e = rand() % 2;
            graph[i][j] = e;
            graph[j][i] = e;
        }
    }
    int k = num_v/2;

    color_graph(graph, 0, colors, num_v, k);
    double time = (double)(clock() - start)/CLOCKS_PER_SEC;
    printf("%f\n", time);
}

int main() {
    stress_test();
    return 0;
}
