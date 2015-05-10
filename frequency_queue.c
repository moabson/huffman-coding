/*
 * frequency_queue.c
 *
 */

#include "frequency_queue.h"

FrequencyQueue* FrequencyQueue_create() {
	FrequencyQueue *frequencyQueue = (FrequencyQueue *) malloc(sizeof(FrequencyQueue));

	frequencyQueue->first = NULL;
	frequencyQueue->length = 0;

	return frequencyQueue;
}

int FrequencyQueue_isEmpty(FrequencyQueue *fq) {
	return (fq->first == NULL);
}

void FrequencyQueue_insert(FrequencyQueue *frequencyQueue, HuffmanNode *huffmanNode, int frequency) {
	if(FrequencyQueue_isEmpty(frequencyQueue) || frequency < frequencyQueue->first->frequency) {
		huffmanNode->nextHuffmanNode = frequencyQueue->first;
		frequencyQueue->first = huffmanNode;
	} else {
		HuffmanNode *current = frequencyQueue->first;

		while((current->nextHuffmanNode != NULL) && (frequency < current->frequency)) {
			current = current->nextHuffmanNode;
		}

		huffmanNode->nextHuffmanNode = current->nextHuffmanNode;
		current->nextHuffmanNode = huffmanNode;
	}

	frequencyQueue->length++;
}

HuffmanNode* FrequencyQueue_get(FrequencyQueue *frequencyQueue) {
	if(!FrequencyQueue_isEmpty(frequencyQueue)) {
		HuffmanNode *huffmanNode = frequencyQueue->first;

		frequencyQueue->first = frequencyQueue->first->nextHuffmanNode;

		frequencyQueue->length--;

		return huffmanNode;
	} else {
		return NULL;
	}
}

void FrequencyQueue_print(FrequencyQueue *frequencyQueue) {
	printf("[*] priting FrequencyQueue\n");

	if(!FrequencyQueue_isEmpty(frequencyQueue)) {
		HuffmanNode *current = frequencyQueue->first;

		while(current != NULL) {
			printf("[%c:%d] -> ", current->character, current->frequency);

			current = current->nextHuffmanNode;
		}

		printf("\n");

	}
}
