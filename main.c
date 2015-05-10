#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency_queue.h"
#include "huffman_tree.h"

#define MAX 256

int main(int argc, char *argv[]) {
	char string[] = "this is an example of a huffman tree";

	FrequencyQueue *frequencyQueue = FrequencyQueue_create(string);
	FrequencyQueue_print(frequencyQueue);

	printf("[*] printing HuffmanTree root\n");

	HuffmanTree *huffmanTree = HuffmanTree_build(frequencyQueue);

	printf("[%c:%d]\n", huffmanTree->root->character, huffmanTree->root->frequency);

	return 0;
}
