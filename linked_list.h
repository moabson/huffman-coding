/*
 * linked_list.h
 *
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

typedef struct linkedList LinkedList;

struct node {
	char bit;

	struct node *nextNode;
};

struct linkedList {
	Node *first;
	int length;
};

LinkedList* LinkedList_createEmpty();

void LinkedList_insert(LinkedList *linkedList, char bit);

void LinkedList_deleteFirst(LinkedList *linkedList);

void LinkedList_print(LinkedList *linkedList);

#endif /* LINKED_LIST_H_ */
