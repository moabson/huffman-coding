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
#include "debug.h"

typedef struct frequencyQueue FrequencyQueue;

struct frequencyQueue {
	HuffmanNode *first;
	int length;
};

/*
 *Cria a fila de frequencia vazia, com ponteiro apontando para VAZIO e tamanho 0.
 *@retorna ponteiro frequencyQueue.
 */
FrequencyQueue* FrequencyQueue_createEmpty();

/*
*Le os caracteres do arquivo e monta a fila de frequencia.
*@ Recebe arquivo file.
*@ Retorna ponteiro frequencyQueue.
*/
FrequencyQueue* FrequencyQueue_create(FILE *file);

/*
* Verifica se a fila de frequencia esta vazia.
*@ Recebe ponteiro frequencyQueue.
*@ Retorna TRUE se vazia, FALSE caso contrário.
*/
int FrequencyQueue_isEmpty(FrequencyQueue *frequencyQueue);

/*
*Insere o caractere na fila de acordo com sua frequencia.
*@Recebe o ponteiro para fila frequencyQueue, ponteiro para o nó huffmanNode, e a frequencia.
*/
void FrequencyQueue_insert(FrequencyQueue *frequencyQueue, HuffmanNode *huffmanNode, int frequency);

/*
*Remove o primeiro nó da fila de frequencia e retorna-o.
*@ Recebe ponteiro frequencyQueue.
*@ Retorna ponteiro huffmanNode se frequencyQueue não está vazia, NULL caso contrário.
*/
HuffmanNode* FrequencyQueue_get(FrequencyQueue *frequencyQueue);

/*
*Imprime a fila de frequencia.
*@ Recebe ponteiro frequencyQueue.
*/
void FrequencyQueue_print(FrequencyQueue *frequencyQueue);

#endif /* FREQUENCY_QUEUE_H_ */
