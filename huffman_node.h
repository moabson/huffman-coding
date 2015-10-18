/*
 * huffman_node.h
 *
 */

#ifndef HUFFMAN_NODE_H_
#define HUFFMAN_NODE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct huffmanNode HuffmanNode;

struct huffmanNode {
	unsigned char character;
	int frequency;

	struct huffmanNode *nextHuffmanNode;
	struct huffmanNode *left;
	struct huffmanNode *right;
};

/**
* Cria um nó vazio para ser utilizado em HuffmanNode_createNode e HuffmanNode_createLeaf.
*
* @return ponteiro para nó vazio.
*
*/
HuffmanNode* HuffmanNode_createEmpty();

/**
* Cria um nó.
*
* @param character - caractere do nó.
* @param frequency - frequência com que o caractere aparece.
* @return ponteiro para novo nó.
*
*/
HuffmanNode* HuffmanNode_createNode(unsigned char character, int frequency, HuffmanNode *left, HuffmanNode *right);

/**
* Cria um nó folha.
*
* @param character - caractere do nó.
* @param frequency - frequência com que o caractere aparece.
* @return ponteiro para novo nó folha.
*
*/
HuffmanNode* HuffmanNode_createLeaf(unsigned char character, int frequency);

/**
* Verifica se determinado nó é um nó folha.
*
* @param huffmanNode - ponteiro para nó a ser verificado.
* @return 1 (true) se vazia ou 0 (false) caso contrário.
*
*/
int HuffmanNode_isLeaf(HuffmanNode *huffmanNode);

#endif /* HUFFMAN_NODE_H_ */
