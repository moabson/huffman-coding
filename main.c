#include <stdio.h>
#include <stdlib.h>
#include "frequency_queue.h"
#include "huffman_tree.h"


int main(int argc, char *argv[]) {
	FrequencyQueue *frequencyQueue = FrequencyQueue_create();

	HuffmanNode *newHuffmanNode1 = HuffmanNode_createLeaf('A', 3);
	HuffmanNode *newHuffmanNode2 = HuffmanNode_createLeaf('B', 1);
	HuffmanNode *newHuffmanNode3 = HuffmanNode_createLeaf('C', 1);
	HuffmanNode *newHuffmanNode4 = HuffmanNode_createLeaf('T', 1);
	HuffmanNode *newHuffmanNode5 = HuffmanNode_createLeaf('E', 1);

	FrequencyQueue_insert(frequencyQueue, newHuffmanNode1, newHuffmanNode1->frequency);
	FrequencyQueue_insert(frequencyQueue, newHuffmanNode2, newHuffmanNode2->frequency);
	FrequencyQueue_insert(frequencyQueue, newHuffmanNode3, newHuffmanNode3->frequency);
	FrequencyQueue_insert(frequencyQueue, newHuffmanNode4, newHuffmanNode4->frequency);
	FrequencyQueue_insert(frequencyQueue, newHuffmanNode5, newHuffmanNode5->frequency);

	FrequencyQueue_print(frequencyQueue);

	printf("[*] printing HuffmanTree root\n");
	HuffmanTree *huffmanTree = HuffmanTree_build(frequencyQueue);

	printf("[%c:%d]\n", huffmanTree->root->character, huffmanTree->root->frequency);

	return 0;
}
