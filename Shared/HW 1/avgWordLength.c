//Daniel Lee
//Assignment 1

#include <stdio.h>
#include <ctype.h>

int main() {
	int lineCount = 0;
	int numLines = 0;
	int numChars = 0;
	int numWords = 0;
	int totalWordLength = 0;
	int isWord;
	float avgLength;

	printf("Enter text.  Use an empty line to stop.\n");
  
	while (1) {
	    int ic = getchar();
		//printf("%d\n",numWords);
	    if (ic < 0)    //EOF encountered
	        break;
	    char c = (char) ic;
		if (!isspace(c)) {
			totalWordLength++;
			if (isWord == 0) {
				numWords++;
				isWord = 1;
			}
		}
		if (isspace(c)) {
			isWord = 0;
		}
	    if (c == '\n' && lineCount == 0) //Empty line
	        break;
	    numChars++;
	    if (c == '\n') {
	        numLines ++;
	        lineCount = 0;
	    }
	    else
	        lineCount ++;
	}
	//printf("%d\n", totalWordLength);
	printf("Your text has %d lines and %d characters.\n", numLines, numChars);
	avgLength = (float)totalWordLength/(float)numWords;
	//printf("Average length is: %.2f\n", avgLength);
	printf("Your text has %d words, with an average length of %.2f.\n", numWords, avgLength);
}
