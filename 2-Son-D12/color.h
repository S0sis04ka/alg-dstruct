#ifndef LAB_D_COLOR_H
#define LAB_D_COLOR_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int color_graph(int** graph, int s, int* colors, int n, int k);
void solve_from_file(const char* input_filename, const char* output_filename);

#endif //LAB_D_COLOR_H
