// bst.h:  Functions to support binary search trees

#ifndef BST_H
#define BST_H

struct bstnode {
	void *item;
	struct bstnode *left;
	struct bstnode *right;
};
typedef struct bstnode BSTnode;

// Create a new node having the specified item.
BSTnode *createNode(void *item);

// Search the tree rooted at node n for the node matching the specified item.
// If the item exists, return its node.  If not, return the node that would be its parent.
// The function "compare" compares items.
BSTnode *find(BSTnode *n, void *item, int compare(void *, void *));

// Insert an item into the tree rooted at node n.
// If the tree already has a node for that item, do nothing.
void insert(BSTnode *n, void *item, int compare(void *, void *));

#endif




