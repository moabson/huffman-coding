/*
 * huffman_tree.h
 *
 */

#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency_queue.h"
#include "huffman_node.h"
#include "debug.h"
#include "linked_list.h"

#define MAX 256

typedef struct huffmanTree HuffmanTree;

struct huffmanTree {
	HuffmanNode *root;
	char *table[MAX];
	int number_nodes;
};

/**
* Cria árvore vazia.
*
* @return ponteiro para HuffmanTree.
*
*/
HuffmanTree* HuffmanTree_createEmpty();

/**
* Constrói árvore a partir da fila de prioridade com os caracteres.
*
* @param frequencyQueue - ponteiro para a fila de prioridadade com os caracteres e
* suas respectivas frequências em ordem crescente.
* @return ponteiro para HuffmanTree.
*/
HuffmanTree* HuffmanTree_build(FrequencyQueue *frequencyQueue);

/**
* Verifica se a árvore está vazia.
*
* @param huffmanTree - ponteiro para árvore.
* @return 1 (true) se vazia ou 0 (false) caso contrário.
*
*/
int HuffmanTree_isEmpty(HuffmanTree *huffmanTree);

/**
* Preenche tabela com o código de cada caractere na árvore.
*
* @param huffmanTree - ponteiro para árvore.
* @return void
*
*/
void HuffmanTree_fillTable(HuffmanTree *huffmanTree);

/**
* Pega o código de determinado caractere na árvore com o auxilio de uma lista encadeada.
* Função usada em HuffmanTree_fillTable.
*
* @param huffmanTree - ponteiro para árvore.
* @param root - ponteiro para o root da árvore.
* @param linkedList - ponteiro para lista encadeada.
* @return void
*
*/
void HuffmanTree_catchCode(HuffmanTree *huffmanTree, HuffmanNode *root, LinkedList *linkedList);

/**
* Imprime tabela de códigos da árvore.
*
* @param huffmanTree - ponteiro para árvore.
* @return void
*
*/
void HuffmanTree_printTable(HuffmanTree *huffmanTree);

/**
* Escreve a árvore no arquivo .HUFF, respeitando a restrição do '*' e da '\' e gravando '*'
* para um nó interno.
*
* @param root - ponteiro para nó que será gravado no arquivo.
* @param outFile - ponteiro para um arquivo aberto no modo gravação (.huff).
* @return void
*
*/
void HuffmanTree_writeTree(HuffmanNode *root, FILE *outFile);

/**
* Reconstroi a árvore.
*
* @param fileCompressed - ponteiro para arquivo comprimido.
* @param current - ponteiro para nó atual.
* @param tree - ponteiro para árvore vazia para ser reconstruida
* @return void
*
*/
void HuffmanTree_rebuilding(FILE *fileCompressed, HuffmanNode *current, HuffmanTree *tree);

#endif /* HUFFMAN_TREE_H_ */
