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

/**
  * Cria fila de prioridade dos caracteres vazia, com ponteiro apontando para NULL e
  * tamanho 0.
  *
  * @return ponteiro para FrequencyQueue vazia
  */

FrequencyQueue* FrequencyQueue_createEmpty();

/**
  * Lê os caracteres do arquivo e monta a fila de frequencia.
  *
  * @param file - ponteiro para o arquivo aberto
  * @return ponteiro para FrequencyQueue preenchida
  */

FrequencyQueue* FrequencyQueue_create(FILE *file);

/**
  * Verifica se a fila de frequencia esta vazia.
  *
  * @param frequencyQueue - ponteiro para fila de prioridade com os caracteres
  * @return 1 (true) se vazia ou 0 (false) caso contrário
  */

int FrequencyQueue_isEmpty(FrequencyQueue *frequencyQueue);

/**
  * Insere o caractere na fila de acordo com sua frequência. Os que menos se
  * repetem ficam no inicio da fila.
  *
  * @param frequencyQueue - ponteiro para fila de prioridade com os caracteres
  * @param huffmanNode - ponteiro para nó de huffman a ser inserido
  * @param frequency - inteiro com a frequência do nó para saber sua prioridade
  * @return void
  */

void FrequencyQueue_insert(FrequencyQueue *frequencyQueue, HuffmanNode *huffmanNode, int frequency);

/**
  * Remove o primeiro nó da fila de frequencia e retorna-o.
  *
  * @param frequencyQueue - ponteiro para fila de prioridade com os caracteres
  * @return ponteiro para nó de huffman se a fila não está vazia ou NULL caso contrário
  */

HuffmanNode* FrequencyQueue_get(FrequencyQueue *frequencyQueue);

/**
  * Imprime a fila de prioridade com os caracteres.
  *
  * @param frequencyQueue - ponteiro para fila de prioridade com os caracteres
  * @return void
  */

void FrequencyQueue_print(FrequencyQueue *frequencyQueue);

#endif /* FREQUENCY_QUEUE_H_ */
