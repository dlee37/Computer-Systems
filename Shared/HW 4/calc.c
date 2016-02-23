//Daniel Lee
//Assignment 4

#include <stdio.h>

void pushValStack(int stack[], int *top, int value);
int popValStack(int stack[], int *top);
void pushOpStack(char *stack[], int *top, char *value);
char *popOpStack(char *stack[], int *top);
int doOperation(char *op, int a, int b);

int main(int argc, char *argv[]) {

	char *opstack[50];
	int valstack[50];
	int valTop = 0;
	int opTop = 0;
	int i;
	argv++;

	for (i = 1; i < argc; i++) {
		int val;

		//printf("%s\n", *argv);

		if (strcmp(*argv,"+") == 0 || strcmp(*argv,"x") == 0 || strcmp(*argv,"[") == 0) {
			//printf("first train\n");
			pushOpStack(opstack, &opTop, *argv);
		}

		else if (strcmp(*argv,"]") == 0) {
			//printf("second first train\n");

			while (1) {

				char *tempOp = popOpStack(opstack,&opTop);

				if (strcmp(tempOp,"[") == 0) {
					break;
				}

				int a = *(valstack + valTop - 1);
				int b = *(valstack + valTop - 2);
				int total = doOperation(tempOp, a, b);
				popValStack(valstack,&valTop);
				popValStack(valstack,&valTop);
				pushValStack(valstack,&valTop,total);
			}
		}

		else {
			sscanf(*argv,"%d", &val);
			pushValStack(valstack, &valTop, val);
		}

		argv++;
	}

	while (opTop != 0) {
		//printf("wtf\n");
		char *tempOp = popOpStack(opstack,&opTop);
		int a = *(valstack + valTop - 1);
		int b = *(valstack + valTop - 2);
		//printf("%d\n",a);
		//printf("%d\n",b);
		//printf("%s\n", tempOp);
		int total = doOperation(tempOp, a, b);
		//printf("wtf\n");
		popValStack(valstack,&valTop);
		//printf("wtf\n");
		popValStack(valstack,&valTop);
		//printf("wtf\n");
		//printf("%d\n",valTop);
		pushValStack(valstack,&valTop,total);
		//printf("wtf\n");
	}

	printf("The answer is: %d\n", *valstack); 
}

void pushValStack(int stack[], int *top, int value) {
	//printf("fourth first train\n");
	int *addStack = stack + *top;
	*addStack = value;
	//printf("%d\n", *addStack);
	(*top)++;
}

int popValStack(int stack[], int *top) {
	//printf("fifth first train\n");
	(*top)--;
}

void pushOpStack(char *stack[], int *top, char *value) {
	//printf("sixth first train\n");
	char **addStack = stack + *top;
	*addStack = value;
	(*top)++;
}

char *popOpStack(char *stack[], int *top) {
	//printf("seventh first train\n");
	(*top)--;
	char **ans = stack + *top;
	//printf("%s\n",*ans);
	return *ans;
}

int doOperation(char *op, int a, int b) {
	//printf("eighth first train\n");
	if (strcmp(op,"+") == 0) {
		return a+b;
	}

	else if (strcmp(op,"x") == 0) {
		//printf("ninth first train\n");
		return a*b;
	}

	//printf("eff my life");
	return 0;
}