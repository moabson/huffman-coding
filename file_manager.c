/*
 * file_manager.c
 *
 */

#include "file_manager.h"

void Write_Header(FILE * file, HuffmanTree * tree){

	char character = 0;
	int i;
	for(i = 12; i >=0 ; i--){
		if(i == 7){
			putc(character,file);
			character = 0;
		}
		if(isBitISet(tree->number_nodes,i))
		{
			if(i > 7 && i < 13){
				character = setBit(character,i - 8);
			}
			else{
				character = setBit(character,i);
			}

		}

	}
	putc(character,file);

	Write_Tree(tree->root,file);

}

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

		HuffmanTree_fillTable(huffmanTree);
		HuffmanTree_printTable(huffmanTree);
		printf("number of nodes %d\n",huffmanTree->number_nodes);
		FILE * file_comp = fopen("teste.HUFF","w");
		Write_Header(file_comp,huffmanTree);

		// criar arquivo de saida
	}

	fclose(file);
}

