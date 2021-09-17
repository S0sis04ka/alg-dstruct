#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

int main(){

	const int maxLetters = 50;

	FILE *fin = fopen("../input.txt", "r");

	if (fin == NULL) {
		printf("Can't read file\n");
		return 0;
	}

	struct Node* list = NULL;

	while(!feof(fin)) {
		char* surname = (char*)malloc(sizeof(char) * maxLetters);
		if (surname == NULL) {
			return 0;
		}
		char* name = (char*)malloc(sizeof(char) * maxLetters);
		if (name == NULL) {
			return 0;
		}
		char* fathersname = (char*)malloc(sizeof(char) * maxLetters);
		if (fathersname == NULL) {
			return 0;
		}
		struct Date* dob = (struct Date*)malloc(sizeof(struct Date));
		if (dob == NULL) {
			return 0;
		}

		fscanf(fin, "%s%s%s", surname, name, fathersname);
		fscanf(fin, "%d.%d.%d", &dob->day, &dob->month, &dob->year);

		listAdd(&list, surname, name, fathersname, dob);
	}

	fclose(fin);

	printList(list);
 
	struct Date* date = (struct Date*)malloc(sizeof(struct Date));
    printf("Enter date for search:\n");
	fscanf(stdin, "%d.%d.%d", &date->day, &date->month, &date->year);
	listSearch(list, date);

	free(list);

	return 0;
}