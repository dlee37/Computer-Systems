#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_THREADS 100000

//this program will find the index of ANY occurance, not the first or last. keep this in mind
//if you want faster, increase max threads. mobydick will take a very long time if
//there are a small number of threads (100 is very slow on mobydick)
//the third argument cannot be too high or else segmentation fault will occur (no higher than around 900000)

char *fullText;
char *findWord;
int *searchedIndices;
int textlength = 0;
int found;
int foundIndex;
int length;
int wordlen;
int searchIndex = 0;
int numthreads = 0;

pthread_mutex_t lock;

void *findingword(void *arg);
void printResult();
void freeAll();

int main(int argc, char *argv[]) {
	int i;
	int amountofChars;
	if (argc != 3) {
		printf("Please only type in the word being searched, followed by a space, followed by the length of the array.\n");
		printf("The program will now exit\n");
		return;
	}
	pthread_t tid[MAX_THREADS];
	argv++;
	wordlen = strlen(*argv) + 1;
	findWord = (char *) malloc(wordlen * sizeof(char));
	sscanf(*argv,"%s",findWord); //this initializes the word that is being searched
	wordlen--; //take account that this will not be used as a string for the rest of the time, still had the '\0' character
	argv++;
	sscanf(*argv,"%d",&length);
	fullText = (char *) malloc(length * sizeof(char)); //this initializes the entire thread array
	int searchindexlen = length - wordlen; //printf("%d\n",searchindexlen);
	searchedIndices = (int *) malloc(searchindexlen * sizeof(int)); //this initializes an array for indexes that were already searched
	pthread_mutex_init(&lock,NULL);
	//printf("wordlen is: %d\n",wordlen);
	int index = 0;
	while (index < length) { //scans every character until it reaches EOF or has run out of max length
		int status = getchar();
		if (status == EOF) {
			break;
		}
		fullText[index] = (char) status;
		if (index <= searchindexlen) {
			searchedIndices[index] = -1;
		}
		textlength++;
		index++;
	}

	//printf("%c\n",fullText[99998]);

	for (i = 0; i < MAX_THREADS; i++) {
		if (i > textlength - wordlen) {
			break;
		}

		else if (i > index || found == 1) {
			break;
		}
		//printf("%d\n",i);
		pthread_create(&tid[i],NULL,findingword,(void *) i); //each thread is assigned an index to search.
		//printf("%d\n",i);
		numthreads++;
	}

	for (i = 0; i < numthreads; i++) {
		pthread_join(tid[i],NULL);
	}
	printResult();
	freeAll();
}

void *findingword(void *arg) { //this function only searches as long as the word is. IF not found, it adds itself to the number of threads there are, 
							   //then keeps adding until it finds an index that hasnt been searched yet. 
	int index = (int) arg;
	//printf("%d\n",index);
	int temp = 0; //this keeps track of how many times the for loop search has been called to make the index go back to its original index 
				  //if the index is not found
	int i;

	if (found == 1) { //if found, don't do anything
		return;
	}
	//printf("%d\n",index);
	pthread_mutex_lock(&lock); //start of the critical section
	while (index <= textlength - wordlen) { //if index > wordlength - wordlen, the character search will go out of bounds
		//printf("Index is: %d\n",index);
		//printf("are we here?\n");
		while (alreadyChecked(index,searchedIndices)) {
			//printf("Already Searched Index is: %d\n",index);
			index += numthreads;
			if (index > textlength - wordlen) { //if index > textlength - wordlen, the character search will go out of bounds
				pthread_mutex_unlock(&lock);
				return;
			}
		}
		//printf("Index is: %d\n",index);
		if (index < 0) {
			pthread_mutex_unlock(&lock);
			return;
		}
		searchedIndices[searchIndex] = index;
		//printf("Searchindex is: %d\n",searchIndex);
		//printf("Value of searchindex is: %d\n",searchedIndices[searchIndex]);
		searchIndex++;
		for (i = 0; i < wordlen; i++) { //we check individual characters to determine a match
			if (fullText[index] == findWord[i] && i + 1 < wordlen) {
				index++;
				temp++;
			}
			else {
				break;
			}
		}
		if (fullText[index] == findWord[i]) { //if the for loop was successful and the last characters match
			//printf("did we make it?\n");
			found = 1;
			foundIndex = index - wordlen + 2;
			pthread_mutex_unlock(&lock); //end of the critical section
			return;
		}
		index -= temp;
		temp = 0;
		//printf("%c\n",fullText[index]);
	}
	pthread_mutex_unlock(&lock); //end of the critical section
}
void printResult() {
	printf("%d\n",foundIndex);
	if (found) {
		printf("The pattern occurs at character %d\n",foundIndex);
	}

	else printf("Pattern not found\n");
}

int alreadyChecked(int index) {
	int result = 0;
	int num;
	int i;
	for (i = 0; i < textlength-wordlen; i++) {
		num = searchedIndices[i];
		//printf("num is: %d\n",num);
		if (index == num) {
			//printf("Index is: %d\n",index);
			//printf("alreadychecked index is: %d\n",index);
			result = 1;
			break;
		}
		else if (num < 0) {
			//printf("is it here?\n");
			break;
		}
	}
	return result;
}

void freeAll() {
	free(fullText);
	free(findWord);
	free(searchedIndices);
}