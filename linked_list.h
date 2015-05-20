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

/*
*Cria lista encadeada vazia, com ponteiro avontando para VAZIO e tamanho 0.
*@Retorna ponteiro linkedList.
*/
LinkedList* LinkedList_createEmpty();

/*
*Insere um nó na lista encadeada.
*@Recebe ponteiro linkedList e caractere bit.
*/
void LinkedList_insert(LinkedList *linkedList, char bit);

/*
*Deleta o primeiro nó da lista encadeada.
*@Recebe ponteiro linkedList.
*/
void LinkedList_deleteFirst(LinkedList *linkedList);

/*
*Imprime a lista encadeada.
*@Recebe ponteiro linkedList.
*/
void LinkedList_print(LinkedList *linkedList);

#endif /* LINKED_LIST_H_ */
