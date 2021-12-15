#include "color.h"

int color_graph(int** graph, int s, int* colors, int n, int k) {
    int* queue = (int*)malloc(sizeof(int) * n);
    int count = 0;
    int ind = 0;
    queue[count] = s;
    int* n_colors = (int*)malloc(sizeof(int) * n);
    while (ind <= count) {
        int v = queue[ind];
        ind++;
        for (int i = 0; i < n; i++) {
            n_colors[i] = 0;
            if (graph[v][i] == 1) {
                if (colors[i] == 0) {
                    count++;
                    queue[count] = i;
                }
                n_colors[i] = colors[i];
            }
        }

        int cur_color = 0;
        for (int i = 1; i <= k; i++) {
            int found = 0;
            for (int j = 0; j < n; j++) {
                if (i == n_colors[j]) {
                    found = 1;
                }
            }
            if (found == 0) {
                cur_color = i;
                break;
            }
        }
        if (cur_color == 0) {
            return 1;
        }
        colors[v] = cur_color;
    }

    for (int i = 0; i < n; i++) {
        if (colors[i] == 0) {
            int res = color_graph(graph, i, colors, n, k);
            if (res == 1) {
                return 1;
            }
        }
    }

    return 0;
}

void solve_from_file(const char* input_filename, const char* output_filename) {
    FILE* fin = fopen(input_filename, "r");
    FILE* fout = fopen(output_filename, "w");
    assert(fin != NULL);
    assert(fout != NULL);

    int n, k;
    fscanf(fin, "%d", &n);
    fscanf(fin, "%d", &k);

    int** graph = (int**)malloc(sizeof(int*) * n);
    int* colors = (int*)malloc(sizeof(int) * n);;
    for (int i = 0; i < n; i++) {
        graph[i] = (int*) malloc(sizeof(int) * n);
    }
    int x, y;
    while (fscanf(fin, "%d %d", &x, &y) != EOF) {
        graph[x-1][y-1] = 1;
        graph[y-1][x-1] = 1;
    }
    fclose(fin);

    int res = color_graph(graph, 0, colors, n, k);
    if (res == 0) {
        for (int i = 0; i < n; i++) {
            fprintf(fout, "%d ", colors[i]);
        }
    }
    else {
        fprintf(fout, "%d", 0);
    }
    fclose(fout);
}