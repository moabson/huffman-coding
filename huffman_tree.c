/*
 * huffman_tree.c
 *
 */

#include "huffman_tree.h"

#define NULL_CHAR 0

HuffmanTree* HuffmanTree_createEmpty() {
	HuffmanTree *emptyHuffmanTree = (HuffmanTree *) malloc(sizeof(HuffmanTree));

	emptyHuffmanTree->root = NULL;

	return emptyHuffmanTree;
}

HuffmanTree* HuffmanTree_build(FrequencyQueue *frequencyQueue) {
	HuffmanTree *huffmanTree = HuffmanTree_createEmpty();

	if(!FrequencyQueue_isEmpty(frequencyQueue)) {
		while(frequencyQueue->length > 1) {
			HuffmanNode *left = FrequencyQueue_get(frequencyQueue);
			HuffmanNode *right = FrequencyQueue_get(frequencyQueue);

			HuffmanNode *newHuffmanNode = HuffmanNode_createNode(NULL_CHAR, (left->frequency + right->frequency), left, right);

			FrequencyQueue_insert(frequencyQueue, newHuffmanNode, newHuffmanNode->frequency);
		}

		huffmanTree->root = FrequencyQueue_get(frequencyQueue);
	}

	return huffmanTree;
}

