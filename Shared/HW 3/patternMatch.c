//Daniel Lee
//Assignment 3

#include <stdio.h>

char *findmatch(char pattern[], char text[], int patternLength, int textLength);
int readline(char text[], int maxSize);
void printmessage(char *position, char text[], int patternLength, int textLength);

int main() {

	char text[40], pattern[40], *position;
	int textlength, patternlength;
	
	printf("Enter text: ");
	textlength = readline(text, 40);
	printf("Enter pattern: ");
	//printf("text is: %s\n", text);
	patternlength = readline(pattern, 40);
	printf("pattern is: %c\n", *pattern);
	position = findmatch(pattern, text, patternlength, textlength);
	printmessage(position, text, patternlength, textlength);
}

int readline(char text[], int maxSize) {
	
	int size = 0;
	int index;

	for (index = 0; index < maxSize; index++) {
		int x = getchar();
		char c = (char) x;
		//printf("%d\n", index);

		if (c == '\n') break;

		size++;
		*text = c;
		text++;
	}

	return size;
}

char *findmatch(char pattern[], char text[], int patternLength, int textLength) {
	//printf("%p\n",&pattern); //difference is 44 in hex, or 68 in decimal
	//printf("The address of text in findmatch is: %p\n",&text);  //difference is 18 in hex, or 24 in decimal
	//printf("pattern is: %c\n", *pattern);
	//printf("text is: %c\n", *text);

	int textIndex;
	int patternIndex;
	char *ans;
	char *t = text;
	char *p = pattern;
	printf("%c\n", *p);

	if (patternLength > textLength) return NULL;

	for (textIndex = 0; textIndex < textLength; textIndex++) {

		for (patternIndex = 0; patternIndex < patternLength; patternIndex++) {

			//printf("%c\n", *p);

			if (*p == '?' && patternIndex == patternLength - 1) {
				//printf("one\n");
				ans = t - patternLength + 1;
				return ans;
			}

			else if (*p == *t && patternIndex == patternLength - 1) {
				//printf("two\n");
				ans = t - patternLength + 1;
				return ans;
			}

			else if (*p == '?') {
				//printf("three\n");
				p++;
				t++;
			}

			else if (*t == *p) {
				//printf("four\n");
				p++;
				t++;
			}

			else if (*t != *p) {
				//printf("five\n");
				p -= patternIndex;
				t -= patternIndex;
				//printf("%c\n", *p);
				break;
			}
		}
	
		t++;
	}

	return NULL;
}

void printmessage(char position[], char text[], int patternLength, int textLength) {

	//printf("The address of text in printmessage is: %p\n", &text);
	//printf("The address of position in printmessage is: %p\n", position)

	if (position == NULL) {
		printf("no match\n");
		return;
	}
	
	int textIndex = 1;
	
	while (position != text) {

		text++;
		textIndex++;
	}

	//printf("position is: %c\n", *position);

	printf("The pattern was found at char %d. ", textIndex);

	text += patternLength;
	int index;
	printf("The remaining characters are: ");

	for (index = textIndex + patternLength - 1; index < textLength; index++) {
		
		printf("%c", *text);
		text++;
	}

	printf("\n");
}