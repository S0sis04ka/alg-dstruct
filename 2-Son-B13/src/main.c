#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memallocator.h"

typedef u_int8_t byte;
#define MAX_ITERATIONS 10000
#define MAX_ALLOCATED_SIZE 1000

double mallocTime[MAX_ITERATIONS];
double labTime[MAX_ITERATIONS];

void mallocTest(int iter) {
    unsigned long start = clock();
    for (int i = 0; i < iter; i++) {
        byte* ptr = malloc(sizeof(byte) * (rand() % MAX_ALLOCATED_SIZE));
    }
    mallocTime[iter] = (double)(clock() - start)/CLOCKS_PER_SEC;
}

void labTest(int iter) {
    unsigned long start = clock();
    for (int i = 0; i < iter; i++) {
        byte* ptr = memalloc(sizeof(byte) * (rand()%MAX_ALLOCATED_SIZE));
        memfree(ptr);
    }
    labTime[iter] = (double)(clock() - start)/CLOCKS_PER_SEC;
}

int main() {
    FILE* file = fopen("../results.txt", "w");
    if (file == NULL) {
        return -1;
    }

    byte* stack[MAX_ALLOCATED_SIZE + memgetminimumsize()];
    meminit(stack, MAX_ALLOCATED_SIZE + memgetminimumsize());
    for (int i = 1; i < MAX_ITERATIONS; i++) {
        mallocTest(i);
        labTest(i);
        fprintf(file, "%d %f %f\n", i, mallocTime[i], labTime[i]);
    }
    printf("kek\n");
    fclose(file);
    return 0;
}
