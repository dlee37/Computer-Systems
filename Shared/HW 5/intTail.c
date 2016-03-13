//Daniel Lee
//Assignment 5

#include <stdio.h>
#include <stdlib.h>

void addToHeap(int array[], int val, int *indexPointer, int length);
void printAns(int array[], int index, int length, int amt);

int main(int argc, char *argv[]) {

	int length;
	int index = 0;
	int *indexPointer = &index;
	int amt = 0;

	if (argc == 1) {
		length = 10;
	}

	else {
		argv++;
		sscanf(*argv,"%d",&length);
	}

	//printf("%d\n",length);
	int *array = (int *) malloc(length * sizeof(int));

	while (1) {

		int val;
		scanf("%d", &val);

		if (val == -1) {
			break;
		}

		amt++;
		addToHeap(array,val,indexPointer,length);
	}

	printAns(array, index, length, amt);
	free(array);
}


void addToHeap(int array[], int val, int *indexPointer, int length) {

	int index = *indexPointer;
	if (index == length) {
		*indexPointer = 0;
		index = 0;
	}

	array[index] = val;
	(*indexPointer)++;
}

void printAns(int array[], int index, int length, int amt) {

	int indexCounter = index;
	int count = 0;
	int i;

	if (amt < length) {
		printf("There are only %d numbers: ",amt);

		for (i = 0; i < amt; i++) {
			printf("%d ", array[i]);
		}
	}

	else {
		printf("Here are the last %d numbers: ", length);

		for (i = 0; i < length; i++) {

			if (indexCounter == length) {
				indexCounter = 0;
			}

			printf("%d ", array[indexCounter]);
			indexCounter++;
		}
	}
	printf("\n");
}
