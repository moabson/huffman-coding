/*
 * file_manager.h
 *
 */

#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include <stdio.h>
#include "frequency_queue.h"
#include "huffman_tree.h"
#include "huffman_node.h"
#include "debug.h"
#include "bitwise_operations.h"


/**
 * Grava nos três primeiros bits do primeiro byte do cabeçalho do arquivo de saida o tamanho do lixo
 *
 *
 * @param fileOutRead - ponteiro para o arquivo comprimido, aberto no modo escrita
 * @param fileOutWriter - Ponteiro para o arquivo comprimido, aberto no modo leitura
 * @param sizeTrash - tamanho do lixo
 * @return void
 *
 */
void FileManager_writeTrash(FILE *fileOutRead, FILE *fileOutWriter, int sizeTrash);

/**
 * Grava o texto comprimido no arquivo (.huff)
 *
 * @param originalFileRead - ponteiro para o arquivo que será comprimido, aberto no modo leitura
 * @param fileOutWriter - ponteiro para o arquivo comprimido, aberto no modo escrita
 * @param huffmanTree - ponteiro para a árvore de huffman que contém todas as novas codificações dos caracteres
 * @return quantidade de lixo do último byte gravado no arquivo comprimido
 */
int FileManager_writeNewText(FILE *originalFileRead, FILE *fileOutWriter, HuffmanTree *huffmanTree);

/**
 * Grava o cabeçalho do arquivo compactado, contendo dois bytes representando a quantidade de lixo do último byte e a quatidade de nós da árvore em seguida a árvore gravada em pré-ordem
 *
 * @param fileOutRead - ponteiro para o arquivo de saída, aberto no modo escrita
 * @param huffmanTree - ponteiro para a árvore de huffman que será gravada no arquivo compactado e também será usada para gravar a quantidade de nós
 * @return void
 */
void FileManager_writeHeader(FILE *fileOutWriter, HuffmanTree *huffmanTree);

/**
 * Comprime o arquivo
 *
 * @param fileName - nome do arquivo que será comprimido
 * @return void
 */
void FileManager_compressFile(char *fileName);
/*
 * Descomprime o arquivo
 *
 * @param fileName - caminho para o arquivo que será descomprimido
 * @return void
 */
void FileManager_decompressFile(char *fileName);
/*
 * Pega o tamanho do lixo nos três primeiros bites do primeiro byte do arquivo
 *
 * @param file - ponteiro para o arquivo que será descomprimido, aberto no modo leitura
 * @return int - o tamanho do lixo
 */
int FileManager_getTrash(FILE * file);
/*
 * Pega no cabeçalho do arquivo a quantidade de nós da árvore, sendo que essa quantidade está grada nos cinco ultimos bites do primeiro byte e nos oito bites do segundo byte
 *
 * @param  file - ponteiro para o arquivo que será descomprimido, aberto no modo leitura
 * @return int - quantidade de lixo
 */
int FileManager_numberNodes(FILE *file);
/*
 * decodifica os cararacteres do arquivo através do caminhamento na árvore de huffman, e grava os caracteres decodificados no arquivo descomprimido lendo somente até antes do lixo contido no último byte do arquivo
 *
 * @param  fileCompressedRead - ponteiro para o arquivo comprimido, aberto no modo leitura
 * @param huffmanTree - árvore de huffman com todos os caracteres sendo folhas
 * @param originalFileWriter - ponteiro para o arquivo já descomprimido, aberto no modo gravação
 * @param int - quantidade de lixo contido no último byte do arquivo
 * @return void
 */
void FileManager_decode(FILE *fileCompressedRead, HuffmanTree *huffmanTree, FILE *originalFileWriter, int sizeTrash);
#endif /* FILE_MANAGER_H_ */
