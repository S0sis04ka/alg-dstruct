//
// Created by Artem Son on 17.09.2021.
//

#include <gtest/gtest.h>

extern "C"{
#include "list.h"
};


TEST(compareDatesTest, date1_moreThan_date2_by_year) {
    struct Date* date1 = (struct Date*)malloc(sizeof(struct Date));
    date1->day = 1;
    date1->month = 1;
    date1->year = 10;
    
    struct Date* date2 = (struct Date*)malloc(sizeof(struct Date));
    date2->day = 1;
    date2->month = 1;
    date2->year = 1;
    
    EXPECT_TRUE(compareDates(date1, date2) > 0);
}

TEST(compareDatesTest, date1_moreThan_date2_by_month) {
    struct Date* date1 = (struct Date*)malloc(sizeof(struct Date));
    date1->day = 1;
    date1->month = 2;
    date1->year = 1;
    
    struct Date* date2 = (struct Date*)malloc(sizeof(struct Date));
    date2->day = 1;
    date2->month = 1;
    date2->year = 1;
    
    EXPECT_TRUE(compareDates(date1, date2) > 0);
}

TEST(compareDatesTest, date1_moreThan_date2_by_day) {
    struct Date* date1 = (struct Date*)malloc(sizeof(struct Date));
    date1->day = 2;
    date1->month = 1;
    date1->year = 1;
    
    struct Date* date2 = (struct Date*)malloc(sizeof(struct Date));
    date2->day = 1;
    date2->month = 1;
    date2->year = 1;
    
    EXPECT_TRUE(compareDates(date1, date2) > 0);
}

TEST(compareDatesTest, date1_equalTo_date2) {
    struct Date* date1 = (struct Date*)malloc(sizeof(struct Date));
    date1->day = 1;
    date1->month = 1;
    date1->year = 1;
    
    struct Date* date2 = (struct Date*)malloc(sizeof(struct Date));
    date2->day = 1;
    date2->month = 1;
    date2->year = 1;
    
    EXPECT_TRUE(compareDates(date1, date2) == 0);
}


TEST(listAddTest, addingFirstEll) {
    struct Node* list = nullptr;
    struct Date* date = (struct Date*)malloc(sizeof(struct Date));
    date->day = 1;
    date->month = 1;
    date->year = 1;
    
    char name[15] = "name";
    char surname[15] = "surname";
    char fathersname[15] = "fath";
    
   listAdd(&list, surname, name, fathersname, date);
    
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list->surname, surname);
    EXPECT_EQ(list->name, name);
    EXPECT_EQ(list->fathersname, fathersname);
    EXPECT_EQ(list->dob, date);
}

TEST(listAddTest, addingInTheEnd) {
    struct Node* list = nullptr;
    struct Date* date = (struct Date*)malloc(sizeof(struct Date));
    date->day = 1;
    date->month = 1;
    date->year = 1;
    
    char name[15] = "kek";
    char surname[15] = "lul";
    char fathersname[15] = "uwu";
    
    struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
    node1->dob = (struct Date*)malloc(sizeof(struct Date));
    node1->dob->day = 1;
    node1->dob->month = 1;
    node1->dob->year = 1000;
    node1->name = (char*)malloc(sizeof(char) * 50);
    node1->surname = (char*)malloc(sizeof(char) * 50);
    node1->fathersname = (char*)malloc(sizeof(char) * 50);
    strcpy(node1->name, "kkk");
    strcpy(node1->surname, "www");
    strcpy(node1->fathersname, "uwu");
    node1->next = NULL;
    
    listAdd(&list, surname, name, fathersname, date);
    listAdd(&list, node1->surname, node1->name, node1->fathersname, node1->dob);
    
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list->next->surname, node1->surname);
    EXPECT_EQ(list->next->name, node1->name);
    EXPECT_EQ(list->next->fathersname, node1->fathersname);
    EXPECT_EQ(list->next->dob, node1->dob);
}

