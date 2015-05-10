/*
 * frequency_queue.h
 *
 */

#ifndef FREQUENCY_QUEUE_H_
#define FREQUENCY_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_node.h"

typedef struct frequencyQueue FrequencyQueue;

struct frequencyQueue {
	HuffmanNode *first;
	int length;
};

FrequencyQueue* FrequencyQueue_createEmpty();

FrequencyQueue* FrequencyQueue_create(char *str);

int FrequencyQueue_isEmpty(FrequencyQueue *frequencyQueue);

void FrequencyQueue_insert(FrequencyQueue *frequencyQueue, HuffmanNode *huffmanNode, int frequency);

HuffmanNode* FrequencyQueue_get(FrequencyQueue *frequencyQueue);

void FrequencyQueue_print(FrequencyQueue *frequencyQueue);


#endif /* FREQUENCY_QUEUE_H_ */
