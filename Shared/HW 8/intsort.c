#include <stdio.h>
#include <stdlib.h>
#include "intsort.h"


IntNode *createNode(int val);
void insert(IntNode *header, int val);
void printAll(IntNode *header);

IntNode *first;

int main() {
	int val;
	printf("Enter some numbers, ending with -1: ");
	while (1) {
		scanf("%d",&val);
		if (val == -1) {
			break;
		}
		IntNode *node = createNode(val);
		//printf("%d\n",val);
		if (first == NULL) {
			first = node;
		}
		//printf("first is: %d\n",first -> item);
		insert(node,val);
	}

	printAll(first);
}

IntNode *createNode(int val) {
	IntNode *node = (IntNode *) malloc(sizeof(IntNode));
	node -> item = val;
	node -> next = NULL;
	return node;
}

void insert(IntNode *header, int val) {
	//printf("Header is: %d\n",header -> item);
	IntNode *node = first;
	IntNode *previous = first;
	while (node -> next != NULL) {
		if (node -> item > header -> item && previous != first) {
			header -> next = node;
			previous -> next = header;
			return;
		}

		else if (node -> item > header -> item && previous == first) {
			header -> next = node;
			first = header;
			return;
		}
		previous = node;
		node = node -> next;
	}
	if (node -> item > header -> item && previous == first) {
		header -> next = node;
		first = header;
	}

	else if (node -> item > header -> item && previous != first) {
		previous -> next = header;
		header -> next = node;
	}

	else {
		node -> next = header;
		header -> next = NULL;
	}
	//printf("header is: %d\n",header->item);
}

void printAll(IntNode *header) {
	printf("Here are the numbers in sorted order, ending with -1: ");
	while (header -> next != NULL) {
		printf("%d ",header -> item);
		header = header -> next;
	}
	printf("%d",header -> item);
	printf("\n");
}