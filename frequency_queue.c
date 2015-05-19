/*
 * frequency_queue.c
 *
 */

#include "frequency_queue.h"

#define MAX 256

/*
 * Cria a fila de frequencia vazia.
 * @retorna ponteiro frequencyQueue.
 */
FrequencyQueue* FrequencyQueue_createEmpty() {
	FrequencyQueue *frequencyQueue = (FrequencyQueue *) malloc(sizeof(FrequencyQueue));

	frequencyQueue->first = NULL;
	frequencyQueue->length = 0;

	return frequencyQueue;
}

/*
 * Le os caracteres do arquivo e monta a fila de frequencia.
 * @ Recebe arquivo file.
 * @ Retorna ponteiro frequencyQueue.
 */
FrequencyQueue* FrequencyQueue_create(FILE *file) {
	FrequencyQueue *frequencyQueue = FrequencyQueue_createEmpty();

	int freq[MAX] = {0};
	unsigned char character;
	int i;

	LOG_INFO("loading FrequencyQueue")

	while((character = fgetc(file)) != 255) {
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

/*
 * Verifica se a fila de frequencia esta vazia.
 * @ Recebe ponteiro fq.
 * @ Retorna TRUE se vazia, FALSE caso contrário.
 */
int FrequencyQueue_isEmpty(FrequencyQueue *fq) {
	return (fq->first == NULL);
}

void FrequencyQueue_insert(FrequencyQueue *frequencyQueue, HuffmanNode *huffmanNode, int frequency) {
	if(FrequencyQueue_isEmpty(frequencyQueue) || frequency < frequencyQueue->first->frequency) {
		huffmanNode->nextHuffmanNode = frequencyQueue->first;
		frequencyQueue->first = huffmanNode;
	} else {
		HuffmanNode *current = frequencyQueue->first;

		while((current->nextHuffmanNode != NULL) && (current->nextHuffmanNode->frequency < frequency)) {
			current = current->nextHuffmanNode;
		}

		huffmanNode->nextHuffmanNode = current->nextHuffmanNode;
		current->nextHuffmanNode = huffmanNode;
	}

	frequencyQueue->length++;
}
/*
 * Remove o primeiro elemento da fila de frequencia e retorna-o.
 *@ Recebe ponteiro frequencyQueue.
 *@ Retorna ponteiro huffmanNode se frequencyQueue não está vazia, NULL caso contrário.
 */
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
/*
*Imprime a fila de frequencia.
*@ Recebe ponteiro frequencyQueue.
*/
void FrequencyQueue_print(FrequencyQueue *frequencyQueue) {
	if(!FrequencyQueue_isEmpty(frequencyQueue)) {
		LOG_INFO("priting FrequencyQueue")

		HuffmanNode *current = frequencyQueue->first;

		printf("~ ");

		while(current != NULL) {
			printf("[%d:%d] -> ", current->character, current->frequency);

			current = current->nextHuffmanNode;
		}

		printf("\n");
	} else {
		LOG_WARN("priting FrequencyQueue: FrequencyQueue is empty!")
	}
}
