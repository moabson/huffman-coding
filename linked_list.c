/*
 * linked_list.c
 *
 *  Created on: 14/05/2015
 *      Author: eduardo
 */

#include "linked_list.h"

List * insert(List * first, char bit) {
	List * list = (List*) malloc(sizeof(List));

	list->bit = bit;
	list->next = first;

	return list;

}

List * delete(List * first) {
	List * aux = first;

	first = first->next;
	free(aux);
	return first;
}

void print(List * list) {

	List * aux = list;

	while (aux != NULL) {
		printf("%c", aux->bit);
		aux = aux->next;
	}
	printf("\n");
}
