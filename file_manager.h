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

void Write_Trash( FILE * file_comp, FILE * file2, int size_trash);

int Write_newText(FILE * file, FILE * file_comp, HuffmanTree * tree);

void Write_Header(FILE * file, HuffmanTree * tree);

void compressFile(char *filePath);

// void decompressFile(char *filePath);

#endif /* FILE_MANAGER_H_ */
