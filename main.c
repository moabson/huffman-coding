#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_manager.h"

#define MAX 256

int main(int argc, char *argv[]) {
	int compress = 0;
	int decompress = 0;
	char filePath[MAX];

	if(argc == 3) {
		if(strcmp(argv[1], "-c") == 0) {
			compress = 1;
		} else if(strcmp(argv[1], "-d") == 0) {
			decompress = 1;
		}

		strncpy(filePath, argv[2], MAX);
	}

	if(compress) {
		compressFile(filePath);
	} else if(decompress) {
		printf("Descomprimir arquivo %s\n", filePath);
	} else {
		// usage
	}

	/*

	char string[] = "this is an example of a huffman tree";

	FrequencyQueue *frequencyQueue = FrequencyQueue_create(string);
	FrequencyQueue_print(frequencyQueue);

	HuffmanTree *huffmanTree = HuffmanTree_build(frequencyQueue);

	LOG_INFO("priting root of HuffmanTree")

	printf("~ [%c:%d]\n", huffmanTree->root->character, huffmanTree->root->frequency);

	*/

	return 0;
}