TEST(listAddTest, addingFront) {
    struct Node* list = nullptr;
    struct Date* date = (struct Date*)malloc(sizeof(struct Date));
    date->day = 1;
    date->month = 1;
    date->year = 1000;
    
    char name[15] = "kek";
    char surname[15] = "lul";
    char fathersname[15] = "uwu";
    
    struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
    node1->dob = (struct Date*)malloc(sizeof(struct Date));
    node1->dob->day = 1;
    node1->dob->month = 1;
    node1->dob->year = 1;
    node1->name = (char*)malloc(sizeof(char) * 50);
    node1->surname = (char*)malloc(sizeof(char) * 50);
    node1->fathersname = (char*)malloc(sizeof(char) * 50);
    strcpy(node1->name, "kkk");
    strcpy(node1->surname, "www");
    strcpy(node1->fathersname, "uwu");
    node1->next = NULL;
    
    listAdd(&list, surname, name, fathersname, date);
    listAdd(&list, node1->surname, node1->name, node1->fathersname, node1->dob);
    
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list->surname, node1->surname);
    EXPECT_EQ(list->name, node1->name);
    EXPECT_EQ(list->fathersname, node1->fathersname);
    EXPECT_EQ(list->dob, node1->dob);
}

TEST(listSearchTest, dateInList) {
    struct Node* list = (struct Node*) malloc(sizeof(struct Node));
    struct Date* date = (struct Date*)malloc(sizeof(struct Date));
    date->day = 1;
    date->month = 1;
    date->year = 1000;
    list->surname = "kek";
    list->name = "lul";
    list->fathersname = "uwu";
    list->dob = date;
    list->next = NULL;
    
    
    struct Date* fdate = (struct Date*)malloc(sizeof(struct Date));
    fdate->day = 1;
    fdate->month = 1;
    fdate->year = 1000;
    
    EXPECT_EQ(listSearch(list, fdate), 1);
}

TEST(listSearchTest, dateNotInList) {
    struct Node* list = (struct Node*) malloc(sizeof(struct Node));
    struct Date* date = (struct Date*)malloc(sizeof(struct Date));
    date->day = 1;
    date->month = 1;
    date->year = 1000;
    list->surname = "kek";
    list->name = "lul";
    list->fathersname = "uwu";
    list->dob = date;
    list->next = NULL;
    
    struct Date* fdate = (struct Date*)malloc(sizeof(struct Date));
    fdate->day = 1;
    fdate->month = 1;
    fdate->year = 0;
    
    EXPECT_EQ(listSearch(list, fdate), 0);
}

TEST(listSearchTest, dateInListMulti) {
    struct Node* list = (struct Node*) malloc(sizeof(struct Node));
    struct Date* date1 = (struct Date*)malloc(sizeof(struct Date));
    date1->day = 1;
    date1->month = 1;
    date1->year = 1;
    list->surname = "kek";
    list->name = "lul";
    list->fathersname = "uwu";
    list->dob = date1;
    
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    struct Date* date2 = (struct Date*)malloc(sizeof(struct Date));
    date2->day = 3;
    date2->month = 2;
    date2->year = 1;
    node->surname = "pff";
    node->name = "brr";
    node->fathersname = "grr";
    node->dob = date2;
    node->next = NULL;
    list->next = node;
    
    struct Date* fdate = (struct Date*)malloc(sizeof(struct Date));
    fdate->day = 3;
    fdate->month = 2;
    fdate->year = 1;
    
    EXPECT_EQ(listSearch(list, fdate), 1);
}

TEST(listSearchTest, dateNotInListMulti) {
    struct Node* list = (struct Node*) malloc(sizeof(struct Node));
    struct Date* date1 = (struct Date*)malloc(sizeof(struct Date));
    date1->day = 1;
    date1->month = 1;
    date1->year = 1;
    list->surname = "kek";
    list->name = "lul";
    list->fathersname = "uwu";
    list->dob = date1;
    
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    struct Date* date2 = (struct Date*)malloc(sizeof(struct Date));
    date2->day = 3;
    date2->month = 2;
    date2->year = 1;
    node->surname = "pff";
    node->name = "brr";
    node->fathersname = "grr";
    node->dob = date2;
    node->next = NULL;
    list->next = node;
    
    struct Date* fdate = (struct Date*)malloc(sizeof(struct Date));
    fdate->day = 1;
    fdate->month = 2;
    fdate->year = 3;
    
    EXPECT_EQ(listSearch(list, fdate), 0);
}