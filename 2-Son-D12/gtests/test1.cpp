#include <gtest/gtest.h>

#define INPUT_FILENAME "../input.txt"
#define OUTPUT_FILENAME "../output.txt"
#define MAX_CHAR 100

extern "C"{
#include "../color.h"
#include <iostream>
}


TEST(functional_test, example) {
    FILE* fin = fopen(INPUT_FILENAME, "w");
    fprintf(fin, "3 3\n"
                 "2 3\n"
                 "1 3\n"
                 "1 2");
    fclose(fin);

    solve_from_file(INPUT_FILENAME, OUTPUT_FILENAME);
    FILE* fout = fopen(OUTPUT_FILENAME, "r");
    char ans[MAX_CHAR] = {'\0'};
    fgets(ans, MAX_CHAR, fout);
    EXPECT_TRUE(strcmp(ans, "1 2 3 ") == 0);
}

TEST(functional_test, one_node_zero_colors){
    FILE* input = fopen(INPUT_FILENAME, "w");
    fprintf(input, "1 0\n");
    fclose(input);

    solve_from_file(INPUT_FILENAME, OUTPUT_FILENAME);

    FILE* output = fopen(OUTPUT_FILENAME, "r");
    char ans[MAX_CHAR] = {'\0'};
    fgets(ans, MAX_CHAR, output);
    EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Simle_test, one_node_one_color) {
    FILE* fin = fopen(INPUT_FILENAME, "w");
    fprintf(fin, "1 1\n");
    fclose(fin);

    solve_from_file(INPUT_FILENAME, OUTPUT_FILENAME);
    FILE* fout = fopen(OUTPUT_FILENAME, "r");
    char ans[MAX_CHAR] = {'\0'};
    fgets(ans, MAX_CHAR, fout);
    EXPECT_TRUE(strcmp(ans, "1 ") == 0);
}

TEST(functional_test, line_graph) {
    FILE* fin = fopen(INPUT_FILENAME, "w");
    fprintf(fin, "4 2\n"
                 "1 2\n"
                 "2 3\n"
                 "3 4");
    fclose(fin);

    solve_from_file(INPUT_FILENAME, OUTPUT_FILENAME);
    FILE* fout = fopen(OUTPUT_FILENAME, "r");
    char ans[MAX_CHAR] = {'\0'};
    fgets(ans, MAX_CHAR, fout);
    EXPECT_TRUE(strcmp(ans, "1 2 1 2 ") == 0);
}

TEST(functional_test, two_node_island) {
    FILE* fin = fopen(INPUT_FILENAME, "w");
    fprintf(fin, "2 1\n");
    fclose(fin);

    solve_from_file(INPUT_FILENAME, OUTPUT_FILENAME);
    FILE* fout = fopen(OUTPUT_FILENAME, "r");
    char ans[MAX_CHAR] = {'\0'};
    fgets(ans, MAX_CHAR, fout);
    EXPECT_TRUE(strcmp(ans, "1 1 ") == 0);
}

TEST(functional_test, graph_and_single_island) {
    FILE* fin = fopen(INPUT_FILENAME, "w");
    fprintf(fin, "3 2\n"
                 "1 2\n");
    fclose(fin);

    solve_from_file(INPUT_FILENAME, OUTPUT_FILENAME);
    FILE* fout = fopen(OUTPUT_FILENAME, "r");
    char ans[MAX_CHAR] = {'\0'};
    fgets(ans, MAX_CHAR, fout);
    EXPECT_TRUE(strcmp(ans, "1 2 1 ") == 0);
}

TEST(functional_test, four_node_graph) {
    FILE* fin = fopen(INPUT_FILENAME, "w");
    fprintf(fin, "4 3\n"
                 "1 2\n"
                 "1 3\n"
                 "1 4\n"
                 "2 3\n"
                 "3 4\n");
    fclose(fin);

    solve_from_file(INPUT_FILENAME, OUTPUT_FILENAME);
    FILE* fout = fopen(OUTPUT_FILENAME, "r");
    char ans[MAX_CHAR] = {'\0'};
    fgets(ans, MAX_CHAR, fout);
    EXPECT_TRUE(strcmp(ans, "1 2 3 2 ") == 0);
}

TEST(functional_test, star) {
    FILE* fin = fopen(INPUT_FILENAME, "w");
    fprintf(fin, "2 1\n");
    fclose(fin);

    solve_from_file(INPUT_FILENAME, OUTPUT_FILENAME);
    FILE* fout = fopen(OUTPUT_FILENAME, "r");
    char ans[MAX_CHAR] = {'\0'};
    fgets(ans, MAX_CHAR, fout);
    EXPECT_TRUE(strcmp(ans, "1 1 ") == 0);
}
