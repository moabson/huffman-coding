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
	char character;
	int frequency;

	struct huffmanNode *nextHuffmanNode;
	struct huffmanNode *left;
	struct huffmanNode *right;
};

HuffmanNode* HuffmanNode_createEmpty();

HuffmanNode* HuffmanNode_createNode(char character, int frequency, HuffmanNode *left, HuffmanNode *right);

HuffmanNode* HuffmanNode_createLeaf(char character, int frequency);

int HuffmanNode_isLeaf(HuffmanNode *huffmanNode);

#endif /* HUFFMAN_NODE_H_ */
