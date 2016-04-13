//Daniel Lee

#include <stdio.h>
#include <stdlib.h>
#include "gc.h"

void gc();
void mark(void *p);
void sweep();
void *stackBottom();
int inHeap(int *p);
int isMarked(int *p);
int *getHeader(int *p) ;

void gc() {
	int *end = (int *) stackBottom();
	int x = 3;
	int *p = &x;
	//printf("address of end is: %p\n",end);
	//printf("address of p + 1 is: %p\n",p+1);
	while (p != end) {
		if (inHeap(p)) {
			mark(p);
		}
		//printf("Address of p is: %p\n",p);
		p++;
	}
	//printf("Address of first block is: %p\n",firstBlock());
	//printf("Address of last block is: %p\n",lastBlock());
	sweep();
}

void mark(void *p) {
	int *val = (int *) p;
	if (!inHeap(val)) {
		return;
	}
	int *pointer = getHeader(p);
	if (isMarked(pointer)) return;
	if (inHeap(val)) {
		//printf("%p\n",pointer);
		*pointer = (*pointer) + 2;
		while (pointer != nextBlock(pointer)) {
		pointer++;
		if (inHeap(pointer))
			mark(pointer);
		}
	}
}

void sweep() {
	int *ptr = firstBlock();
	while (ptr != lastBlock()) {
		if (isMarked(ptr)) {
			*ptr = (*ptr) - 2;
		}

		else {
			if (isAllocated(ptr)) {
				(*ptr)--;
			}
		}
		ptr = nextBlock(ptr);
	}
	coalesce();
}

void *stackBottom() {
	unsigned long bottom;
    FILE *statfp = fopen("/proc/self/stat", "r");
    fscanf(statfp,
           "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
           "%*u %*u %*u %*u %*u %*u %*d %*d "
           "%*d %*d %*d %*d %*u %*u %*d "
           "%*u %*u %*u %lu", &bottom);
    fclose(statfp);
	return (void *) bottom;
}

int inHeap(int *p) {
	//printf("Address is: %p\n",p);
	if ((*p) >= firstBlock()) {
		if ((*p) <= lastBlock()) {
			return 1;
		}
	}
	return 0;
}

int isMarked(int *p) {
	if ((*p)%4 == 3) {
		return 1;
	}

	return 0;
}

int *getHeader(int *p) {
	int *next = firstBlock();
	while (next != lastBlock()) {
		if (*p >= next) {
			if (*p <= nextBlock(next)) {
				return next;
			}
		}
		next++;
	}
}
