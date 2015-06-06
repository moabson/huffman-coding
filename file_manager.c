/*
 * file_manager.c
 *
 */

#include "file_manager.h"

void Write_Trash(FILE * filecompress1, FILE * filecompress2, int size_trash){

	unsigned char character;
	int i;

	character = fgetc(filecompress2);
	for(i = 0; i < 3; i++){
		if(isBitISet(size_trash, i)){
			character = setBit(character,i + 5);
			printf("character %d\n",character);
		}

	}
	putc(character,filecompress1);
	printf("size trash %d\n",size_trash);



}

void Write_Header(FILE * file, HuffmanTree * tree){

	unsigned char character = 0;
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

	HuffmanTree_writeTree(tree->root,file);

}
int Write_newText(FILE * file, FILE * file_comp, HuffmanTree * tree){
	unsigned char character;
	unsigned char new_character = 0;
	int i, j;
	j = 7;

	while(!feof(file)){

		character = fgetc(file);
		if(feof(file))
			break;

		for(i = 0; i < strlen(tree->table[character]); i++, j--){
			if(tree->table[character][i] == '1'){
				new_character = setBit(new_character,j);

			}

			if(j == 0){
				j = 8;
				putc(new_character,file_comp);
				new_character = 0;
			}
		}

	}
	printf("lixo %d\n",7 - j);
	putc(new_character,file_comp);
	return (7 - j);
}


void compressFile(char *filePath){
	FILE *file = fopen(filePath, "r");

	if(file == NULL) {
		LOG_ERR_PTR("failed on opening file");
	} else {
		LOG_INFO("open ", "%s file successfully", filePath);

		FrequencyQueue *frequencyQueue = FrequencyQueue_create(file);
		FrequencyQueue_print(frequencyQueue);

		int size_trash;

		HuffmanTree *huffmanTree = HuffmanTree_build(frequencyQueue);

		LOG_INFO("priting root of HuffmanTree")

		printf("~ [%c:%d]\n", huffmanTree->root->character, huffmanTree->root->frequency);

		HuffmanTree_fillTable(huffmanTree);
		HuffmanTree_printTable(huffmanTree);
		printf("number of nodes %d\n",huffmanTree->number_nodes);

		FILE * filecompress1 = fopen("teste.HUFF","w");
		FILE * filecompress2 = fopen("teste.HUFF","r");

		Write_Header(filecompress1,huffmanTree);
		rewind(file);
		size_trash = Write_newText(file,filecompress1,huffmanTree);
		rewind(filecompress1);

		Write_Trash(filecompress1,filecompress2,size_trash);
		// criar arquivo de saida

	}

	fclose(file);
}

