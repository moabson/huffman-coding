/*
 * huffman_node.c
 *
 */

#include "huffman_node.h"

HuffmanNode* HuffmanNode_createEmpty() {
	HuffmanNode *emptyHuffmanNode = (HuffmanNode *) malloc(sizeof(HuffmanNode));

	emptyHuffmanNode->character = 0;
	emptyHuffmanNode->frequency = 0;
	emptyHuffmanNode->nextHuffmanNode = NULL;
	emptyHuffmanNode->left = NULL;
	emptyHuffmanNode->right = NULL;

	return emptyHuffmanNode;
}

HuffmanNode* HuffmanNode_createNode(unsigned char character, int frequency, HuffmanNode *left, HuffmanNode *right) {
	HuffmanNode *huffmanNode = HuffmanNode_createEmpty();

	huffmanNode->character = character;
	huffmanNode->frequency = frequency;
	huffmanNode->left = left;
	huffmanNode->right = right;

	return huffmanNode;
}

HuffmanNode* HuffmanNode_createLeaf(unsigned char character, int frequency) {
	HuffmanNode *leafHuffmanNode = HuffmanNode_createEmpty();

	leafHuffmanNode->character = character;
	leafHuffmanNode->frequency = frequency;

	return leafHuffmanNode;
}

int HuffmanNode_isLeaf(HuffmanNode *huffmanNode) {
	return (huffmanNode->left == NULL && huffmanNode->right == NULL);
}
