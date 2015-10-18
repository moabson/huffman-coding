/*
 * file_manager.c
 *
 */

#include "file_manager.h"

void FileManager_decode(FILE *fileCompressedRead, HuffmanTree * huffmanTree,FILE * originalFileWriter, int sizeTrash){
	int currentChar;
	int nextChar;
	int end, i, j;
	HuffmanNode * auxNode = huffmanTree->root;

	end = 0;
	i = 7;
	j = 7;
	currentChar = fgetc(fileCompressedRead);

	while(1){
		if((nextChar = fgetc(fileCompressedRead)) == EOF){
			// flag para indicar o fim do arquivo
			end = 1;
		}
		// se nextChar não indicar o fim do arquivo
		if(!end){
			// percorre um byte, bit a bit
			while(i >= 0){
				if(BitwiseOperations_isBitISet(currentChar,i)){
					auxNode = auxNode->right;
					i--;
				} else {
					auxNode = auxNode->left;
					i--;
				}
				if(HuffmanNode_isLeaf(auxNode)){
					putc(auxNode->character, originalFileWriter);
					auxNode = huffmanTree->root;
				}
			}
			// quando o byte acabar, o próximo byte será percorrido bit a bit
			i = 7;
			currentChar = nextChar;

		}
		else{
			// fim do arquivo foi detectado
			for(i = 8 - sizeTrash; i > 0; i--, j--){
				if(BitwiseOperations_isBitISet(currentChar,j)){
					auxNode = auxNode->right;
				}else{
					// se houver lixo no ultimo byte, o desconsideramos,
					// fazendo a subtração do tamanho do mesmo
					auxNode = auxNode->left;
				}
				if(HuffmanNode_isLeaf(auxNode)){
					putc(auxNode->character,originalFileWriter);
					auxNode = huffmanTree->root;

				}

			}

			// acabou
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

		strcat(filePath,".huff");
		FILE * filecompress1 = fopen(filePath,"w");
		FILE * filecompress2 = fopen(filePath,"r");

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
				filePath[strlen(filePath) - 5] = '\0';
				FILE *decompress = fopen(filePath,"w");
				FileManager_decode(file,tree,decompress,size_trash);
				LOG_INFO("Uncompressed file");
				fseek (file, 0, SEEK_END);
				fseek (decompress, 0, SEEK_END);
				printf("Compressed file size = %ld\n",ftell(file));
				printf("Umcompressed file size = %ld\n",ftell(decompress));
				printf("The compression rate = %lf%\n",(double)((ftell(decompress) - ftell(file))*100)/ftell(decompress));

			}

		}
}

