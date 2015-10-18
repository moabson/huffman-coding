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

/**
* Cria uma lista encadeada vazia.
*
* @return ponteiro para LinkedList.
*
*/
LinkedList* LinkedList_createEmpty();

/**
* Insere um nó no final da lista.
*
* @param linkedList - ponteiro para lista.
* @param bit - caractere que representa um bit.
* @return void
*/
void LinkedList_insert(LinkedList *linkedList, unsigned char bit);

/**
* Apaga o primeiro nó da lista.
*
* @param linkedList - ponteiro para lista.
* @return void
*
*/
void LinkedList_deleteFirst(LinkedList *linkedList);

/**
* Imprime a lista.
*
* @param linkedList - ponteiro para lista.
* @return void
*
*/
void LinkedList_print(LinkedList *linkedList);

#endif /* LINKED_LIST_H_ */
