/*
 * file_manager.c
 *
 */

#include "file_manager.h"

void FileManager_decode(FILE *file, HuffmanTree * tree,FILE * decompress, int size_trash){
	int character1;
	int character2;
	int end, i, j;
	HuffmanNode * auxNode = tree->root;

	end = 0;
	i = 7;
	j = 7;
	character1 = fgetc(file);



	while(1){
		if((character2 = fgetc(file)) == EOF){
			end = 1;
		}
		if(!end){
			while(i >= 0){
				if(BitwiseOperations_isBitISet(character1,i)){
					auxNode = auxNode->right;
					i--;
				} else {
					auxNode = auxNode->left;
					i--;
				}
				if(HuffmanNode_isLeaf(auxNode)){
					putc(auxNode->character, decompress);
					auxNode = tree->root;
				}
			}

			i = 7;
			character1 = character2;

		}
		else{
			for(i = 8 - size_trash; i > 0; i--, j--){
				if(BitwiseOperations_isBitISet(character1,j)){
					auxNode = auxNode->right;
				}else{
					auxNode = auxNode->left;
				}
				if(HuffmanNode_isLeaf(auxNode)){
					putc(auxNode->character,decompress);
					auxNode = tree->root;

				}

			}
			break;
		}

	}


}

int FileManager_getTrash(FILE * file){
	unsigned char character = fgetc(file);
	unsigned char size_trash = 0;
	int i,j;
	j = 2;

	for(i = 7; i > 4; i--){
		if(BitwiseOperations_isBitISet(character, i)){
			size_trash = BitwiseOperations_setBit(size_trash,j);

		}
		j--;
	}

	return size_trash;
}
int FileManager_numberNodes(FILE *file){
	unsigned char character = fgetc(file);
	int nodes = 0;
	int i;

	for(i = 4; i > -1; i--){
		if(BitwiseOperations_isBitISet(character, i)){
			nodes = BitwiseOperations_setBit(nodes,i + 8);
		}
	}

	character = fgetc(file);

	for(i = 7; i > -1; i--){
		if(BitwiseOperations_isBitISet(character, i)){
			nodes = BitwiseOperations_setBit(nodes,i);
		}
	}
	printf("number of nodes |%d|\n",nodes);
	return nodes;
}

void FileManager_writeTrash(FILE * filecompress1, FILE * filecompress2, int size_trash){

	unsigned char character;
	int i;

	character = fgetc(filecompress2);
	for(i = 0; i < 3; i++){
		if(BitwiseOperations_isBitISet(size_trash, i)){
			character = BitwiseOperations_setBit(character,i + 5);
		}

	}
	putc(character,filecompress1);



}

void FileManager_writeHeader(FILE * file, HuffmanTree * tree){

	unsigned char character = 0;
	int i;
	for(i = 12; i >=0 ; i--){
		if(i == 7){
			putc(character,file);
			character = 0;
		}
		if(BitwiseOperations_isBitISet(tree->number_nodes,i))
		{
			if(i > 7 && i < 13){
				character = BitwiseOperations_setBit(character,i - 8);
			}
			else{
				character = BitwiseOperations_setBit(character,i);
			}

		}

	}
	putc(character,file);

	HuffmanTree_writeTree(tree->root,file);

}
int FileManager_writeNewText(FILE * file, FILE * file_comp, HuffmanTree * tree){
	unsigned char character;
	unsigned char new_character = 0;
	int i, j;
	j = 7;

	while(!feof(file)){

		character = fgetc(file);
		if(feof(file)){
			if(j == 7)
				j = 0;
			else{
				putc(new_character,file_comp);
				j++;
			}
			break;
		}
		for(i = 0; i < strlen(tree->table[character]); i++, j--){
			if(tree->table[character][i] == '1'){
				new_character = BitwiseOperations_setBit(new_character,j);
			}

			if(j == 0){
				j = 8;
				putc(new_character,file_comp);
				new_character = 0;
			}
		}

	}

	return (j);
}


void FileManager_compressFile(char *filePath){
	FILE *file = fopen(filePath, "r");

	if(file == NULL) {
		LOG_ERR_PTR("failed on opening file");
	} else {
		LOG_INFO("open ", "%s file successfully", filePath);

		FrequencyQueue *frequencyQueue = FrequencyQueue_create(file);
		FrequencyQueue_print(frequencyQueue);

		int size_trash;

		HuffmanTree *huffmanTree = HuffmanTree_build(frequencyQueue);

		LOG_INFO("priting root of HuffmanTree");

		printf("~ [%c:%d]\n", huffmanTree->root->character, huffmanTree->root->frequency);

		HuffmanTree_fillTable(huffmanTree);
		HuffmanTree_printTable(huffmanTree);

		FILE * filecompress1 = fopen("teste.HUFF","w");
		FILE * filecompress2 = fopen("teste.HUFF","r");

		FileManager_writeHeader(filecompress1,huffmanTree);
		LOG_INFO("Header recorded with success");
		rewind(file);
		size_trash = FileManager_writeNewText(file,filecompress1,huffmanTree);
		LOG_INFO("compressed text");
		rewind(filecompress1);

		FileManager_writeTrash(filecompress1,filecompress2,size_trash);
		LOG_INFO("Trash recorded with success");
		LOG_INFO("File compressed with success");
		// criar arquivo de saida

	}

	fclose(file);
}
void FileManager_decompressFile(char *filePath){
	FILE *file = fopen(filePath, "r");
	HuffmanTree * tree = HuffmanTree_createEmpty();
	HuffmanNode * root = HuffmanNode_createEmpty();
	int size_trash;
	int nodes;
		if(file == NULL) {
			LOG_ERR_PTR("failed on opening file");
		} else {
			LOG_INFO("open ", "%s file successfully", filePath);
			size_trash = FileManager_getTrash(file);
			printf("size trash %d\n",size_trash);
			rewind(file);
			nodes = FileManager_numberNodes(file);
			printf("%d\n",nodes);
			if(nodes == 1){
				root->character = fgetc(file);
				tree->root = root;
			}else{
				root->character = fgetc(file);
				tree->root = root;
				tree->number_nodes = nodes - 1;
				HuffmanTree_rebuilding(file, tree->root, tree);
				LOG_INFO("Tree of Huffman rebuilt");
				HuffmanTree_fillTable(tree);
				HuffmanTree_printTable(tree);
				FILE *decompress = fopen("decompress.txt","w");
				FileManager_decode(file,tree,decompress,size_trash);
				LOG_INFO("Uncompressed file");
			}

		}
}

