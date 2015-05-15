/*
 * linked_list.c
 *
 */

#include "linked_list.h"

LinkedList* LinkedList_createEmpty() {
	LinkedList *linkedList = (LinkedList *) malloc(sizeof(LinkedList));

	linkedList->first = NULL;
	linkedList->length = 0;

	return linkedList;
}

void LinkedList_insert(LinkedList *linkedList, char bit) {
	Node *newNode = (Node *) malloc(sizeof(Node));

	newNode->bit = bit;

	newNode->nextNode = linkedList->first;
	linkedList->first = newNode;

	linkedList->length++;
}

void LinkedList_deleteFirst(LinkedList *linkedList) {
	Node *aux = linkedList->first;

	linkedList->first = linkedList->first->nextNode;

	linkedList->length--;

	free(aux);
}

void LinkedList_print(LinkedList *linkedList) {
	Node *aux = linkedList->first;

	while (aux != NULL) {
		printf("%c", aux->bit);

		aux = aux->nextNode;
	}

	printf("\n");
}
