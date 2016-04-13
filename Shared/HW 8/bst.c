#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTnode *createNode(void *item);
BSTnode *find(BSTnode *n, void *item, int compare(void *, void *));
void insert(BSTnode *n, void *item, int compare(void *, void *));
int compare(void *item1, void *item2);

BSTnode *top;

BSTnode *createNode(void *item)  {
	BSTnode *node = (BSTnode *) malloc(sizeof(BSTnode));
	node -> item = item;
	node->left = NULL;
	node->right = NULL;
	return node;
}

BSTnode *find(BSTnode *n, void *item, int compare(void *, void *)) {
	BSTnode *node = n;
	while (1) {

		if (node->left == NULL && node->right == NULL) break;

		if (compare(node->item,item) == 0) {
			//WordCount *wc = (WordCount *) node->item;
			//printf("word equal: %s\n",wc->word);
			return node;
		}

		else if (compare(node->item,item) > 0) {
			//printf("not\n");
			if (node->left == NULL) {
				//printf("end\n");
				//WordCount *wc = (WordCount *) node->item;
				//printf("word left: %s\n",wc->word);
				return node;
			}
			else 
				node = node->left;
		}

		else if (compare(node->item,item) < 0) {
			//printf("why is this happening\n");
			if (node->right == NULL) {
				//printf("end\n");
				//WordCount *wc = (WordCount *) node->item;
				//printf("word right: %s\n",wc->word);
				return node;
			}
			else 
				node = node->right;
		}
	}
	//printf("end\n");
	//WordCount *wc = (WordCount *) node->item;
	//printf("word null: %s\n",wc->word);
	return node;
}

void insert(BSTnode *n, void *item, int compare(void *, void *)) {
	BSTnode *node = n;
	if (compare(node->item,item) > 0) {
		//printf("insert left is working\n");
		node->left = createNode(item);
	}

	else if (compare(node->item,item) < 0) {
		//printf("insert right is working\n");
		node->right = createNode(item);
	}
	return;
}

BSTnode *getTop() {
	return top;
}

void setTop(BSTnode *n) {
	top = n;
}