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

/*
*Cria o nó de huffman vazio.
*@Retona o ponteiro do nó emptyHuffmanNode.
*/
HuffmanNode* HuffmanNode_createEmpty();

/*
*Cria o nó de huffman com os dados recebidos.
*@Recebe o caracter character, o inteiro frequency, o ponteiro para o nó left e o ponteiro para o nó right.
*@Retorna o ponteiro para o nó huffmanNode.
*/
HuffmanNode* HuffmanNode_createNode(char character, int frequency, HuffmanNode *left, HuffmanNode *right);

/*
*Cria um nó que representa uma folha da arvore de Huffman com os valores dados.
*@Recebe o caracter character e o inteiro frequency.
*@Retorna o ponteiro para o nó leafHuffmanNode.
*/
HuffmanNode* HuffmanNode_createLeaf(char character, int frequency);

/*
*Verifica se o nó recebido é uma folha.
*@Recebe o ponteiro ponteiro para o nó huffmanNode.
*@Retorna TRUE se for uma folha e FALSE caso contrário.
*/
int HuffmanNode_isLeaf(HuffmanNode *huffmanNode);

#endif /* HUFFMAN_NODE_H_ */
