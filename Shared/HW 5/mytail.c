//Daniel Lee
//Assignment 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addToHeap(char *array[], char *line, int *indexPointer, int length);
void printAns(char *array[], int index, int length, int amt);
char *readaline(int length);

int main(int argc, char *argv[]) {

	int length;
	int index = 0;
	int *indexPointer = &index;
	int amt = 0;
	int i;

	if (argc == 1)
		length = 10;

	else {
		argv++;
		sscanf(*argv, "%d", &length);
	}

	char **array = (char **) malloc(length * sizeof(char *));

	while (1) {
		char *line = readaline(80);
		//printf("%s\n",line);

		if (line == NULL) {
			break;
		}

		amt++;
		addToHeap(array,line,indexPointer,length);
	}

	printAns(array, index, length, amt);

	for (i = 0; i < length; i++) {
		free(array[i]);
	}

	free(array);
}

void addToHeap(char *array[], char *line, int *indexPointer, int length) {

	int index = *indexPointer;
	if (index == length) {
		*indexPointer = 0;
		index = 0;
	}

	array[index] = line;
	(*indexPointer)++;
}

void printAns(char *array[], int index, int length, int amt) {

	int indexCounter = index;
	int count = 0;
	int i;

	if (amt < length) {

		for (i = 0; i < amt; i++) {
			printf("%s", array[i]);
		}
	}

	else {

		for (i = 0; i < length; i++) {

			if (indexCounter == length) {
				indexCounter = 0;
			}

			printf("%s\n", array[indexCounter]);
			indexCounter++;
		}
	}

	printf("\n");
}

char *readaline(int length) {

	char *store = (char *) malloc(length * sizeof(char));
	char *string = fgets(store, length, stdin);

	if (string == NULL) {
		free(store);
		return NULL;
	}

	int len = strlen(string);
	//printf("%s",string);
	if (string[len-1] == '\n')
		string[len-1] = '\0';

	return string;
}
