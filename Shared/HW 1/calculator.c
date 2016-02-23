//Daniel Lee
//Assignment 1

#include <stdio.h>

float processPlus(float amt, float val) {
	//printf("Plus");
	return amt + val;
}

float processMinus(float amt, float val) {
	//printf("Minus");
	return amt - val;
}

float processTimes(float amt, float val) {
	//printf("Times");
	return amt * val;
}

float processDivide(float amt, float val) {
	//printf("Divide");
	return amt/val;
}

float processPrint(float amt) {
	printf("%f\n", amt);
	return amt;
}

float processClear() {
	//printf("Clear");
	return 0;
}

int takesNoArgs(char op) {
	if (op == 'C' || op == '=') {
		//printf("Takes args\n");
		return 1;
	}
	//printf("Does not take args\n");
	return 0;
}

float processOp(float amt, char op, float val) {
	if (op == '+') {
		return processPlus(amt,val);
	}

	else if (op == '-') {
		return processMinus(amt,val);
	}

	else if (op == '*') {
		return processTimes(amt,val);
	}

	else if (op == '/') {
		return processDivide(amt,val);
	}
	
	else if (op == '=') {
		return processPrint(amt);
	}

	else if (op == 'C') {
		return processClear();
	}

	else {
		printf("Bad Operator\n");
		return amt;
	}
}

void main() {
	float amt = 0.0F;
	char op;
	float val;
	
	printf("CS 2271 Calculator\n");
	
	while (1) {

		int ic = getchar();
		if (ic < 0) break;
		op = (char) ic;
		if (op == 'Q') break;

		//printf("%c\n",op);

		if (takesNoArgs(op) == 1) {
			//printf("Hello\n");
			val = 0.0F;
		}
		
		else {
			scanf("%f", &val);
		}
		
		amt = processOp(amt, op, val);
		int temp = getchar();
		char t = (char) temp;
		if (t != '\n') {
			while ((char) getchar() != '\n') {
				int temp = getchar();
				char t = (char) temp;
			}
		}
		//printf("Hello\n");
	}

	printf("Thank you and good bye!\n");
}
