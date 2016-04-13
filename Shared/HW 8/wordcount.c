#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"

typedef struct wordcount {
	char word[80];
	int count;
} WordCount;

WordCount *createWordCount(char word[]);
int wordCompare(void *w1, void *w2);
WordCount *createWordCount(char word[]);
WordCount *convertFromNode(BSTnode *n);
void printAll();

WordCount *most;

int main() {
	char word[80];
	BSTnode *first;
	while (1) {
		int x = scanf("%s",word);
		//printf("Word is: %s\n",word);

		if (x == EOF) break;

		WordCount *wc = createWordCount(word);

		if (first == NULL) {
			first = createNode(wc);
			setTop(first);
			most = wc;
			continue;
		}
		
		BSTnode *n = find(first,wc,wordCompare);
		WordCount *w1 = convertFromNode(n);
		//printf("word in wordcount is: %s\n",w1->word);
		/* if (n->left == NULL && n->right != NULL) {
			BSTnode *node = n->right;
			WordCount *w = convertFromNode(node);
			printf("right is: %s\n",w->word);
		}

		if (n->left != NULL && n->right == NULL) {
			BSTnode *node = n->left;
			WordCount *w = convertFromNode(node);
			printf("right is: %s\n",w->word);
		}
		if (n->left != NULL && n->right != NULL) {
			BSTnode *node = n->left;
			BSTnode *node1 = n->right;
			WordCount *w = convertFromNode(node);
			WordCount *x = convertFromNode(node1);
			printf("left is: %s\n",w->word);
			printf("right is: %s\n",x->word);
		} */
		if (wordCompare(wc,w1) == 0) {
			(w1->count)++;
			if (w1->count > most->count) {
				most = w1;
			}
		}
		else {
			//printf("%d\n",wordCompare(n->item,wc));
			insert(n,wc,wordCompare);
		}
	}
	printf("\n");
	printAll();
}

int wordCompare(void *w1, void *w2) {
	WordCount *s1 = (WordCount *) w1;
	WordCount *s2 = (WordCount *) w2;
	//printf("different compare\n");
	int ans = strcmp(s1->word,s2->word);
	return ans;
}

WordCount *createWordCount(char word[]) {
	WordCount *wc = (WordCount *) malloc(sizeof(WordCount));
	strcpy(wc->word,word);
	wc->count=1;
	return wc;
}

WordCount *convertFromNode(BSTnode *n) {
	WordCount *wc = (WordCount *) n->item;
	return wc;
}

void printAll() {
	printf("The most frequent word is \"%s\", which appears %d times.\n",most->word,most->count);
}