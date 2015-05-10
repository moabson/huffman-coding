#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency_queue.h"
#include "huffman_tree.h"
#include "debug.h"

#define MAX 256

int main(int argc, char *argv[]) {
	char string[] = "this is an example of a huffman tree";

	FrequencyQueue *frequencyQueue = FrequencyQueue_create(string);
	FrequencyQueue_print(frequencyQueue);

	HuffmanTree *huffmanTree = HuffmanTree_build(frequencyQueue);

	LOG_INFO("priting root of HuffmanTree")

	printf("~ [%c:%d]\n", huffmanTree->root->character, huffmanTree->root->frequency);

	return 0;
}
