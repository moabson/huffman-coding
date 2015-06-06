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

void Write_Trash( FILE * filecompress1, FILE * filecompress2, int size_trash);

/**
 * Grava o texto comprimido no arquivo .HUFF
 *
 * @param FILE - ponteiro para o arquivo que será comprimido, aberto no modo leitura
 * @param FILE - ponteiro para o arquivo comprimido, aberto no modo escrita
 * @param HuffmanTree - ponteiro para a árvore de huffman que contém todas as novas codificações dos caracteres
 * @return int - a quantidade de lixo do último byte gravado no arquivo comprimido
 */
int Write_newText(FILE * file, FILE * file_comp, HuffmanTree * tree);

/**
 * Grava o cabeçalho do arquivo compactado, contendo dois bytes representando a quantidade de lixo do último byte e a quatidade de nós da árvore em seguida a árvore gravada em pré-ordem
 *
 *@param FILE - ponteiro para o arquivo que será comprimido, aberto no modo leitura
 *@param HuffmanTree - ponteiro para a árvore de huffman que será gravada no arquivo compactado e também será usada para gravar a quantidade de nós
 *@return void
 */
void Write_Header(FILE * file, HuffmanTree * tree);

/**
 * Comprimi o arquivo
 *
 * @param char - caminho para o arquivo que será comprimido
 * @return void
 */
void compressFile(char *filePath);

// void decompressFile(char *filePath);

#endif /* FILE_MANAGER_H_ */
