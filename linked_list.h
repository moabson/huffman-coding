/*
 * linked_list.h
 *
 *  Created on: 14/05/2015
 *      Author: eduardo
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include <stdio.h>
#include <stdlib.h>


typedef struct list List;

struct list {
	char bit;
	struct list * next;
};

List * insert(List * list, char bit);

List * delete(List * first);

void print(List * list);

#endif /* LINKED_LIST_H_ */
