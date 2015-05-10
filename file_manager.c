/*
 * file_manager.c
 *
 */

#include "file_manager.h"

void compressFile(char *filePath) {
	FILE *file = fopen(filePath, "r");

	if(file == NULL) {
		LOG_ERR_PTR("failed on opening file");
	} else {
		LOG_INFO("open ", "%s file successfully", filePath);

		FrequencyQueue *frequencyQueue = FrequencyQueue_create(file);
		FrequencyQueue_print(frequencyQueue);

		HuffmanTree *huffmanTree = HuffmanTree_build(frequencyQueue);

		LOG_INFO("priting root of HuffmanTree")

		printf("~ [%c:%d]\n", huffmanTree->root->character, huffmanTree->root->frequency);

		// criar arquivo de saida
	}

	fclose(file);
}

