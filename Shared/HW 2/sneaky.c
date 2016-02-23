//Daniel Lee
//Assignment 2

#include <stdio.h>
void f();

int main() {
    printf("In main...\n");
    char c = 'A';
    int n = 123;
    f();
    printf("Back in main.\n");
    printf("%d%c\n", n, c);
}

void f() {
    printf("In f...\n");
    // add your code here
	int x = 666;
	char d = 'B';
	int *p = &x + 14;
	/*
	when looking, the address between the function f variable, they were always 0x38 apart, or 56 in decimal, apart.
	In int, that is 56/4, or 13 addresses apart, and for char it was 56.
	*/
	char *q = &d + 56;
	*p = x;
	*q = d;
}
