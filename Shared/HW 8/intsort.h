// intsort.h: definitions for the intsort program

#ifndef INTSORT_H
#define INTSORT_H

struct intnode {
	int item;
	struct intnode *next;
};
typedef struct intnode IntNode;

// create a node
IntNode *createNode(int val);

// insert a node into the chain, in sorted order
void insert(IntNode *header, int val);

// print the values stored in the chain of nodes
void printAll(IntNode *header);

#endif

