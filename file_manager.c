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

	// i controla a posição no primeiro byte
	// j controla a posição no sizeTrash

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
	int numberOfNodes = 0;
	int i;

	// percorre o primeiro byte
	// i começa de 4 pulando os 3 bits do lixo

	for(i = 4; i > -1; i--){
		if(BitwiseOperations_isBitISet(character, i)){
			numberOfNodes = BitwiseOperations_setBit(numberOfNodes,i + 8);
		}
	}

	// percorre o segundo byte
	// i começa de 7 indicando o primeiro bit do byte

	character = fgetc(file);

	for(i = 7; i > -1; i--){
		if(BitwiseOperations_isBitISet(character, i)){
			numberOfNodes = BitwiseOperations_setBit(numberOfNodes,i);
		}
	}
	printf("number of nodes |%d|\n",numberOfNodes);
	return numberOfNodes;
}

void FileManager_writeTrash(FILE * fileOutRead, FILE * fileOutWriter, int sizeTrash){

	unsigned char character;
	int i;

	character = fgetc(fileOutWriter);

	// grava o lixo nos 3 primeiros bits
	// pos: i + 5
	//   7   6   5
	// | 0 | 0 | 0 | ...
	for(i = 0; i < 3; i++){
		if(BitwiseOperations_isBitISet(sizeTrash, i)){
			character = BitwiseOperations_setBit(character,i + 5);
		}

	}

	// grava o primeiro byte com os 3 primeiros bits modificados, com o tamanho do lixo
	putc(character,fileOutRead);



}

void FileManager_writeHeader(FILE * fileOutWriter, HuffmanTree * huffmanTree){

	unsigned char mask = 0;
	int i;

	// 2 bytes = 16 bits
	// 3 bits primeiros para o lixo
	// 13 bits restantes para a quantidade de Nós
	for(i = 12; i >=0 ; i--){
		// transição para o segundo byte
		// grava o primeiro byte no arquivo e inicia o segundo
		if(i == 7){
			putc(mask,fileOutWriter);
			mask = 0;
		}
		// verifica se o bit na posição i está setado
		if(BitwiseOperations_isBitISet(huffmanTree->number_nodes,i)){
			// primeiro byte
			// se i estiver no intervalo [8, 12], então estamos no primeiro byte
			if(i > 7 && i < 13){
				mask = BitwiseOperations_setBit(mask,i - 8);
			}
			// segundo byte
			else{
				mask = BitwiseOperations_setBit(mask,i);
			}

		}

	}

	// grava o segundo byte
	putc(mask,fileOutWriter);

	HuffmanTree_writeTree(huffmanTree->root,fileOutWriter);

}
int FileManager_writeNewText(FILE * originalFileRead, FILE * fileOutWriter, HuffmanTree * huffmanTree){
	unsigned char character;
	unsigned char mask = 0;
	int i, j,sizeTrash = 0;

	// j indica o indice do bit
	j = 7;

	while(!feof(originalFileRead)){

		character = fgetc(originalFileRead);
		if(feof(originalFileRead)){
			// se j == 7, então não sobrou bits
			if(j == 7){
				j = 0;
			}
			// caso contrario grava a quantidade de bits que sobrou (lixo)
			else{
				putc(mask,fileOutWriter);
				j++;
			}
			break;
		}
		for(i = 0; i < strlen(huffmanTree->table[character]); i++, j--){
			if(huffmanTree->table[character][i] == '1'){
				mask = BitwiseOperations_setBit(mask,j);
			}
			// quando j chegar a 0, o byte foi setado, então grava-o
			// no arquivo e reinicia o j e mask
			if(j == 0){
				j = 8;
				putc(mask,fileOutWriter);
				mask = 0;
			}
		}

	}
	sizeTrash = j;
	return sizeTrash;
}


void FileManager_compressFile(char *fileName){
	FILE *file = fopen(fileName, "r");
	int size_trash;

	if(file == NULL) {
		LOG_ERR_PTR("failed on opening file");
	} else {
		LOG_INFO("open ", "%s file successfully", fileName);

		FrequencyQueue *frequencyQueue = FrequencyQueue_create(file);
		FrequencyQueue_print(frequencyQueue);

		HuffmanTree *huffmanTree = HuffmanTree_build(frequencyQueue);

		LOG_INFO("priting root of HuffmanTree");

		printf("~ [%c:%d]\n", huffmanTree->root->character, huffmanTree->root->frequency);

		HuffmanTree_fillTable(huffmanTree);
		HuffmanTree_printTable(huffmanTree);

		strcat(fileName,".huff");
		FILE * fileOutWriter = fopen(fileName,"w");
		FILE * fileOutRead = fopen(fileName,"r");

		FileManager_writeHeader(fileOutWriter,huffmanTree);
		LOG_INFO("Header recorded with success");
		rewind(file);
		size_trash = FileManager_writeNewText(file,fileOutWriter,huffmanTree);
		LOG_INFO("compressed text");
		rewind(fileOutWriter);

		FileManager_writeTrash(fileOutWriter,fileOutRead,size_trash);
		LOG_INFO("Trash recorded with success");
		LOG_INFO("File compressed with success");
		// criar arquivo de saida

		fseek (file, 0, SEEK_END);
		fseek (fileOutRead, 0, SEEK_END);
		printf("Original file size = %ld\n",ftell(file));
		printf("Compressed file size = %ld\n",ftell(fileOutRead));
		printf("The compression rate = %lf%\n",(double)((ftell(file) - ftell(fileOutRead))*100)/ftell(file));


	}

	fclose(file);
}
void FileManager_decompressFile(char *fileName){
	FILE *fileCompressed = fopen(fileName, "r");
	HuffmanTree * huffmanTree = HuffmanTree_createEmpty();
	HuffmanNode * root = HuffmanNode_createEmpty();
	int sizeTrash, numberOfNodes;

		if(fileCompressed == NULL) {
			LOG_ERR_PTR("failed on opening file");
		} else {
			LOG_INFO("open ", "%s file successfully", fileName);

			sizeTrash = FileManager_getTrash(fileCompressed);

			printf("size trash %d\n",sizeTrash);

			rewind(fileCompressed);

			numberOfNodes = FileManager_numberNodes(fileCompressed);

			printf("%d\n",numberOfNodes);

			if(numberOfNodes == 1){
				root->character = fgetc(fileCompressed);
				huffmanTree->root = root;
			}else{
				root->character = fgetc(fileCompressed);

				huffmanTree->root = root;
				huffmanTree->number_nodes = numberOfNodes - 1;

				HuffmanTree_rebuilding(fileCompressed, huffmanTree->root, huffmanTree);

				LOG_INFO("Tree of Huffman rebuilt");

				HuffmanTree_fillTable(huffmanTree);
				HuffmanTree_printTable(huffmanTree);

				fileName[strlen(fileName) - 5] = '\0';

				FILE *decompress = fopen(fileName,"w");

				FileManager_decode(fileCompressed,huffmanTree,decompress,sizeTrash);

				LOG_INFO("Uncompressed file");
			}

		}
}

