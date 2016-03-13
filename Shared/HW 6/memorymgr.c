#include <stdio.h>
#include <stdlib.h>
#include "memorymgr.h"

void initmemory(int amt);
void *myalloc(int amt);
void myfree(void *p);
void coalesce();
void printallocation();
int *firstBlock();
int *lastBlock();
int isAllocated(int *p);
int *nextBlock(int *p);
void createNewHeader(int *p, int amt);

int totalsize;
int *first;
int *last;

void initmemory(int amt) {
	int total = 8; //header on 1st block and header for sentinel block is total of 8 bytes
	int space = amt;
	void *current;
	while (1) {
		if (space%4 == 0) {
			if (space%8 == 0) {
				space++;
				continue;
			}
			else {
				break;
			}
		}
		space++;
	}
	total += space;
	while (total%8 != 0) {
		total++;
	}

	first = (int *) malloc(total);
 	last = (int *) first + 1 + (space/4); //have to account for header, so add 1
 	//printf("%p\n",first);
 	//printf("%p\n",last);
	totalsize = space + 4; //have to account for the first header
	*first = totalsize;
	//printf("%d\n", *first);
	*last = 0;
}

void *myalloc(int amt) {
	int *p = first;
	void *result;
	int actual = amt + 4; //header is always 4 bytes
	if (amt > totalsize) return NULL;
	while (p != lastBlock()) {
		if (*p >= actual && !isAllocated(p)) {
			createNewHeader(p,actual);
			result = (void *) p + 4;
			return result;
		}
		else {
			p = nextBlock(p);
		}
	}
	return NULL;
}

void myfree(void *p) {
	//printf("%p\n",p);
	int *s = (int *) p - 1;
	//printf("%p\n",s);
	(*s)--;
}

void coalesce() {
	int *p = first;
	int *next = nextBlock(p);
	while (next != lastBlock()) {
		if (!isAllocated(p) && !isAllocated(next)) {
			*p += *next;
		}
		else {
			p = nextBlock(p);
		}
		next = nextBlock(p);
	}
}

void printallocation() {
	int *p = first;
	int num = 0;
	while (p != lastBlock()) {
		int length;
		if (isAllocated(p)) {
			length = (*p) - 1;
			printf("Block %d: size: %d\t", num, length);
			printf("allocated\n");
		}
		else {
			length = *p;
			printf("Block %d: size: %d\t", num, length);
			printf("unallocated\n");
		}
		p = nextBlock(p);
		num++;
	}
}

int *firstBlock() {
	return first;
}

int *lastBlock() {
	return last;
}

int isAllocated(int *p) {
	if ((*p)%8 != 0) {
		return 1;
	}
	return 0;
}

int *nextBlock(int *p) {
	int size = *p;
	if (isAllocated(p)) size--;
	int *next = p;
	next = next + (size/4);
	return next;
}

void createNewHeader(int *p, int amt) {
	int size = amt;
	int blocksize = *p;
	while (size%8 != 0) {
		size++;
	}
	*p = size + 1;
	int *next = p + (size/4);
	*next = blocksize - size;
}
