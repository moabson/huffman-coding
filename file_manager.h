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

void Write_Header(FILE * file, HuffmanTree * tree);

void compressFile(char *filePath);

// void decompressFile(char *filePath);

#endif /* FILE_MANAGER_H_ */
