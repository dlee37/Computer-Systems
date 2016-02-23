//Daniel Lee
//calendar.c

#include <stdio.h>

void main() {
	int numDays, start, currentDay;

	printf("Enter number of days in a month: ");
	scanf("%d", &numDays);
	printf("Enter starting day of the week (1=Sun, 7=Sat): ");
	scanf("%d", &start);
	
	//does printing here
	beginSpace(start);

	for (currentDay = 1; currentDay <= numDays; currentDay++) {
		checkFullWeek(start);
		start++;
		//printf("1");
		printf("%d\t",currentDay);
	}
	printf("\n");
}

void beginSpace(int start) {
	int i;
	
	for (i = 1; i < start; i++) {
		printf("\t");
	}
}

void checkFullWeek(int start) {
	if ((start-1)%7 == 0) {
		printf("\n");
	}
}
