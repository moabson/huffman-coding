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
 * Grava a quantidade de lixo do ultimo byte gravado no arquivo comprimido no primeiro byte do arquivo comprimido
 *
 * @param FILE - ponteiro para o arquivo comprimido, aberto no modo escrita
 * @param FILE - ponteiro para o arquivo comprimido, aberto no modo leitura
 * @param int - tamanho do lixo
 * @return void
 */

void FileManager_writeTrash( FILE * filecompress1, FILE * filecompress2, int size_trash);

/**
 * Grava o texto comprimido no arquivo .HUFF
 *
 * @param FILE - ponteiro para o arquivo que será comprimido, aberto no modo leitura
 * @param FILE - ponteiro para o arquivo comprimido, aberto no modo escrita
 * @param HuffmanTree - ponteiro para a árvore de huffman que contém todas as novas codificações dos caracteres
 * @return int - a quantidade de lixo do último byte gravado no arquivo comprimido
 */
int FileManager_writeNewText(FILE * file, FILE * file_comp, HuffmanTree * tree);

/**
 * Grava o cabeçalho do arquivo compactado, contendo dois bytes representando a quantidade de lixo do último byte e a quatidade de nós da árvore em seguida a árvore gravada em pré-ordem
 *
 *@param FILE - ponteiro para o arquivo que será comprimido, aberto no modo leitura
 *@param HuffmanTree - ponteiro para a árvore de huffman que será gravada no arquivo compactado e também será usada para gravar a quantidade de nós
 *@return void
 */
void FileManager_writeHeader(FILE * file, HuffmanTree * tree);

/**
 * Comprimi o arquivo
 *
 * @param char - caminho para o arquivo que será comprimido
 * @return void
 */
void FileManager_compressFile(char *filePath);
/*
 * Descommprimi o arquivo
 *
 * @param char - caminho para o arquivo que será descomprimido
 * @return void
 */
void FileManager_decompressFile(char *filePath);
/*
 * Pega o tamanho do lixo nos três primeiros bites do primeiro byte do arquivo
 *
 * @param FILE - ponteiro para o arquivo que será descomprimido, aberto no modo leitura
 * @return int - o tamanho do lixo
 */
int FileManager_getTrash(FILE * file);
/*
 * Pega no cabeçalho do arquivo a quantidade de nós da árvore, sendo que essa quantidade está grada nos cinco ultimos bites do primeiro byte e nos oito bites do segundo byte
 *
 * @param  FILE - ponteiro para o arquivo que será descomprimido, aberto no modo leitura
 * @return int - quantidade de lixo
 */
int FileManager_numberNodes(FILE *file);
/*
 * decodifica os cararacteres do arquivo através do caminhamento na árvore de huffman, e grava os caracteres decodificados no arquivo descomprimido lendo somente até antes do lixo contido no último byte do arquivo
 *
 * @param  FILE - ponteiro para o arquivo comprimido, aberto no modo leitura
 * @param HuffmanTree - arvore de Huffman com todos os caracteres sendo folhas
 * @param FILE - ponteiro para o arquivo já descomprimido, aberto no modo gravação
 * @param int - quantidade de lixo contido no último byte do arquivo
 * @return void
 */
void FileManager_decode(FILE *file, HuffmanTree * tree,FILE * decompress, int size_trash);

#endif /* FILE_MANAGER_H_ */
