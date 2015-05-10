/*
 * frequency_queue.c
 *
 */

#include "frequency_queue.h"

#define MAX 256

FrequencyQueue* FrequencyQueue_createEmpty() {
	FrequencyQueue *frequencyQueue = (FrequencyQueue *) malloc(sizeof(FrequencyQueue));

	frequencyQueue->first = NULL;
	frequencyQueue->length = 0;

	return frequencyQueue;
}

FrequencyQueue* FrequencyQueue_create(char *str) {
	FrequencyQueue *frequencyQueue = FrequencyQueue_createEmpty();

	int freq[MAX] = {0};
	unsigned char character;
	int i;

	LOG_INFO("loading FrequencyQueue")

	for(i = 0; i < strlen(str); i++) {
		character = str[i];

		freq[(int) character]++;
	}

	for(i = 0; i < MAX; i++) {
		if(freq[i] > 0) {
			character = (char) i;

			HuffmanNode *newHuffmanNode = HuffmanNode_createLeaf(character, freq[character]);

			FrequencyQueue_insert(frequencyQueue, newHuffmanNode, newHuffmanNode->frequency);
		}
	}

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
		LOG_WARN("FrequencyQueue_get: FrequencyList is empty")

		return NULL;
	}
}

void FrequencyQueue_print(FrequencyQueue *frequencyQueue) {
	if(!FrequencyQueue_isEmpty(frequencyQueue)) {
		LOG_INFO("priting FrequencyQueue")

		HuffmanNode *current = frequencyQueue->first;

		printf("~ ");

		while(current != NULL) {
			printf("[%c:%d] -> ", current->character, current->frequency);

			current = current->nextHuffmanNode;
		}

		printf("\n");
	} else {
		LOG_WARN("priting FrequencyQueue: FrequencyQueue is empty!")
	}
}
